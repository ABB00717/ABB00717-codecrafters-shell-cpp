#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

const std::unordered_set<std::string> validCommands = {"echo", "exit", "type"};

void commandNotFound(std::string command) {
  std::cout << command << ": command not found\n";
}

bool inputCommand(std::string &input) {
  std::cout << "$ ";
  if (std::getline(std::cin, input))
    return true;

  return false;
}

std::string getPath(std::string command) {
  std::string path_env = std::getenv("PATH");

  std::stringstream ss(path_env);
  std::string path;

  while (!ss.eof()) {
    std::getline(ss, path, ':');
    std::string abs_path = path + '/' + command;

    if (std::filesystem::exists(abs_path))
      return abs_path;
  }

  return "";
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (inputCommand(input)) {
    std::stringstream ss(input);
    std::string command, arg;
    std::vector<std::string> args;
    ss >> command;
    while (ss >> arg)
      args.push_back(arg);

    if (command == "exit") {
      if (args.size() != 1 || args[0] != "0") {
        std::cout << "Invalid Usage\n";
        continue;
      }
        return 0;
    } else if (command == "echo") {
      if (args.size() <= 0) {
        std::cout << "Invalid Usage\n";
        continue;
      }

      std::string output = "";
      for (auto arg : args) {
        output += arg;
        output += " ";
      }
      output.pop_back();
      std::cout << output << std::endl;
    } else if (command == "type") {
      if (args.size() != 1) {
        std::cout << "Invalid Usage\n";
        continue;
      }
      
      std::string targetCommand = args[0];
      std::string path = getPath(targetCommand);
      if (validCommands.count(targetCommand)) {
        std::cout << targetCommand << " is a shell builtin" << std::endl;
      } else {
        if (path.empty()) {
          std::cout << targetCommand << ": not found\n";
        } else {
          std::cout << targetCommand << " is " << path << std::endl;
        }
      }
    } else {
      std::cout << command << ": command not found\n";
    }
  }
}
