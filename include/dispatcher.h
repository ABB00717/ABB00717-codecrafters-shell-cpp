#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "parser.h"
#include <vector>
#include "executor.h"

void dispatchCommands(std::vector<CommandNode*> commands);

#endif