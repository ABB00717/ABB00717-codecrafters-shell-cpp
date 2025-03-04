#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

bool inputCommand(std::string &input);
std::vector<std::string> parseInputs(const std::string& input);
std::string getPath(std::string command);

#endif