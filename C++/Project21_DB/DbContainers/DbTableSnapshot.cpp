#include "DbTableSnapshot.h"
#include <algorithm>
using namespace std;

void DbTableSnapshot::addNewColumn(DbColumn *newColumn)
{
    columns.push_back(newColumn);
}

void DbTableSnapshot::sort(string columnName, string how)
{
    if(how == "ASC")
        sortAscendent(columnName);
    else
        sortDescendent(columnName);

}

void DbTableSnapshot::sortAscendent(string byColumn)
{

    unsigned int columnIndex;

    for(int i=0;i<columns.size();i++)
        if(columns[i]->getName() == byColumn)
    {
        columnIndex = i;
        break;
    }

    for(int i=0;i<columns[columnIndex]->size()-1;i++)
        for(int j=i+1;j<columns[columnIndex]->size();j++)
        {
            DbColumn *c = columns[columnIndex];

            DbVariable *vi = c->getCopyItemAt(i);
            DbVariable *vj = c->getCopyItemAt(j);

            if(*vi > *vj)
                swapRows(i,j);

        }
}

void DbTableSnapshot::sortDescendent(string byColumn)
{

    unsigned int columnIndex;

    for(int i=0;i<columns.size();i++)
        if(columns[i]->getName() == byColumn)
    {
        columnIndex = i;
        break;
    }

    for(int i=0;i<columns[columnIndex]->size()-1;i++)
        for(int j=i+1;j<columns[columnIndex]->size();j++)
        {
            DbColumn *c = columns[columnIndex];

            DbVariable *vi = c->getCopyItemAt(i);
            DbVariable *vj = c->getCopyItemAt(j);

            if(*vi < *vj)
                swapRows(i,j);


        }
}

ostream& DbTableSnapshot::output(ostream &out)
{
    string newLine="\n";
    string tab="\t";

    for(int i=0; i<columns.size(); i++)
        out<<columns[i]->getName()<<tab;

    out<<newLine;

    for(int i=0;i<columns[0]->size();i++)
    {
        for(int j=0;j<columns.size();j++)
        {
            DbColumn *c = columns[j];
            DbVariable *v = c->getCopyItemAt(i);
            out<<v->getStringRepresentation()<<tab;

        }
        out<<newLine;

    }

    return out;
}

DbTableSnapshot::~DbTableSnapshot()
{
    for(int i=0;i<columns.size();i++)
        delete columns[i];
}

void DbTableSnapshot::swapRows(int i, int j)
{

    for(int k=0;k<columns.size();k++)
        {

                 DbColumn *c = columns[k];
                 DbVariable *vi = c->getCopyItemAt(i);
                 DbVariable *vj = c->getCopyItemAt(j);


                DbVariable *aux = vi;
                vi = vj;
                vj = aux;

                c->setItemAt(i,vi);
                c->setItemAt(j,vj);

        }

}
