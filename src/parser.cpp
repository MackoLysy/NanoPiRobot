#include "parser.hpp"

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

bool Parser::isValidJson(std::string json)
{
    return !m_documnet.Parse(json.c_str()).HasParseError();
}

std::string Parser::getString(std::string key)
{
    if (m_documnet.HasMember(key.c_str()) && m_documnet[key.c_str()].IsString())
    {
        return m_documnet[key.c_str()].GetString();
    }
    return "";
}

Parser *Parser::createDocument()
{
    m_docToSend.SetObject();

    return this;
}

Parser *Parser::addMember(std::string field, int value)
{
    Document::AllocatorType &alloc = m_docToSend.GetAllocator();
    Value n(field.c_str(), alloc);
    m_docToSend.AddMember(n, value, alloc);
    return this;
}

Parser *Parser::addMember(std::string field, float value)
{
    Document::AllocatorType &alloc = m_docToSend.GetAllocator();
    Value n(field.c_str(), alloc);
    m_docToSend.AddMember(n, value, alloc);
    return this;
}

Parser *Parser::addMember(std::string field, std::string value)
{
    Document::AllocatorType &alloc = m_docToSend.GetAllocator();
    Value n(field.c_str(), alloc);
    Value textPart;
    textPart.SetString(value.c_str(), alloc);
    m_docToSend.AddMember(n, textPart, alloc);
    return this;
}

std::string Parser::toString()
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    m_docToSend.Accept(writer);
    return buffer.GetString();
}