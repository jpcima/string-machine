#include <json.hpp>
#include <memory>
#include <fstream>
#include <cstdio>

static std::string ConvertSymbol(const std::string &sym)
{
    std::string result;
    bool cap = true;
    result.reserve(sym.size());
    for (char c : sym) {
        if (c == '_')
            cap = true;
        else {
            if (cap && c >= 'a' && c <= 'z')
                c = c - 'a' + 'A';
            result.push_back(c);
            cap = false;
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    unsigned count = argc - 1;
    std::unique_ptr<nlohmann::json[]> documents{new nlohmann::json[count]};

    for (unsigned i = 0; i < count; ++i) {
        std::ifstream in(argv[i + 1]);
        documents[i] = nlohmann::json::parse(in);
    }

    for (unsigned i = 0; i < count; ++i) {
        const nlohmann::json &doc = documents[i];
        printf("static const Preset::Group pg%u = {\"%s\"};\n", i, doc["group"].get<std::string>().c_str());
    }

    for (unsigned i = 0; i < count; ++i) {
        const nlohmann::json &presets = documents[i]["presets"];
        for (unsigned p = 0, pn = presets.size(); p < pn; ++p) {
            const nlohmann::json &preset = presets[p];
            printf("static const Preset::Parameter pp%u_%u[] = {\n", i, p);
            for (auto it : preset["parameters"].items())
                printf("    {pId%s, %g},\n", ConvertSymbol(it.key()).c_str(), it.value().get<double>());
            printf("    {-1, 0},\n");
            printf("};\n");
        }
    }


    printf("const Preset Presets[] = {\n");
    for (unsigned i = 0; i < count; ++i) {
        const nlohmann::json &presets = documents[i]["presets"];
        for (unsigned p = 0, pn = presets.size(); p < pn; ++p) {
            const nlohmann::json &preset = presets[p];
            printf("    {\"%s\", &pg%u, pp%u_%u},\n", preset["name"].get<std::string>().c_str(), i, i, p);
        }
    }
    printf("};\n");

    unsigned preset_count = 0;
    for (unsigned i = 0; i < count; ++i) {
        const nlohmann::json &presets = documents[i]["presets"];
        preset_count += presets.size();
    }
    printf("const unsigned NumPresets = %u;\n", preset_count);

    return 0;
}
