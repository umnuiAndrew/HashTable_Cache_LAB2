#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "ProbingHashTable.hpp"
#include <algorithm>

struct less_than_key
{
    inline bool operator() (const Element<std::string, int>& struct1, const Element<std::string, int>& struct2)
    {
        return !(struct1.value < struct2.value);
    }
};


std::string file_to_string()
{
    std::string outputstring;
    std::string buffer;
    std::ifstream input("1.txt");

    while (std::getline(input, buffer))
    {
        outputstring += (buffer + '\n');
    }
    return outputstring;
}

void string_to_vector(std::vector<std::string> &out_put_vector, std::string &inputString)
{
    long long input_lenght = inputString.length();

    std::string word;
    for (long long i = 0; i < input_lenght; ++i)
    {
        int a;
        a = inputString[i];
        if (((a >= 65 && a <= 90) || (a >= 97 && a <= 122) || a == 95) && inputString[i] != ' ' && inputString[i] != '\n' && inputString[i] != '\0')
        {
            word += inputString[i];
        }
        else
        {
            if (word != "" && word != " " && word != "\n" && word != "\t" 
            && word != "the" && word != "a" && word != "an")
            {
                out_put_vector.push_back(word);
                word.clear();
            }
        }
    }
}

void Add_to_HashTable(HashTable<std::string, int> *myHashTable, std::string word)
{
    if (!myHashTable->Search(word))
    {
        myHashTable->Add(word, 1);
    }
    else
    {
        Element<std::string, int> *found_word = myHashTable->Search(word);
        ++(found_word->value);
    }
}

void strVector_to_hashtable(HashTable<std::string, int> *myHashTable, std::vector<std::string> &strVector)
{
    for (std::string str : strVector)
    {
        Add_to_HashTable(myHashTable, str);
    }
}

void sort_function(HashTable<std::string, int> *myHashTable)
{
    int n = myHashTable->GetSize();
    std::vector<Element<std::string, int>> myData = myHashTable->GetData();
    std::vector<Element<std::string, int>> workedData;

    for (size_t i = 0; i < n; ++i)
    {
        if (myData[i].isUsed && !(myData[i].isDeleted))
        {
            workedData.push_back(myData[i]);
        }
    }

    std::sort(workedData.begin(), workedData.end(), less_than_key());
    
    for (int i = 0; i < 100; ++i)
    {
        std::cout << i << ": " << workedData[i].key << " -> " << workedData[i].value << "\n";
    }
}

void utility_function(HashTable<std::string, int> *myHashTable)
{
    std::string inputString = file_to_string();
    std::vector<std::string> strVector;
    string_to_vector(strVector, inputString);
    strVector_to_hashtable(myHashTable, strVector);
    sort_function(myHashTable);
}

// for (int i = 65; i < 125; ++i)
// {
//     char a;
//     a = i;
//     if ((i <= 90) || (i >= 97 && i <= 122) || i == 95)
//     {
//         std::cout << a << " ";
//     }
// }
