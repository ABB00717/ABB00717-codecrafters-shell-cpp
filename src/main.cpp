#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const std::set<std::string> validCommands = {"echo", "exit", "type"};

void commandNotFound(std::string command) {
  std::cout << command << ": command not found\n";
}

bool inputCommand(std::string &input) {
  std::cout << "$ ";
  if (std::getline(std::cin, input))
    return true;

  return false;
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

    if (command == "exit" && args.size() == 1 && args[0] == "0") {
      return 0;
    } else if (command == "echo" && args.size() > 0) {
      std::string output = "";
      for (auto arg : args) {
        output += arg;
        output += " ";
      }
      output.pop_back();
      std::cout << output << std::endl;
    } else if (command == "type" && args.size() == 1) {
      std::string targetCommand = args[0];

      if (validCommands.count(targetCommand)) {
        std::cout << targetCommand << " is a shell builtin" << std::endl;
      } else {
        std::cout << targetCommand << ": not found\n";
      }
    } else {
      std::cout << command << ": command not found\n";
    }
  }
}
