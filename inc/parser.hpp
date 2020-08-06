#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>

using namespace rapidjson;

class Parser
{

public:
    Parser(/* args */);
    ~Parser();
    bool isValidJson(std::string json);
    std::string getString(std::string key);
    Parser *createDocument();
    Parser *addMember(std::string field, int value);
    Parser *addMember(std::string field, float value);
    Parser *addMember(std::string field, std::string value);
    std::string  toString();
private:
    Document m_documnet;
    Document m_docToSend;
};
