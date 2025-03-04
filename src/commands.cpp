#include "../include/commands.h"

void commandNotFound(const std::string& command) {
  std::cout << command << ": command not found\n";
}

void handleEcho(const std::vector<std::string> &args) {
  if (args.empty()) {
    std::cout << "Invalid Usage\n";
    return;
  }

  std::ostringstream output;
  for (const auto& arg : args) {
    output << arg << " ";
  }
  
  std::string result = output.str();
  if (!result.empty())
    result.pop_back();
  std::cout << result << std::endl;
}

void handleExit(const std::vector<std::string> &args) {
  if (args.size() != 1) {
    std::cout << "Invalid Usage\n";
  }

  try {
    int exitCode = std::stoi(args[0]);
    exit(exitCode);
  } catch (...) {
    std::cout << "Invalid Exit Code" << std::endl;
  }
}

void handleType(const std::vector<std::string> &args) {
  if (args.size() != 1) {
    std::cout << "Invalid Usage\n";
    return;
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
}