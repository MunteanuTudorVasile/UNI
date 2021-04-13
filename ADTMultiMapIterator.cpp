#include "ADTMultiMapIterator.h"
#include <string>
bool ADTMultiMapIterator::valid()
{
    if (this->currentPosition >= 0 && this->currentPosition < this->mHashTable->size())
        return true;
    return false;
} // theta(1)

ADTMultiMapIterator::ADTMultiMapIterator(ADTMultiMap* mHashTable)
{
    this->mHashTable = mHashTable;
    currentPosition = 0;
    while (this->valid() && this->mHashTable->getArray()[this->currentPosition].Key.empty())
    {
        this->currentPosition += 1;
    }
} // theta(1) in most cases / theta(n) where n is the number of empty positions in our array

bool ADTMultiMapIterator::next()
{
    do
    {
        this->currentPosition += 1;
    } while (this->valid() && this->mHashTable->getArray()[this->currentPosition].Key.empty());
    if(this->valid())
        return true;
    return false;
} // theta(n) n is the number of empty positions in our array before a valid position

std::string& ADTMultiMapIterator::getCurrentKey()
{
    if (!this->valid())
        throw std::exception("The Iterator is not valid anymore.");
    return this->mHashTable->getArray()[this->currentPosition].Key;
} // theta(1)

std::string& ADTMultiMapIterator::getCurrentValue()
{
    if (!this->valid())
        throw std::exception("The Iterator is not valid anymore.");
    return this->mHashTable->getArray()[this->currentPosition].Value;
} // theta(1)
