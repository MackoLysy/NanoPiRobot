#include "helpers.hpp"

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

std::string getIPAddress()
{

    auto temp = exec("ifconfig  | grep 'inet addr:'| grep -v '127.0.0.1' ");
    auto values = split(temp, ' ');

    for (auto value : values)
    {
        std::size_t found = value.find("addr:");
        if (found != std::string::npos)
        {
            std::string ToRemove = "addr:";
            eraseSubStr(value, ToRemove);
            return value;
        }
    }
    return "";
}

void eraseSubStr(std::string &mainStr, const std::string &toErase)
{
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
