#ifndef DELETECOMMAND_H
    #define DELETECOMMAND_H

#include "Command.h"

class DeleteCommand : public Command
{
public:
    void execute(DbDatabase*,std::string,std::ostream&);
};
#endif // DELETECOMMAND_H
