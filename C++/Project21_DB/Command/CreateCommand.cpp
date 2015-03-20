#include "CreateCommand.h"
#include "../DbContainers/DbColumnFactory.h"
#include "../DbContainers/DbMapTable.h"
using namespace std;

void CreateCommand::execute(DbDatabase *db,string command,ostream &out)
{

    vector<string> tokens = getTokens(command);

    if(tokens[0] != "CREATE")
     throw "Invalid command " + command;

    DbTable *tb;
    DbColumn *c;

    int debugI = tokens.size();
    string debugS = tokens[2];
    tb = new DbMapTable(tokens[2]);

    for(int i = 4; i<tokens.size()-1;i=i+2)
    {
        c = DbColumnFactory::getColumnOfType(tokens[i+1],tokens[i]);
        tb->addNewColumn(c);

    }

    db->addNewTable(tb);

    out<<"Succesfully created. ";
}
