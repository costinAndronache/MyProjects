#include "DbMapDatabase.h"
#include<string>

using namespace std;

void DbMapDatabase::addNewTable(DbTable *newTable)
{
    tbMap[newTable->getName()]=newTable;
}

void DbMapDatabase::dropTable(string tbName)
{
    TBMap::iterator it = tbMap.find(tbName);

    if(it == tbMap.end())
        throw "No such table to delete " + tbName;

    DbTable *t = it->second;

    tbMap.erase(it);

    delete t;
}

DbTable *DbMapDatabase::getTableAccess(string tbName)
{
        TBMap::iterator it = tbMap.find(tbName);

    if(it == tbMap.end())
        throw "No such table to access " + tbName;

    DbTable *t = it->second;

    return t;
}

DbMapDatabase::~DbMapDatabase()
{
    for(TBMap::iterator it=tbMap.begin();it!=tbMap.end();it++)
    {
        delete it->second;
    }
}

void DbMapDatabase::loadFromFile(string file)
{
    int numOfTables;

    ifstream f(file.c_str());

    f>>numOfTables;

    for(int i =1; i<=numOfTables;i++)
    {
        string tbName;
        int numOfColumns;
        int numOfRows;


        f>>tbName>>numOfColumns>>numOfRows;

        DbTable *tb = new DbMapTable(tbName);

        for(int j = 1; j<= numOfColumns; j++)
        {
            string columnName;
            string typeID;

            f>>columnName>>typeID;

            string value;

            DbColumn *c = DbColumnFactory::getColumnOfType(typeID,columnName);

            for(int k=1;k<=numOfRows;k++)
            {

                f>>value;
                DbVariable *v = c->getSampleFromString(value);
                c->addNewItem(v);
            }

            tb->addNewColumn(c);

        }

        tb->setNumOfRows(numOfRows);

        addNewTable(tb);

    }

    f.close();
}

void DbMapDatabase::saveToFile(string file)
{
    unsigned int ebp1, ebp2;

    asm volatile ("mov %%ebp, %0"
         : "=r" (ebp1)
         :
         : "%ebx");


    ofstream g(file.c_str());

    g<<tbMap.size()<<'\n';

    for(TBMap::iterator it = tbMap.begin();it!=tbMap.end();it++)
    {
        DbTable *tb = it->second;

        g<<tb->getName()<<' '<<tb->getNumberOfColumns()<<' '<<tb->getRows()<<'\n';

        vector<string> columns = tb->getColumnNames();

        for(int i=0;i<columns.size();i++)
        {
            string cName = columns[i];

            DbColumn *c = tb->getColumnAccess(cName);

            g<<c->getName()<<' '<<c->getType()->getID()<<'\n';


            for(int k=0;k<tb->getRows();k++)
            {

                    asm volatile ("mov %%ebp, %0"
         : "=r" (ebp1)
         :
         : "%ebx");


                DbVariable *v = c->getCopyItemAt(k);
                g<<v->getStringRepresentation()<<'\n';

                delete v;

            }



        }

        g<<'\n';

    }


}





