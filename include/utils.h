#ifndef UTILS_H
#define UTILS_H

#include <termios.h>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "commands.h"

bool inputCommand(std::string& input);
void enableRawMode(struct termios &orig_termios);
void disableRawMode(struct termios &orig_termios);
std::string tabComplete(const std::string& input);
std::string getPath(std::string command);
std::string getLongestCommonPrefix(const std::set<std::string>& candidates);

#endif