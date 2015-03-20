#include "SelectCommand.h"
#include "../Selectors/Selectors.h"
using namespace std;

#define NO_SORT 0
#define SORT_ASC 1
#define SORT_DESC 2

void SelectCommand::execute(DbDatabase *db,string command,ostream &out)
{
    vector<string> tokens = getTokens(command);

    int sortType = NO_SORT;

    if(tokens[0]!="SELECT")
        throw "Invalid command" + command;


    ConditionSelector *s;

    string selectClause=" ", sortColumn;
    vector<string> *columnList;

    int last;
    if(tokens[1] == "*")
        {
            columnList = NULL;
            last = 2;
        }
    else
    {
        columnList = new vector<string>();

        for(int i=1;tokens[i]!="FROM";i++)
            {columnList->push_back(tokens[i]);
            last = i;
            }

            last++;

    }

    DbTable *tb = db->getTableAccess(tokens[last+1]);


    if(last+2>=tokens.size())
    {
        //SIMPLE SELECT * FROM TABLE
        last = last+2;
    }

    else
     if(tokens[last+2] == "SORT")
    {
        //SELECT * FROM TABLE SORT BY COLUMN TYPE

        sortColumn = tokens[last+4];

        if(tokens[last+5] == "ASC")
            sortType = SORT_ASC;
         else
            sortType = SORT_DESC;

    }
    else
    {


     //here we have a WHERE
    bool looped = false;
    for(int i=last+3;i<tokens.size() && tokens[i]!="SORT";i++)
        {
            selectClause.append(tokens[i] + " ");
            last = i;
            looped = true;
        }

        last++;


    if(looped && last!=tokens.size())
    {
        if(tokens[last+3] == "ASC")
            sortType=SORT_ASC;
        else
            sortType=SORT_DESC;

        sortColumn=tokens[last+2];
    }

    }

    if(selectClause == " ")
        s=NULL;
    else
        s=new ConditionSelector(selectClause);


    DbTableSnapshot tbS = tb->selectRows(columnList,s);

    if(s)
        delete s;

    switch(sortType)
    {
    case SORT_ASC:
        tbS.sort(sortColumn,"ASC");
        break;
    case SORT_DESC:
        tbS.sort(sortColumn,"DESC");
        break;
    default:
        break;
    }


    tbS.output(out);

}
