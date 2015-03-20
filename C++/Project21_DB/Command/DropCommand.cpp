#include "DropCommand.h"

#include "../DbContainers/DbColumnFactory.h"
#include "../DbContainers/DbMapTable.h"

using namespace std;

void DropCommand::execute(DbDatabase *db,string command, ostream &out)
{
    vector<string> tokens = getTokens(command);

    if(tokens[0] != "DROP")
        throw "Invalid command " + command;
    db->dropTable(tokens[2]);

    out<<"Succesfully dropped " + tokens[2] + " table.";
}

