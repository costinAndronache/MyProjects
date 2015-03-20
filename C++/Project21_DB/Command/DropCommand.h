#ifndef DROPCOMMAND_H
    #define DROPCOMMAND_H

#include "Command.h"

class DropCommand : public Command
{
public:
    void execute(DbDatabase *db,std::string command, std::ostream &out);
};
#endif // DROPCOMMAND_H
