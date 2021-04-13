#include "ADTMultiMap.h"


#include <iostream>

int ADTMultiMap::divisionHash(const std::string& Key) const
{
    int sum = 0;
    for (char i : Key)
        sum += i;
    return sum % ADDRESS_MAP_OF_VALUES;
} // O(n) where n is the length of the key

void ADTMultiMap::changeFirstEmpty()
{
    while (this->FirstEmpty >= 0 && !this->Array[this->FirstEmpty].Key.empty())
    {
        this->FirstEmpty -= 1;
    }
} // O(M)

ADTMultiMap::ADTMultiMap() : MyIterator(nullptr)
{
    this->Array = new ADT_MultiMap_Pair[SIZE_OF_MULTIMAP];
    if (this->Array == nullptr)
        throw std::exception("Array #1 allocation failed.");
    this->Count = 0;
    this->Next = new int[SIZE_OF_MULTIMAP];
    if (this->Next == nullptr)
        throw std::exception("Array #2 allocation failed.");

    this->M = SIZE_OF_MULTIMAP;
    this->FirstEmpty = M - 1;
    this->HashFunc = &ADTMultiMap::divisionHash;
} // theta(1)

ADTMultiMap::~ADTMultiMap()
{
    delete[] this->Next;
    delete[] this->Array;
    delete this->MyIterator;
} // theta(1)

void ADTMultiMap::insert(const std::string& Key, const std::string& Value)
{
    if (Key.empty())
        throw std::exception("The key must be a valid string.");
    if (Value.empty())
        throw std::exception("The value must be a valid string.");
    int mKeyPosition = (*this.*HashFunc)(Key);
    if (this->Array[mKeyPosition].Key.empty())
    {
        this->Array[mKeyPosition].Key = Key;
        this->Array[mKeyPosition].Value = Value;
        this->Next[mKeyPosition] = -1;
        this->Count += 1;
        return;
    }
    this->changeFirstEmpty();
    if (this->FirstEmpty == -1)
    {
        int* newNextArr = new int[this->M * 2];
        delete[] this->Next;
        this->Next = newNextArr;

        ADT_MultiMap_Pair* newArr = new ADT_MultiMap_Pair[this->M * 2];

        const int lastSize = this->M;
        ADT_MultiMap_Pair* lastArr = this->Array;

        this->M *= 2;
        this->Array = newArr;
        this->FirstEmpty = M - 1;
        this->Count = 0;
        for (int i = 0; i < lastSize; i++) // rehash every cell
        {
            if (!lastArr[i].Key.empty())
            {
                this->insert(lastArr[i].Key, lastArr[i].Value);
            }
        }
        delete[] lastArr; // no need for that array

        mKeyPosition = (*this.*HashFunc)(Key);
        if (this->Array[mKeyPosition].Key.empty())
        {
            this->Array[mKeyPosition].Key = Key;
            this->Array[mKeyPosition].Value = Value;
            this->Next[mKeyPosition] = -1;
            this->Count += 1;
            return;
        }
        this->changeFirstEmpty();
    }
    int current = mKeyPosition;
    while (this->Next[current] != -1)
    {
        current = this->Next[current];
    }

    this->Array[this->FirstEmpty].Key = Key;
    this->Array[this->FirstEmpty].Value = Value;

    this->Next[this->FirstEmpty] = -1;
    this->Next[current] = this->FirstEmpty;
    this->Count += 1;
} // theta(1) on average, theta(M) - worst case

void ADTMultiMap::search(const std::string& Key, std::vector<std::string>& Values) const
{
    int currentPos = (*this.*HashFunc)(Key);

    while (currentPos != -1 && !this->Array[currentPos].Key.empty())
    {
        if (this->Array[currentPos].Key == Key)
        {
            Values.push_back(this->Array[currentPos].Value);
        }
        currentPos = this->Next[currentPos];
    }
} // theta(n) where n is the number of occurs

