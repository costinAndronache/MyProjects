#ifndef DUMMYSELECTOR_H
    #define DUMMYSELECTOR_H

#include "Selector.h"

class DummySelector : public Selector
{

public:
    std::vector<unsigned int> getRowsThatConform(DbTable *table)
    {
        std::vector<unsigned int> myVec;

        myVec.push_back(0);
        myVec.push_back(1);
        myVec.push_back(2);
        myVec.push_back(3);

        return myVec;
    }
};
#endif
