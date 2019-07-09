#include "layout.h"

static void flatten_layout_do_item(Layout &layout, const LayoutItem &item)
{
    layout.items.push_back(item);
    layout.items.back().items.clear();
    for (const LayoutItem &child : item.items)
        flatten_layout_do_item(layout, child);
}

Layout flatten_layout(const Layout &tree)
{
    Layout layout;
    for (const LayoutItem &item : tree.items)
        flatten_layout_do_item(layout, item);
    return layout;
}
