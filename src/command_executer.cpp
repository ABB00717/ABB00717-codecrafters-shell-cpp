#include "../include/command_executer.h"

void executeCommand(const std::vector<std::string>& tokens) {
  if (tokens.empty())
    return;

  std::string command = tokens[0];
  std::vector<std::string> args(tokens.begin()+1, tokens.end());
  
  if (command == "exit") {
    handleExit(args);
  } else if (command == "echo") {
    handleEcho(args);
  } else if (command == "type") {
    handleType(args);
  } else {
    std::string path = getPath(command);
    if (path.empty()) {
      commandNotFound(command);
    }

    // external exe
    handleExternalProgram(command, args);
  }
}
