#include "../include/utils.h"
#include <cctype>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <set>
#include <string>

bool inputCommand(std::string& input) {
    input.clear();
    
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c;
    std::cout << "$ " << std::flush;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n') {
            std::cout << std::endl;
            break;
        } else if (c == '\t') {
            std::string completed = tabComplete(input);
            if (!completed.empty()) {
                std::string suffix = completed.substr(input.length());
                input = completed;
                std::cout << suffix << std::flush;
            }
        } else if (c == 127 || c == '\b') {
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else {
            input += c;
            std::cout << c << std::flush;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return !input.empty();
}

std::string tabComplete(const std::string& input) {
    static int multiTabCount = 0;
    static std::string lastPrefix;
    std::string prefix = input;

    std::set<std::string> candidates;

    for (const auto& cmd : validCommands) {
        if (cmd.find(prefix) == 0) {
            candidates.insert(cmd);
        }
    }

    std::string path_env = std::getenv("PATH");
    std::stringstream ss(path_env);
    std::string path;

    while (std::getline(ss, path, ':')) {
        try {
            if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
                continue;
            }
            
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                std::string filename = entry.path().filename().string();
                if (filename.find(prefix) == 0) {
                    candidates.insert(filename);
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            continue;
        }
    }

    if (candidates.empty()) {
        std::cout << "\a";
        multiTabCount = 0;
        lastPrefix.clear();
        return "";
    }

    std::string commonPrefix = getLongestCommonPrefix(candidates);
    if (commonPrefix.size() > input.size()) {
        multiTabCount = 0;
        lastPrefix.clear();
        return commonPrefix;
    }
    
    if (candidates.size() == 1) {
        multiTabCount = 0;
        lastPrefix.clear();
        return *candidates.begin() + " ";
    }

    if (prefix != lastPrefix) {
        multiTabCount = 1;
        lastPrefix = prefix;
        std::cout << "\a" << std::flush;
    } else {
        multiTabCount++;
    }

    if (multiTabCount == 2) {
        std::cout << std::endl;
        for (const auto& cand : candidates) {
            std::cout << cand << "  ";
        }
        std::cout << std::endl << "$ " << prefix << std::flush;
        multiTabCount = 0;
    }

    return prefix;
}

std::string getPath(std::string command) {
    try {
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
    } catch (...) {
        return "";
    }

    return "";
}

std::string getLongestCommonPrefix(const std::set<std::string>& candidates) {
    if (candidates.empty()) return "";

    auto it = candidates.begin();
    std::string prefix = *it;
    ++it;

    while (it != candidates.end()) {
        const std::string& current = *it;
        size_t j = 0;

        while (j < prefix.size() && j < current.size() && prefix[j] == current[j]) {
            j++;
        }

        prefix = prefix.substr(0, j);
        if (prefix.empty()) break;

        ++it;
    }

    return prefix;
}
