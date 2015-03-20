#ifndef TFSTATEMENT_H
    #define TFSTATEMENT_H

#include "../DbContainers/DbTable.h"

class TFStatement
{
private:
    bool haveTwoColumns;
    std::string statement;
    DbColumn *columnOne;
    DbColumn *columnTwo;

    std::string value, columnNameOne, relOp;
    std::string columnNameTwo; //optional, either stock <= 5.1    or stock <= earnings i.e
    void initialize(std::string &statement, DbTable *table);

public:
    TFStatement(std::string &statement,DbTable *table){initialize(statement,table);}
    bool getResultForRow(unsigned int rowNumber);


};
#endif // TFSTATEMENT_H
