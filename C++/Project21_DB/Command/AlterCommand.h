#ifndef ALTERCOMMAND_H
    #define ALTERCOMMAND_H

#include "Command.h"

class AlterCommand : public Command
{
public:
    void execute(DbDatabase *db,std::string,std::ostream&);
};
#endif // ALTERCOMMAND_H
