#include "../include/commands.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

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
  if (validCommands.count(targetCommand)) {
    std::cout << targetCommand << " is a shell builtin" << std::endl;
  } else {
    std::string path = getPath(targetCommand);
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
  char buffer[FILENAME_MAX];
  if (getcwd(buffer, FILENAME_MAX)) {
    std::cout << buffer << std::endl;
  }
}

void handleCd(const std::vector<std::string> &args) {
  if (args.size() > 1) {
    std::cerr << "Error: No more than two directories should appear." << std::endl;
    return;
  } else if (args.empty()) {
    const char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
      std::cerr << "Error: Unable to get the home directory." << std::endl;
    }
    
    if (chdir(homeDir) != 0) {
      std::cerr << "Error: Unable to switch to the home directory." << std::endl;
      return;
    }
  } else {
    const char* newPath = const_cast<char *>(args[0].c_str());

    if (chdir(newPath) != 0) {
      std::cerr << "cd: " << newPath << ": No such file or directory" << std::endl;
      return;
    }
  }
}