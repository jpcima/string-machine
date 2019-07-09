#include "reader.h"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <fstream>

typedef std::vector<std::string> TokenList;
static bool read_file_tokens(const char *filename, TokenList &tokens);
static Layout read_tokens_layout(TokenList::iterator &tok_it, TokenList::iterator tok_end);

Layout read_file_layout(const char *filename)
{
    std::vector<std::string> tokens;
    if (!read_file_tokens(filename, tokens))
        throw std::runtime_error("Cannot read fluid design file.");

    TokenList::iterator tok_it = tokens.begin();
    TokenList::iterator tok_end = tokens.end();
    return read_tokens_layout(tok_it, tok_end);
}

static std::string consume_next_token(TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    if (tok_it == tok_end)
        throw file_format_error("Premature end of tokens");
    return *tok_it++;
}

static void ensure_next_token(const char *text, TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    std::string tok = consume_next_token(tok_it, tok_end);
    if (tok != text)
        throw file_format_error("Unexpected token: " + tok);
}

static std::string consume_enclosed_string(TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    ensure_next_token("{", tok_it, tok_end);

    std::string text = consume_next_token(tok_it, tok_end);
    if (text == "}")
        return std::string();

    for (std::string part; (part = consume_next_token(tok_it, tok_end)) != "}";) {
        text.push_back(' ');
        text.append(part);
    }

    return text;
}

static std::string consume_any_string(TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    if (tok_it != tok_end && *tok_it == "{")
        return consume_enclosed_string(tok_it, tok_end);
    else
        return consume_next_token(tok_it, tok_end);
}

static int consume_int_token(TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    std::string text = consume_next_token(tok_it, tok_end);
    return std::stoi(text);
}

static void consume_properties(LayoutItem &item, TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    ensure_next_token("{", tok_it, tok_end);
    for (std::string text; (text = consume_next_token(tok_it, tok_end)) != "}";) {
        if (text == "open" || text == "selected")
            ; // skip
        else if (text == "label")
            item.label = consume_any_string(tok_it, tok_end);
        else if (text == "xywh") {
            ensure_next_token("{", tok_it, tok_end);
            item.x = consume_int_token(tok_it, tok_end);
            item.y = consume_int_token(tok_it, tok_end);
            item.w = consume_int_token(tok_it, tok_end);
            item.h = consume_int_token(tok_it, tok_end);
            ensure_next_token("}", tok_it, tok_end);
        }
        else if (text == "box")
            item.box = consume_next_token(tok_it, tok_end);
        else if (text == "labelfont")
            item.labelfont = consume_int_token(tok_it, tok_end);
        else if (text == "labelsize")
            item.labelsize = consume_int_token(tok_it, tok_end);
        else if (text == "align")
            item.align = consume_int_token(tok_it, tok_end);
    }
}

static LayoutItem consume_layout_item(const std::string &type, TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    LayoutItem item;
    item.type = type;
    item.id = consume_any_string(tok_it, tok_end);
    consume_properties(item, tok_it, tok_end);
    if (tok_it != tok_end && *tok_it == "{") {
        consume_next_token(tok_it, tok_end);
        for (std::string text; (text = consume_next_token(tok_it, tok_end)) != "}";)
            item.items.push_back(consume_layout_item(text, tok_it, tok_end));
    }
    return item;
}

static Layout read_tokens_layout(TokenList::iterator &tok_it, TokenList::iterator tok_end)
{
    Layout layout;

    std::string version_name;
    std::string header_name;
    std::string code_name;

    while (tok_it != tok_end) {
        std::string key = consume_next_token(tok_it, tok_end);

        if (key == "version")
            version_name = consume_next_token(tok_it, tok_end);
        else if (key == "header_name") {
            ensure_next_token("{", tok_it, tok_end);
            header_name = consume_next_token(tok_it, tok_end);
            ensure_next_token("}", tok_it, tok_end);
        }
        else if (key == "code_name") {
            ensure_next_token("{", tok_it, tok_end);
            code_name = consume_next_token(tok_it, tok_end);
            ensure_next_token("}", tok_it, tok_end);
        }
        else {
            layout.items.push_back(consume_layout_item(key, tok_it, tok_end));
        }
    }

    return layout;
}

static bool read_file_tokens(const char *filename, TokenList &tokens)
{
    std::ifstream stream(filename);
    std::string line;

    std::string text;
    while (std::getline(stream, line)) {
        if (!line.empty() && line[0] != '#') {
            text.append(line);
            text.push_back('\n');
        }
    }

    if (stream.bad())
        return false;

    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    tokenizer tok(text, boost::char_separator<char>(" \t\r\n", "{}"));
    for (tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        tokens.push_back(*tok_iter);

    return !stream.bad();
}
