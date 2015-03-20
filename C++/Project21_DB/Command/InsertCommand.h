#ifndef INSERTCOMMAND_H
    #define INSERTCOMMAND_H


#include "Command.h"

class InsertCommand : public Command
{


public:
    void execute(DbDatabase *,std::string,std::ostream&);
};
#endif // INSERTCOMMAND_H
