#include <iostream>
#include <string>

bool inputCommand(std::string& input) {
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
  while (inputCommand(input))
    std::cout << input << ": command not found\n";
}
