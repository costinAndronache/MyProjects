#ifndef DBTABLESNAPSHOT_H
    #define DBTABLESNAPSHOT_H

#include "DbColumn.h"

class DbTableSnapshot
{
private:
    std::vector<DbColumn*> columns;

    void sortAscendent(std::string byColumn);
    void sortDescendent(std::string byColumn);
    void swapRows(int i, int j);
public:
    void addNewColumn(DbColumn *newColumn);
    std::ostream& output(std::ostream &out);
    void sort(std::string byColumn,std::string how);
    ~DbTableSnapshot();

};
#endif // DBTABLESNAPSHOT_H