void ADTMultiMap::deletePair(const std::string& Key, const std::string& Value)
{
    if (Key.empty())
        throw std::exception("The key must be a valid string.");
    if (Value.empty())
        throw std::exception("The value must be a valid string.");
    int mKeyPos = (*this.*HashFunc)(Key);
    int lastPosition = -1;
    while (mKeyPos != -1 && !this->Array[mKeyPos].Key.empty())
    {
        if (this->Array[mKeyPos].Key == Key && this->Array[mKeyPos].Value == Value)
        {
            this->Count -= 1;
            if(this->Next[mKeyPos] == -1)
            {
                this->Array[mKeyPos].Key.clear();
            }else
            {
                this->Array[mKeyPos].Key = this->Array[this->Next[mKeyPos]].Key;
                this->Array[mKeyPos].Value = this->Array[this->Next[mKeyPos]].Value;
                if (lastPosition != -1)
                {
                    this->Next[lastPosition] = mKeyPos;
                }
                this->Array[this->Next[mKeyPos]].Key.clear();
                this->Array[this->Next[mKeyPos]].Value.clear();
                if (this->Array[mKeyPos].Key.empty())
                    this->Next[mKeyPos] = -1;
                else
                    this->Next[mKeyPos] = this->Next[this->Next[mKeyPos]];
            }
            return;

        }
        lastPosition = mKeyPos;
        mKeyPos = this->Next[mKeyPos];
    }
    throw std::exception("The pair does not exists.");
} // theta(1) in most cases / theta(n), where n is the number of duplicates

void ADTMultiMap::deleteKey(const std::string& Key)
{
    if (Key.empty())
        throw std::exception("The key must be a valid string.");
    int mKeyPos = (*this.*HashFunc)(Key);
    int lastPosition = -1;
    bool deleted = false;
    while (mKeyPos != -1 && !this->Array[mKeyPos].Key.empty())
    {
        if (this->Array[mKeyPos].Key == Key)
        {
            this->Count -= 1;
            deleted = true;
            if (this->Next[mKeyPos] == -1)
            {
                this->Array[mKeyPos].Key.clear();
            }
            else
            {
                this->Array[mKeyPos].Key = this->Array[this->Next[mKeyPos]].Key;
                this->Array[mKeyPos].Value = this->Array[this->Next[mKeyPos]].Value;
                if (lastPosition != -1)
                {
                    this->Next[lastPosition] = this->Next[this->Next[mKeyPos]];
                }
                this->Array[this->Next[mKeyPos]].Key.clear();
                this->Array[this->Next[mKeyPos]].Value.clear();
                lastPosition = this->Next[mKeyPos];
                if (this->Array[mKeyPos].Key.empty())
                    this->Next[mKeyPos] = -1;
                else
                    this->Next[mKeyPos] = this->Next[this->Next[mKeyPos]];
            }
           
        }else{
            mKeyPos = this->Next[mKeyPos];
            lastPosition = mKeyPos;
        }
        
    }
    if (!deleted)
        throw std::exception("The category does not exists.");
} // theta(n) - n number of values with the key = Key

int ADTMultiMap::count() const
{
    return this->Count;
} // theta(1)
int ADTMultiMap::size() const
{
    return this->M;
} // theta(1)
bool ADTMultiMap::isEmpty() const
{
    return this->Count == 0;
} // theta(1)

void ADTMultiMap::clear()
{
    delete[] this->Array;
    delete[] this->Next;

    this->M = SIZE_OF_MULTIMAP;
    this->Count = 0;
    this->FirstEmpty = M - 1;

    this->Array = new ADT_MultiMap_Pair[SIZE_OF_MULTIMAP];
    this->Next = new int[SIZE_OF_MULTIMAP];
    if (this->Array == nullptr)
        throw std::exception("Failed to allocate memory for 'this->Array'");
    if (this->Next == nullptr)
        throw std::exception("Failed to allocate memory for 'this->Next'");
} // theta(1)

ADT_MultiMap_Pair* ADTMultiMap::getArray() const
{
    return this->Array;
} // theta(1)

void ADTMultiMap::createIterator()
{
    if (this->MyIterator != nullptr)
    {
        delete this->MyIterator;
    }
    this->MyIterator = new ADTMultiMapIterator(this);
} // theta(1)

ADTMultiMapIterator* ADTMultiMap::getIterator()
{
    if (this->Count == 0)
        return nullptr;
    if(this->MyIterator == nullptr)
        this->createIterator();
    return this->MyIterator;
} // theta(1)

bool ADTMultiMap::containsPair(const std::string& Key, const std::string& Value) const
{
    if (Key.empty())
        throw std::exception("The key must be a valid string.");
    if (Value.empty())
        throw std::exception("The value must be a valid string.");
    int mKeyPos = (*this.*HashFunc)(Key);
    while (mKeyPos != -1 && !this->Array[mKeyPos].Key.empty())
    {
        if (this->Array[mKeyPos].Key == Key)
        {
            return true;
        }
        mKeyPos = this->Next[mKeyPos];
    }
    return false;
} // theta(1) in most cases / theta(n) in case the load factor is close to 1, where n is the number of pairs before our pair
