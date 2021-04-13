#pragma once
#include "ADTMultiMap.h"
class ADTMultiMapIterator
{
private:
    ADTMultiMap* mHashTable;
    int currentPosition;
    bool valid();
public:
    ADTMultiMapIterator(ADTMultiMap* mHashTable);
    bool next();
    std::string& getCurrentKey();
    std::string& getCurrentValue();
};

