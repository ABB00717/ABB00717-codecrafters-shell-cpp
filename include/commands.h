#ifndef COMMANDS_H
#define COMMANDS_H

#include <sstream>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"

const std::unordered_set<std::string> validCommands = {"echo", "exit", "type"};
void commandNotFound(const std::string& command);
void handleEcho(const std::vector<std::string> &args);
void handleExit(const std::vector<std::string> &args);
void handleType(const std::vector<std::string> &args);
void handleExternalProgram(const std::string& command, const std::vector<std::string> &args);
void handlePwd();

#endif