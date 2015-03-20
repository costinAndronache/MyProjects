#include <iostream>
#include "DbTypes/DbTypes.h"
#include "DbVariables/DbVariables.h"
#include "BooleanEvaluator/BEOperatorFactory.h"
#include "BooleanEvaluator/BooleanEvaluator.h"
#include "DbContainers/DbColumns.h"

#include "DbContainers/DbMapTable.h"
#include "Selectors/TFStatement.h"
#include "Selectors/Selectors.h"

#include "DbContainers/DbTableSnapshot.h"
#include "Selectors/Selectors.h"
#include <cstdlib>

#include "Command/Commands.h"
#include "Command/CommandFactory.h"

#include "DbContainers/DbMapDatabase.h"

using namespace std;

string intToString(int x)
{
    char vx[200];
    itoa(x,vx,10);

    return string(vx);
}

int main()
{

    DbMapDatabase myDatabase("myDbOne");

    string command="";
    char cstr[1024];

    myDatabase.loadFromFile("DbRead.txt");

    /*
    SelectCommand s;
    try{
    s.execute(&myDatabase,"SELECT * FROM tableName1 WHERE colNameOne>22",cout);
    }
    catch(string e)
    {
        cout<<e;
    }

    CreateCommand c;
    c.execute(&myDatabase,"CREATE TABLE myTB ( ii INT ss STRING ) ",cout);
    InsertCommand i;

    i.execute(&myDatabase,"INSERT INTO myTB ii ss VALUES 25 Hello25 ",cout);
    i.execute(&myDatabase,"INSERT INTO myTB ii ss VALUES 26 Hello26 ",cout);
    i.execute(&myDatabase,"INSERT INTO myTB ii ss VALUES 27 Hello27 ",cout);

    cout<<"\n";
    SelectCommand s;
    try{
    s.execute(&myDatabase,"SELECT * FROM myTB WHERE ii>=5 AND ii>=4 SORT BY ii DESC ",cout);
    s.execute(&myDatabase,"SELECT * FROM myTB SORT BY ss ASC ",cout);
    }
    catch(string ex)
    {
        cout<<ex;
    }
    cout<<'\n';


    *
    /


    do
    {

        cin.getline(cstr,1023);

        command = string(cstr);

        if(command == "QUIT")
            break;

        if(command == "SAVE")
        {
            myDatabase.saveToFile("DbSave.txt");
            cout<<"Succesfully saved.\n";
            continue;
        }

        Command *cmd = CommandFactory::getCommand(command);
        try
        {
        cmd->execute(&myDatabase,command,cout);
        }
        catch(string ex)
        {
            cout<<'\n'<<ex<<'\n';
        }

        cout<<'\n';

        delete cmd;

    }while(true);
    */



    InsertCommand i;
    i.execute(&myDatabase,"INSERT INTO myTable myINT mySTRING VALUES 1 haz",cout);

    try{
    SelectCommand s;
    s.execute(&myDatabase,"SELECT * FROM myTable",cout);
    }
    catch(exception ex)
    {
        //cout<<ex;
    }

    myDatabase.saveToFile("DbSave.txt");



    cout<<BooleanEvaluator::evaluate((" F OR F "));
    return 0;
}
