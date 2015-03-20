#include "CommandFactory.h"
using namespace std;

Command *CommandFactory::getCommand(string command)
{
    const char *p = command.c_str();

    char v[3]={*p,*(p+1),'\0'};

    string s = string(v);

    //cout<<s;

    if(s == "IN")
        return new InsertCommand;

    if(s == "CR")
        return new CreateCommand;

    if( s == "DR")
        return new DropCommand;

    if( s == "AL")
        return new AlterCommand;

    if( s == "SE")
        return new SelectCommand;

    if( s == "DE")
        return new DeleteCommand;


}
