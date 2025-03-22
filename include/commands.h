#ifndef COMMANDS_H
#define COMMANDS_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "utils.h"

const std::unordered_set<std::string> validCommands = {"echo", "exit", "type",
                                                       "pwd", "cd"};

void commandNotFound(const std::string& command);
void handleEcho(const std::vector<std::string>& args);
void handleExit(const std::vector<std::string>& args);
void handleType(const std::vector<std::string>& args);
void handleExternalProgram(const std::string& command,
                           const std::vector<std::string>& args);
void handlePwd();
void handleCd(const std::vector<std::string>& args);

#endif