#ifndef COMMAND_H
    #define COMMAND_H

#include<iostream>
#include<string>
#include<vector>
#include "../DbContainers/DbDatabase.h"

class Command
{
protected:

    static std::vector<std::string> getTokens(std::string);
public:
    virtual void execute(DbDatabase *db,std::string,std::ostream&) = 0;
};


#endif // COMMAND_H
