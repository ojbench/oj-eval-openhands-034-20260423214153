

#include "skip_list.hpp"
#include <iostream>
#include <string>

int main() {
    SkipList<int> intSkipList;
    
    // Test with integers
    std::cout << "Testing SkipList with integers:" << std::endl;
    
    // Insert some values
    intSkipList.insert(10);
    intSkipList.insert(20);
    intSkipList.insert(5);
    intSkipList.insert(15);
    intSkipList.insert(25);
    
    // Search for values
    std::cout << "Search 10: " << (intSkipList.search(10) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 15: " << (intSkipList.search(15) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 30: " << (intSkipList.search(30) ? "Found" : "Not found") << std::endl;
    
    // Delete some values
    intSkipList.deleteItem(15);
    std::cout << "After deleting 15, search 15: " << (intSkipList.search(15) ? "Found" : "Not found") << std::endl;
    
    // Test with strings
    SkipList<std::string> stringSkipList;
    std::cout << "\nTesting SkipList with strings:" << std::endl;
    
    stringSkipList.insert("apple");
    stringSkipList.insert("banana");
    stringSkipList.insert("cherry");
    
    std::cout << "Search 'apple': " << (stringSkipList.search("apple") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'grape': " << (stringSkipList.search("grape") ? "Found" : "Not found") << std::endl;
    
    stringSkipList.deleteItem("banana");
    std::cout << "After deleting 'banana', search 'banana': " << (stringSkipList.search("banana") ? "Found" : "Not found") << std::endl;
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    
    return 0;
}

