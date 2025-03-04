#include <iostream>
#include <sstream>
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
  while (inputCommand(input)) {
    std::stringstream ss(input);
    std::string command;
    int arg;
    ss >> command >> arg;

    if (command == "exit" && arg == 0)
      return 0;
    
    std::cout << input << ": command not found\n";
  }
}
