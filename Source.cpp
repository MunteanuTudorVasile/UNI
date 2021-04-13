#include <iostream>
#include "ADTMultiMap.h"
#include "Service.h"
ADTMultiMap* mMultiMap;

char* menuOptions[8] = { "Add item\t\t|", "Remove item\t|", "Remove category\t|", "Search item\t|", "Get category\t|", "Get count\t\t|", "Show items\t\t|", "Exit\t\t|" };

void printMenu()
{
    std::cout << "=========================" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << "| " << i + 1 << ". " << menuOptions[i] << std::endl;
    }
    std::cout << "=========================" << std::endl; 
}
int getIntInRange(int rng)
{
    int inp;
    while (true)
    {
        std::cout << "| Input: ";
        try
        {
            std::cin >> inp;
            if (inp < 1 || inp > 8)
                throw std::exception();
            return inp;
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: Error, please enter a valid integer(1-" << rng << ")\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}
void handleOption(int opt)
{
    if (opt == 1)
    {
        std::string category;
        std::cin.ignore();
        std::cout << "| Item's category: ";
        std::getline(std::cin, category);

        std::string name;
        std::cout << "| Item's name: ";
        std::getline(std::cin, name);

        try
        {
            mMultiMap->insert(category, name);
            std::cout << "| Status: Success" << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: " << ex.what() << std::endl;
        }
    }
    if (opt == 2)
    {
        std::string category;
        std::cin.ignore();
        std::cout << "| Item's category: ";
        std::getline(std::cin, category);

        std::string name;
        std::cout << "| Item's name: ";
        std::getline(std::cin, name);

        try
        {
            mMultiMap->deletePair(category, name);
            std::cout << "| Status: Success" << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: " << ex.what() << std::endl;
        }
    }
    if (opt == 3)
    {
        std::string category;
        std::cin.ignore();
        std::cout << "| Category: ";
        std::getline(std::cin, category);
        try
        {
            mMultiMap->deleteKey(category);
            std::cout << "| Status: Success" << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: " << ex.what() << std::endl;
        }

    }
    if (opt == 4)
    {
        std::string category;
        std::cin.ignore();
        std::cout << "| Item's category: ";
        std::getline(std::cin, category);

        std::string name;
        std::cout << "| Item's name: ";
        std::getline(std::cin, name);

        try
        {
            if (mMultiMap->containsPair(category, name))
                std::cout << "| Status: The item exists" << std::endl;
            else
                std::cout << "| Status: The item does not exists" << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: " << ex.what() << std::endl;
        }
    }
    if (opt == 5)
    {
        std::string category;
        std::cin.ignore();
        std::cout << "| Category: ";
        std::getline(std::cin, category);

        try
        {
            std::vector<std::string> arr;
            mMultiMap->search(category, arr);

            if (arr.size() == 0)
                throw std::exception("The category does not exist");
            for (auto& result : arr)
            {
                std::cout << "| " << category << " - " << result << std::endl;
            }
        }
        catch (const std::exception& ex)
        {
            std::cout << "| Status: " << ex.what() << std::endl;
        }
    }
    if (opt == 6)
    {
        std::cout << "| Count: " << mMultiMap->count() << std::endl;
    }
    if (opt == 7)
    {
        if (mMultiMap->count() == 0)
        {
            std::cout << "| Status: The inventory is empty\n";
            return;
        }
            
        mMultiMap->createIterator();
        ADTMultiMapIterator* mIterator = mMultiMap->getIterator();
        std::cout << "| Items: \n";
        do
        {
            std::cout << "| " << mIterator->getCurrentKey() << " - " << mIterator->getCurrentValue() << "\n";
        } while (mIterator->next());
    }
}
int main()
{
    runTests();
    mMultiMap = new ADTMultiMap();
    int menuSize = 8;
    int option;
    do
    {
        printMenu();
        option = getIntInRange(menuSize);
        handleOption(option);
    } while (option != menuSize);
    
    delete mMultiMap;
    system("pause");
}
