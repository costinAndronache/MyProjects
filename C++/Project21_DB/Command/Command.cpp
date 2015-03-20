#include "Command.h"
#include <cstring>
using namespace std;

vector<string> Command::getTokens(string s)
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

