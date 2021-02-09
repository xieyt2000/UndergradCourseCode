#include "square.h"

bool square::testContaHappen()
{
    if(immueContaAfterSplit)
    {
        immueContaAfterSplit=false;
        return  false;

    }
    for(auto i : contaminateID)
    {
        if(i!=liquidId) return true;
    }
    return  false;
}
