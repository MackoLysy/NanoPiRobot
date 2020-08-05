#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <sstream>

std::string exec(const char* cmd);
std::string getIPAddress();

std::vector<std::string> split(const std::string& s, char delimiter);
void eraseSubStr(std::string &mainStr, const std::string &toErase);
bool GetDataFromServer(std::string &rawData, std::string &data);
