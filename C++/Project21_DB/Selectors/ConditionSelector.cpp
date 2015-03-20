#include "ConditionSelector.h"
#include <cstring>
#include <iostream>
using namespace std;

extern void preprocess(char cstr[]);

vector<string> ConditionSelector::getTokens(string s)
{
    char *cstr = new char[s.length()+1];

    strcpy(cstr,s.c_str());

    strtok(cstr," ");

    vector<string> result;

    char *p=cstr;

    while(p)
    {
        result.push_back(string(p));
        p = strtok(NULL," ");
    }

    delete[] cstr;

    return result;
}

vector<unsigned int> ConditionSelector::getRowsThatConform(DbTable *table)
{

    vector<string> tokenList = getTokens(condition);

    booleanExpression = " ";

    vector<unsigned int> result;

    for(int i=0;i<table->getRows();i++)
    {
        booleanExpression="";
        for(int k=0;k<tokenList.size();k++)
        {
            char c[255];
            strcpy(c,tokenList[k].c_str());
            preprocess(c);
            string token = string(c);

            if( token == "(" || token == ")" || token=="AND" || token=="OR" || token=="NOT")
                booleanExpression.append(token + " ");
            else
            {
                TFStatement *tfs;

                TFStmtMap::iterator it = tfMap.find(token);

                if(it == tfMap.end())
                {
                    tfs = new TFStatement(token,table);
                    tfMap[token]=tfs;

                }
                else
                    tfs = it->second;

                if(tfs->getResultForRow(i))
                    booleanExpression.append("T ");
                else
                    booleanExpression.append("F ");
            }
        }

        //cout<<"The expression for row "<<i<<" is: "<<booleanExpression<<'\n';
        if(BooleanEvaluator::evaluate(booleanExpression))
            result.push_back(i);

    }

    //cout<<"We have "<<result.size()<<" rows that are ok!";
    return result;

}
