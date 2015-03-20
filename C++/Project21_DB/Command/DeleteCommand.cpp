#include "DeleteCommand.h"
#include "../Selectors/Selectors.h"
using namespace std;
void DeleteCommand::execute(DbDatabase *db,string command,ostream& out)
{
    vector<string> tokens = getTokens(command);

    DbTable *tb;

    if(tokens[0]!="DELETE")
        throw "Invalid command " + command;

    tb = db->getTableAccess(tokens[2]);

    string selectClause=" ";

    for(int i=4;i<tokens.size();i++)
        selectClause.append(tokens[i] + " ");

    Selector *s = new ConditionSelector(selectClause);

    tb->deleteRows(s);

    delete s;

    out<<"Succesfully deleted.";
}
