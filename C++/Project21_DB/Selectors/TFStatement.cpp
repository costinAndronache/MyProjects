#include "TFStatement.h"
#include<cstring>
#include <iostream>
using namespace std;

void preprocess(char cstr[])
{
    int i=0;
    while(cstr[i] == ' ')
        i++;

    strcpy(cstr,cstr+i);
}
void TFStatement::initialize(string &statement, DbTable *table)
{
    this->statement = statement;

    char cstr[256];
    strcpy(cstr,statement.c_str());

    int i=0;
    preprocess(cstr);

    while(isalpha(cstr[i]))
        i++;

    char cstrColumnNameOne[256];
    for(int j=0;j<i;j++)
        cstrColumnNameOne[j] = cstr[j];

    cstrColumnNameOne[i] ='\0';

    columnNameOne = string(cstrColumnNameOne);

    char cstrRelOp[10];
    cstrRelOp[0] = cstr[i];

    if(cstr[i+1] == '=')
        {
            cstrRelOp[1]=cstr[i+1];
            cstrRelOp[2]='\0';
            i=i+2;
        }
        else
            {
                cstrRelOp[1]='\0';
                i++;
            }

    relOp = string(cstrRelOp);

    if(isdigit(cstr[i]))
        {
            haveTwoColumns = false;
            value = string(cstr+i);
        }
        else
            if (cstr[i] == '\'')
        {
            char str[256];
            int j = i+1;
            while(cstr[j]!='\'')
            {
                str[j-i-1]=cstr[j];
                j++;
            }
            str[j]='\0';

            haveTwoColumns=false;
            value = string(str);
        }
        else
        {
            haveTwoColumns = true;
            columnNameTwo = string(cstr+i);
        }


    columnOne = table->getColumnAccess(columnNameOne);

    if(haveTwoColumns)
        columnTwo = table->getColumnAccess(columnNameTwo);

    //cout<<columnNameOne<<" --- "<<relOp<<" --- "<<value;
}

bool TFStatement::getResultForRow(unsigned int rowNumber)
{

    DbVariable *leftValue, *rightValue;

    leftValue = columnOne->getCopyItemAt(rowNumber);

    if(haveTwoColumns)
        rightValue = columnTwo->getCopyItemAt(rowNumber);
    else
        rightValue = columnOne->getSampleFromString(value);

    if(relOp == "==")
        return *rightValue==*leftValue;

    if(relOp == ">")
        return *leftValue>*rightValue;

    if(relOp == ">=")
        return *leftValue>=*rightValue;

    if(relOp == "<")
        return *leftValue<*rightValue;

    if(relOp == "<=")
        return *leftValue<=*rightValue;

    if(relOp == "!=")
        return *leftValue!=*rightValue;

    delete leftValue;
    delete rightValue;

    throw "Undefined operator " + relOp + " in statement: " + statement;

}
