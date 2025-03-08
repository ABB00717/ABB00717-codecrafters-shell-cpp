#include "../include/utils.h"
#include <cctype>
#include <cstdio>
#include <string>

bool inputCommand(std::string &input) {
  std::cout << "$ ";
  if (std::getline(std::cin, input))
    return true;

  return false;
}

std::vector<std::string> parseInputs(const std::string& input) {
  std::stringstream ss(input);
  std::string token;
  std::vector<std::string> tokens;

  char c;
  bool insideQuotes = false;
  std::string currentToken;

  while (ss.get(c)) {
    if (c == '\'') {
      insideQuotes = !insideQuotes;
      if (!insideQuotes) {
        tokens.push_back(currentToken);
        currentToken.clear();
      }
    } else if (std::isspace(c) && !insideQuotes) {
      if (!currentToken.empty()) {
        tokens.push_back(currentToken);
        currentToken.clear();
      }
    } else {
      currentToken += c;
    }
  }

  if (!currentToken.empty()) {
    tokens.push_back(currentToken);
  }

  return tokens;
}

std::string getPath(std::string command) {
  try {
    std::string path_env = std::getenv("PATH");
    
    std::stringstream ss(path_env);
    std::string path;
    
    while (std::getline(ss, path, ':')) {
      std::filesystem::path abs_path = path;
      abs_path /= command;
      if (std::filesystem::exists(abs_path)) {
        return abs_path.string();
      }
    }
  } catch (...) {
    return "";
  }

  return "";
}