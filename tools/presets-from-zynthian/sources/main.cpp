// Convert zss files to internal presets

#include "StringMachineShared.cpp"
#include <json.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <cstring>
using json = nlohmann::json;

static std::string preset_group = "Misc";

static std::vector<std::unique_ptr<Parameter>> parameter_list;

static size_t find_parameter(const std::string &symbol)
{
    for (size_t i = 0, n = parameter_list.size(); i < n; ++i) {
        if (parameter_list[i]->symbol == symbol.c_str())
            return i;
    }
    return ~size_t{0};
}

static std::string strip_directory(const std::string &in)
{
    size_t pos = in.rfind('/');
    if (pos == in.npos)
        return in;
    return in.substr(pos + 1);
}

static std::string strip_suffix(const std::string &in, const std::string &suffix)
{
    size_t ilen = in.size();
    size_t slen = suffix.size();
    if (slen > ilen || memcmp(in.data() + ilen - slen, suffix.data(), slen))
        return in;
    return in.substr(0, ilen - slen);
}

static void process_file(const char *filename)
{
    json doc = json::parse(std::ifstream(filename));

    json layer;
    for (json curr_layer : doc["layers"]) {
        std::string name = curr_layer["engine_name"];
        if (name == "Jalv/" DISTRHO_PLUGIN_NAME) {
            layer = curr_layer;
            break;
        }
    }

    if (layer.is_null())
        throw std::runtime_error("layer not found");

    std::string program_name = strip_directory(strip_suffix(filename, ".zss"));

    std::vector<double> values;
    values.resize(parameter_list.size());

    for (const auto &item : layer["controllers_dict"].items()) {
        std::string symbol = item.key();
        double value = item.value()["value"];

        size_t index = find_parameter(symbol);
        if (index == ~size_t{0})
            throw std::runtime_error("parameter not found: " + symbol);

        values[index] = value;
    }

    printf("{\"%s\", \"%s\", {\n", program_name.c_str(), preset_group.c_str());
    for (size_t i = 0, n = parameter_list.size(); i < n; ++i)
        printf("/* %s */ %g,\n", parameter_list[i]->name.buffer(), values[i]);
    printf("}},\n");
}

int main(int argc, char *argv[])
{
    for (size_t index = 0;; ++index) {
        std::unique_ptr<Parameter> param{new Parameter};
        InitParameter(index, *param);
        if (param->symbol.isEmpty())
            break;
        parameter_list.emplace_back(std::move(param));
    }

    try {
        for (int i = 1; i < argc; ++i)
            process_file(argv[i]);
    }
    catch (std::exception &ex) {
        std::cerr << ex.what() << "\n";
    }

    return 0;
}
