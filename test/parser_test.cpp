#include <gtest/gtest.h>
#include <iostream>
#define protected public
#define private public
#include "parser.hpp"
#undef protected
#undef private

TEST(Parser, validJsonError)
{
    Parser parser;
    std::string value = "jest :d";
    ASSERT_EQ(false, parser.isValidJson(value));
}

TEST(Parser, validJson)
{
    Parser parser;
    std::string str = "{ \"hello\" : \"world\" }";
    ASSERT_EQ(true, parser.isValidJson(str));
}

TEST(Parser, getMemberEmpty)
{
    Parser parser;
    std::string str = "{ \"hello\" : \"world\" }";
    parser.isValidJson(str);
    ASSERT_EQ("", parser.getString("test"));
}

TEST(Parser, getMemberValid)
{
    Parser parser;
    std::string str = "{ \"type\" : \"init\" }";
    parser.isValidJson(str);
    ASSERT_EQ("init", parser.getString("type"));
}

TEST(Parser, doubleParse)
{
    Parser parser;
    std::string str = "{ \"type\" : \"init\" }";
    parser.isValidJson(str);
    ASSERT_EQ("init", parser.getString("type"));

    str = "{ \"hello\" : \"world\" }";
    parser.isValidJson(str);
    ASSERT_EQ("world", parser.getString("hello"));
}

TEST(Parser, simpleJSONCreate)
{
    Parser parser;
    auto result = parser.createDocument()->addMember("test", "1")->toString();
    parser.isValidJson(result);
    ASSERT_EQ("1", parser.getString("test"));
}

TEST(Parser, simpleJSONMulti)
{
    Parser parser;
    auto result = parser.createDocument()->addMember("test1", "1")->addMember("test2", "2")->toString();
    parser.isValidJson(result);
    ASSERT_EQ("1", parser.getString("test1"));
    ASSERT_EQ("2", parser.getString("test2"));
}
