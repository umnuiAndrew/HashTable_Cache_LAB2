#include <iostream>
#include <unordered_map>
#include "ProbingHashTable.hpp"
#include "ProbingHashTable_People.hpp"
#include "convert_file_to_vector_of_string.hpp"
#include "LRU_Cache.hpp"

int main()
{
    // std::cout << "Hash-table program: \n";
    // HashTable<std::string, int> *H1 = new HashTable<std::string, int>();
    // H1->Add("Andrew", 68);
    // H1->Add("Godfrei", 89);
    // H1->Add("Ilya", 99);
    // H1->Add("Andrew", 99);
    // H1->Add("Andrew", 888);

    // H1->DeleteNode("Ilya");
    // H1->DeleteNode("Andrew");

    //  Add_to_HashTable(H1, "Andrew");
    //  Add_to_HashTable(H1, "Andrew");
    //  Add_to_HashTable(H1, "Tambo");
    //  Add_to_HashTable(H1, "Dimitri");
    //  Add_to_HashTable(H1, "Hien");
    //  Add_to_HashTable(H1, "Ivan");
    // H1->Print();

    // Element<std::string, int> *my_elem = H1->Search("Godfrei");
    // std::cout << "Search for Key: " << my_elem->key << ", value: " << my_elem->value << "\n\n";
    // H1->Print();
    // std::cout << "Number of element: " << H1->GetNotEmptyCount() << "\n";

    // utility_function(H1);

    // std::cout << MyHash{}(per1) << "\n";
    // std::cout << std::hash<People>{}(per1) << "\n";
    // HashTable<int, dll *> H1(3);
    // dll* node1 = new dll(8, NULL, NULL);
    // H1.Add(2, node1);
    LRUCache<std::string, std::string> obj(5);
    obj.set("Duc", "Anh");
    obj.set("Tam", "Bo");
    obj.set("Dima", "LD");
    obj.set("Ivan", "Do");
    obj.set("Thuy", "Hien Hien");
    obj.set("Dima", "Stikalovski");
    obj.set("asdf", "dsfg");
    obj.set("ghf", "Stikaljhgjhgovski");
    obj.set("Dertima", "Stiertkalovski");
    obj.set("Diretma", "Stikahgfhfglovski");
    obj.set("Diertwma", "Stikaqwerlovski");
    obj.print();
    std::string empty = obj.get("ghf");
    std::cout << "\n";
    obj.print();
}

//задача
// 1, Book
// 2, есть массив строчик, исполь unorderd_set для поиска строчик
// 3, 2 массив, обединение, вычитание пересечение (ok)
// for 1LAB: string of "*." give n number of element, change * -> . find (ok)
//****......**..*** n=2 -> 7 //< O(n**2) ~O(N)