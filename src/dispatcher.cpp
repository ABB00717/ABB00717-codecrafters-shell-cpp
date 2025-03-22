#include "../include/dispatcher.h"
#include <unistd.h> // for STDOUT_FILENO
#include <fcntl.h>  // for open()
#include <cstdio>

void dispatchCommands(std::vector<CommandNode*> commands) {
    if (commands.empty())
        return;

    CommandNode* cmd = commands[0];
    int savedStdout = -1;
    int outputFd = -1;

    if (!cmd->outputFile.empty()) {
        outputFd = open(cmd->outputFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputFd < 0) {
            perror("open outputfile");
            return;
        }

        savedStdout = dup(cmd->outputFd);

        dup2(outputFd, cmd->outputFd);
        close(outputFd);
    }

    runSingleCommand(cmd->args);

    if (savedStdout != -1) {
        dup2(savedStdout, cmd->outputFd);
        close(savedStdout);
    }
}