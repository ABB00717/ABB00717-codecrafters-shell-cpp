#include "../include/commands.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void commandNotFound(const std::string &command) {
  std::cout << command << ": command not found\n";
}

void handleEcho(const std::vector<std::string> &args) {
  if (args.empty()) {
    std::cout << "Invalid Usage\n";
    return;
  }

  std::ostringstream output;
  for (const auto &arg : args) {
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

void handleExternalProgram(const std::string &command,
                           const std::vector<std::string> &args) {
  std::vector<char *> argsForExe;
  argsForExe.push_back(const_cast<char *>(command.c_str()));
  
  for (const auto &t : args) {
    argsForExe.push_back(const_cast<char *>(t.c_str()));
  }
  argsForExe.push_back(nullptr);

  pid_t pid = fork();
  if (pid == -1) {
    std::cerr << "Error: fork() failed";
    return;
  }

  if (pid == 0) {
    execvp(argsForExe[0], argsForExe.data());
    std::cerr << "Error: Failed to execute command\n";
    exit(1);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
}

void handlePwd() {
  std::cout << std::filesystem::current_path() << std::endl;
}