#pragma once
#include <vector>
#include <string>

struct LayoutItem {
    std::string id;
    std::string type;
    std::string label;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    std::string box;
    int labelfont = 0;
    int labelsize = 0;
    int align = 0;
    std::vector<LayoutItem> items;
};

struct Layout {
    std::vector<LayoutItem> items;
};

Layout flatten_layout(const Layout &tree);
