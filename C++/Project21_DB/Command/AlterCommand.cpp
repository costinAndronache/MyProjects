#include "AlterCommand.h"

#include "../DbContainers/DbColumnFactory.h"

using namespace std;
void AlterCommand::execute(DbDatabase *db,string command,ostream &out)
{


    vector<string> tokens = getTokens(command);

    if(tokens[0]!= "ALTER")
        throw "Invalid command " + command;

    DbTable *tb = db->getTableAccess(tokens[2]);

    if(tokens[3] == "ADD")
    {
        for(int i=5;i<tokens.size()-1;i=i+2)
        {
            DbColumn *c = DbColumnFactory::getColumnOfType(tokens[i+1],tokens[i]);

            tb->addNewColumn(c);
        }

        out<<"Succesfully added the new columns.";
    }
    else
        {
            tb->removeColumn(tokens[4]);
            out<<"Succesfully removed " + tokens[4] + " from table " + tb->getName();
        }
}
