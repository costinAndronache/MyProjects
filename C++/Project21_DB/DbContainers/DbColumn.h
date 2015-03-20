#ifndef DBCOLUMN_H
    #define DBCOLUMN_H


#include "../DbVariables/DbVariables.h"
#include<vector>
#include <algorithm>

class DbColumn
{
        void checkVariableType(DbVariable*);

protected:
    std::string name;
    std::vector<DbVariable *> values;
public:
    virtual DbType *getType() = 0;

    virtual DbVariable *getCopyItemAt(unsigned int index) = 0;
    virtual void setItemAt(unsigned int index,DbVariable *v) = 0;
    virtual void addNewItem(DbVariable *newItem) = 0;
    virtual std::string getName(){return name;}

    virtual void removeItemAt(unsigned int index)
    {
            if(index>=values.size())
        throw "Index out of bounds in deleting a value in INT column " + name;

    values.erase(find(values.begin(),values.end(),values[index]));
    }

    virtual DbVariable *getSampleFromString(std::string) = 0;

    int size(){return values.size();}

    void eraseAll()
    {
        for(int i=0; i<values.size();i++)
            delete values[i];

        values.clear();
    }

    void removeItem(DbVariable *v)
    {
        int stop = -1;
        for(int i=0;i<values.size();i++)
            if( *v == *values[i])
             {stop = i;break;}

        if(stop == -1 )
            throw "No such item to be removed from column: " + name + " " + v->getStringRepresentation();

        values.erase(find(values.begin(),values.end(),values[stop]));


    }

    ~DbColumn()
    {
        eraseAll();
    }

    virtual DbColumn *getEmptyCopy() = 0;

    virtual DbColumn *getFullCopy() = 0;
};
#endif
