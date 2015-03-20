#ifndef SELECTCOMMAND_H
    #define SELECTCOMMAND_H

#include "Command.h"

class SelectCommand : public Command
{
public:
    void execute(DbDatabase *db,std::string,std::ostream&);
};
#endif // SELECTCOMMAND_H
