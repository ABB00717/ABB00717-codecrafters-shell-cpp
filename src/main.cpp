#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/command_executer.h"
#include "../include/utils.h"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (inputCommand(input)) {
    std::vector<std::string> tokens = parseInputs(input);
    executeCommand(tokens);
  }
}
