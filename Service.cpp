#include "Service.h"
#include <assert.h>
void testInsert(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #1 - Inserting 1000 different elements...\n";
	for (int i = 0; i < 1000; i++)
	{
		mMultiMap->insert(std::to_string(i), std::to_string(i));
	}
	std::cout << "| Test #1 - Inserting 1000 different elements - Success\n";
	std::cout << "| Test #1 - Inserting 1000 duplicates...\n";
	for (int i = 0; i < 1000; i++)
	{
		mMultiMap->insert(std::to_string(0), std::to_string(0));
	}
	std::cout << "| Test #1 - Inserting 1000 duplicates - Success\n";
	assert(mMultiMap->count() == 2000);
	std::cout << "| Test #1 - Success\n";
}

void testDelete(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #2 - Removing 1000 different elements...\n";
	for (int i = 0; i < 1000; i++)
	{
		mMultiMap->deletePair(std::to_string(i), std::to_string(i));
	}
	std::cout << "| Test #2 - Removing 1000 different elements - success\n";
	std::cout << "| Test #2 - Removing 1000 duplicates...\n";
	mMultiMap->deleteKey(std::to_string(0));
	std::cout << "| Test #2 - Removing 1000 duplicates - success\n";
	assert(mMultiMap->count() == 0);
	std::cout << "| Test #2 - Success\n";
}
void testClear(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #3 - Inserting 1000 elements...\n";
	for (int i = 0; i < 1000; i++)
	{
		mMultiMap->insert(std::to_string(i), std::to_string(i));
	}
	std::cout << "| Test #3 - Inserting 1000 elements - success\n";
	std::cout << "| Test #3 - Clearing...\n";
	mMultiMap->clear();
	assert(mMultiMap->count() == 0);
	std::cout << "| Test #3 - Success\n";
}
void testSearch(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #4 - Inserting 1000 elements...\n";
	for (int i = 0; i < 1000; i++)
	{
		mMultiMap->insert(std::to_string(0), std::to_string(i));
	}
	std::cout << "| Test #4 - Inserting 1000 elements - success\n";
	std::cout << "| Test #4 - Searching...\n";
	std::vector<std::string> mList;
	mMultiMap->search(std::to_string(0), mList);
	for (int i = 0; i < 1000; i++)
	{
		assert(mMultiMap->containsPair(std::to_string(0), std::to_string(i)) != false);
	}
	assert(mList.size() == 1000);
	std::cout << "| Test #4 - Success\n";
	mMultiMap->clear();
}
void testSizes(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #5 - Inserting 1000 elements...\n";
	int lastSize = SIZE_OF_MULTIMAP;
	std::cout << "| Test #5 - Testing count() && size() && isEmpty()...\n";
	for (int i = 0; i < 1000; i++)
	{
		if (!mMultiMap->isEmpty() && mMultiMap->count() % lastSize == 0)
			lastSize *= 2;
		mMultiMap->insert(std::to_string(0), std::to_string(i));
		assert(mMultiMap->count() == i + 1);
		assert(mMultiMap->size() == lastSize);
	}
	mMultiMap->clear();
	std::cout << "| Test #5 - Success\n";
}
void testIterator(ADTMultiMap* mMultiMap)
{
	std::cout << "| Test #6 - ADTMultiMap->getIterator()...\n";
	ADTMultiMapIterator* mIterator = mMultiMap->getIterator();
	assert(mIterator == nullptr);
	std::cout << "| Test #6 - Inserting elements...\n";
	for (int i = 0; i < 1000; i++)
		mMultiMap->insert(std::to_string(i), std::to_string(i));
	mIterator = mMultiMap->getIterator();
	assert(mIterator != nullptr);
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		do
		{
			count++;
			assert(mIterator->getCurrentKey() == mIterator->getCurrentValue());
		} while (mIterator->next());
		assert(count == 1000);
		mMultiMap->createIterator();
		mIterator = mMultiMap->getIterator();
		count = 0;
	}
	std::cout << "| Test #6 - Success\n";
}
void runTests()
{
    std::cout << "| Status: Executing Tests..." << std::endl;
	std::cout << "| Test #0 - ADTMultiMap()...\n";
	ADTMultiMap* mMultiMap = new ADTMultiMap();
	std::cout << "| Test #0 - Success\n";
    std::cout << "| Test #1 - ADTMultiMap->insert()...\n";
	try
	{
		testInsert(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Test #2 - ADTMultiMap->deleteKey() & ->deletePair()...\n";
	try
	{
		testDelete(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Test #3 - ADTMultiMap->clear()...\n";
	try
	{
		testClear(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Test #4 - ADTMultiMap->search() & ->containsPair()...\n";
	try
	{
		testSearch(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Test #5 - ADTMultiMap->count() & ->size() & ->isEmpty()...\n";
	try
	{
		testSizes(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Test #6 - ADTMultiMapIterator...\n";
	try
	{
		testIterator(mMultiMap);
	}
	catch (const std::exception& ex)
	{
		std::cout << "| Status: " << ex.what() << std::endl;
	}
	std::cout << "| Status: Testing is done...\n";
	delete mMultiMap;
	system("pause");
	system("cls");
}