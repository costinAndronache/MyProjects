#ifndef COMMANDFACTORY_H
    #define COMMANDFACTORY_H

#include "Commands.h"

class CommandFactory
{
public:
    static Command *getCommand(std::string);
};
#endif // COMMANDFACTORY_H
