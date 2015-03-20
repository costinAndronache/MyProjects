#include "DbMapTable.h"
#include <algorithm>
#include <iostream>
using namespace std;


void DbMapTable::addNewColumn(DbColumn *newColumn)
{
    columnMap[newColumn->getName()] = newColumn;

    for(int i=0;i<rows;i++)
        newColumn->addNewItem(new DbNullVar);
}

DbColumn *DbMapTable::getColumnAccess(string columnName)
{
    ColumnMap::iterator it = columnMap.find(columnName);

    if(it == columnMap.end())
        throw "No such column: " + columnName + " in table: " + name + " on getColumnAccess()";

    return it->second;
}

void DbMapTable::removeColumn(string columnName)
{

    ColumnMap::iterator it = columnMap.find(columnName);

    if(it == columnMap.end())
        throw "No such column: " + columnName + " in table: " + name + " on removeColumn()";

    DbColumn *c = it->second;
    columnMap.erase(it);

    delete c;

}

void DbMapTable::insertInto(vector<string> &columnList, vector<DbVariable*> &valueList)
{

    ++rows;

    ColumnMap::iterator it;
    DbColumn *c;

    for(unsigned int i=0;i<columnList.size();i++)
    {
        it = columnMap.find(columnList[i]);
            if(it == columnMap.end())
        throw "No such column: " + columnList[i] + " in table: " + name + " on insertInto()";

        c=it->second;
        c->addNewItem(valueList[i]);
    }

    for(ColumnMap::iterator it = columnMap.begin();it!=columnMap.end();it++)
    {

        vector<string>::iterator vit = find(columnList.begin(),columnList.end(),it->first);

        if(vit==columnList.end())
            it->second->addNewItem(new DbNullVar);

    }

}

DbTableSnapshot DbMapTable::selectRows(vector<string> *columnList,Selector *S)
{
    DbTableSnapshot tbS;

    if(!S)
    {

        if(!columnList)
        {
            for(ColumnMap::iterator it=columnMap.begin();it!=columnMap.end();it++)
                tbS.addNewColumn(it->second->getFullCopy());
        }
        else
        for(int i=0;i<columnList->size();i++)
        {
            ColumnMap::iterator it = columnMap.find(columnList->at(i));
            if(it == columnMap.end())
                throw "No such column: " + columnList->at(i) + " on selecting from " + name;

            tbS.addNewColumn(it->second->getFullCopy());
        }

    }
    else
    {
        vector<unsigned int> rows = S->getRowsThatConform(this);


        if(!columnList)
        {
            for(ColumnMap::iterator it = columnMap.begin();it!=columnMap.end();it++)
            {
            DbColumn *c = it->second->getEmptyCopy();

            for(int k=0;k<rows.size();k++)
                c->addNewItem(it->second->getCopyItemAt(rows[k]));

            tbS.addNewColumn(c);
            }
        }
        else
        for(int i=0;i<columnList->size();i++)
        {
            ColumnMap::iterator it = columnMap.find(columnList->at(i));
            if(it == columnMap.end())
                throw "No such column: " + columnList->at(i) + " on selecting from " + name;

            DbColumn *c = it->second->getEmptyCopy();

            for(int k=0;k<rows.size();k++)
                c->addNewItem(it->second->getCopyItemAt(rows[k]));

            tbS.addNewColumn(c);
        }

    }

    return tbS;

}

void DbMapTable::deleteRows(Selector *S)
{
    vector<unsigned int> rowList = S->getRowsThatConform(this);

    DbVariable **values = new DbVariable*[rowList.size()];
    int total = 0;



    for(ColumnMap::iterator it=columnMap.begin();it!=columnMap.end();it++)
    {
      for(int k=0;k<rowList.size();k++)
         {
             DbColumn *c = it->second;
             DbVariable *v = c->getCopyItemAt(rowList[k]);

             values[k] = v;


             //cout<<"Must delete "<<v->getStringRepresentation()<<"\n";
         }

     for(int i=0;i<rowList.size();i++)
        {
            DbVariable *v = values[i];
            it->second->removeItem(v);

            delete v;
        }

    }

    rows -=rowList.size();

    delete[] values;

}

DbMapTable :: ~DbMapTable()
{
    for(ColumnMap::iterator it=columnMap.begin();
        it!=columnMap.end();
        it++)

        {
            delete it->second;

        }

    columnMap.clear();
}

vector<string> DbMapTable::getColumnNames()
{
    vector<string> result;
    for(ColumnMap::iterator it = columnMap.begin();it!=columnMap.end();it++)
        result.push_back(it->first);

    return result;
}
