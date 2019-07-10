#include "layout.h"
#include "reader.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Please indicate a fluid design file.\n";
        return 1;
    }

    Layout layout = read_file_layout(argv[1]);
    layout = flatten_layout(layout);

    for (const LayoutItem &item : layout.items) {
        if (item.type == "Function")
            continue;

        if (!item.id.empty())
            std::cout << "DECL_IGNORABLE static Rect " << item.id << " = "
                "{" << item.x << ", " << item.y << ", " << item.w << ", " << item.h << "}"
                ";\n";
    }

    for (const LayoutItem &item : layout.items) {
        if (!item.label.empty()) {
            std::cout << "DECL_IGNORABLE static Label " << item.id << "_label = "
                "{\"" << item.label << "\", " << item.align << ", " <<
                "{" << item.x << ", " << item.y << ", " << item.w << ", " << item.h << "}"
                "};\n";
        }
    }

    return 0;
}
