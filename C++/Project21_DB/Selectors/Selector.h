#ifndef SELECTOR_H
    #define SELECTOR_H


class DbTable;

class Selector
{

public:
    virtual std::vector<unsigned int> getRowsThatConform(DbTable *table) = 0;


};
#endif // SELECTOR_H
