#pragma once
#include <exception>
#include <string>
#include <vector>
#define SIZE_OF_MULTIMAP 13     // TOTAL SIZE OF THE MULTI MAP
#define ADDRESS_MAP_OF_VALUES 5 // SIZE_OF_MULTIMAP - ADDRESS_MAP_OF_VALUES = NUMBER OF SLOTS USED ONLY FOR COLLISIONS (CELLAR)
                                // No coalescing can occur until the cellar is exhausted
typedef struct _ADT_MultiMap_Pair {
    std::string Key;
    std::string Value;
} ADT_MultiMap_Pair;

class ADTMultiMapIterator;

class ADTMultiMap
{   

    ADT_MultiMap_Pair * Array;                                          // Array of cells
    int * Next;                                                         // Array of positions to the next cells
    int M;                                                              // Size of the MultiMap
    int FirstEmpty;                                                     // Position of the first empty cell
    int Count;                                                          // Number of elements from the MultiMap
    int (ADTMultiMap::*HashFunc)(const std::string & Key) const;        // Pointer to the Hash Function

    int divisionHash(const std::string & Key) const;                    // Hash Function

    void changeFirstEmpty();                                            // update FirstEmpty

    ADTMultiMapIterator* MyIterator;
public:

    ADTMultiMap();
    ~ADTMultiMap();

    void insert(const std::string & Key, const std::string & Value);
    void clear();
    void deletePair(const std::string & Key, const std::string & Value);
    void deleteKey(const std::string & Key);

    void search(const std::string & Key, std::vector<std::string> & Values) const;
    bool containsPair(const std::string & Key, const std::string & Value)   const;
    int size()                                                              const;
    int count()                                                             const;
    bool isEmpty()                                                          const;
    ADT_MultiMap_Pair* getArray()                                           const;

    void createIterator();
    ADTMultiMapIterator* getIterator();

};

#include "ADTMultiMapIterator.h"

