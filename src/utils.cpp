#include "../include/utils.h"
#include <cstdio>

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
  while (ss >> token)
    tokens.push_back(token);

  return tokens;
}

std::string getPath(std::string command) {
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

  return "";
}