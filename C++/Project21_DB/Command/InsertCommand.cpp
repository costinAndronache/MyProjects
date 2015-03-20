#include "InsertCommand.h"

using namespace std;
void InsertCommand::execute(DbDatabase *db,string command,ostream &out)
{

    vector<string> tokens = getTokens(command);

    if(tokens[0]!="INSERT")
        throw "Invalid command " + command;

    DbTable *tb = db->getTableAccess(tokens[2]);

    vector<string> columnList;
    vector<string> valueList;

    int i;
    for(i=3; tokens[i]!="VALUES";i++)
        columnList.push_back(tokens[i]);

    for(i=i+1;i<tokens.size();i++)
        valueList.push_back(tokens[i]);


    vector<DbVariable*> values;

    for(int i=0;i<columnList.size();i++)
    {
        DbColumn *c = tb->getColumnAccess(columnList[i]);

        DbVariable *v = c->getSampleFromString(valueList[i]);

        values.push_back(v);

    }

    tb->insertInto(columnList,values);

    out<<"Succesfully added the new values.";
}
