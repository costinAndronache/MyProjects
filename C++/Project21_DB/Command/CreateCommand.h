#ifndef CREATECOMMAND_H
    #define CREATECOMMAND_H

#include "Command.h"

class CreateCommand : public Command
{
public:
    void execute(DbDatabase *db,std::string command, std::ostream &out);


};
#endif // CREATECOMMAND_H
