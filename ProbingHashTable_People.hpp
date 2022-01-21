#pragma once
#include <iostream>
#include <vector>
#include "ProbingHashTable.hpp"

class People
{
private:
    std::string name;
    int age;

public:
    People()
    {
    }
    People(std::string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    void setName(std::string name)
    {
        this->name = name;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    std::string getName() const
    {
        return this->name;
    }
    int getAge() const
    {
        return this->age;
    }
};

template<>
struct std::hash<People>
{
    std::size_t operator()(People const& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(s.getName());
        return h1; // or use boost::hash_combine
    }
};

struct MyHash
{
    std::size_t operator()(People const& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(s.getName());
        return h1; // or use boost::hash_combine
    }
};

template <class T, class V>
class HashTableObject
{
private:
    std::size_t size;
    std::vector<Element<T, V>> data;

public:
    HashTableObject()
    {
        this->size = 7;
        this->data.resize(size);
    }

    HashTableObject(int size)
    {
        this->size = size;
        this->data.resize(size);
    }

    std::vector<Element<T,V>> GetData()
    {
        return this->data;
    }

    void SetData(std::vector<Element<T,V>>& new_data)
    {
        this->data = new_data;
    }

    std::size_t HashFunction(const T &key)
    {
        std::size_t hashIndex = std::hash<T>{}(key);
        return hashIndex % this->size;
    }

    const V &Get(const T &key)
    {
        return (this->Search(key))->value;
    }

    const std::size_t GetSize()
    {
        return this->size;
    }

    const std::size_t GetNotEmptyCount()
    {
        std::size_t n = 0;
        for (std::size_t i = 0; i < size; ++i)
        {
            if (data[i].isUsed)
            {
                ++n;
            }
        }
        return n;
    }

    // fix hash all element 1 more time

    void Resize()
    {
        std::size_t new_size = this->size * 2;
        while (!CheckPrime(new_size))
        {
            ++new_size;
        }
        std::vector<Element<T, V>> new_vector(new_size);
        for (std::size_t i = 0; i < this->size; ++i)
        {
            if (this->data[i].isUsed)
            {
                std::size_t hashIndex = HashFunction(this->data[i].key);
                while (new_vector[hashIndex].isUsed && new_vector[hashIndex].key.getName() != this->data[i].key.getName())
                {
                    hashIndex = (hashIndex + 1) % this->size;
                }
                Element<T, V> *new_node = new Element<T, V>(this->data[i].key, this->data[i].value);
                new_vector[hashIndex] = *new_node;
                new_vector[hashIndex].isUsed = true;
            }
        }
        this->data = new_vector;
        this->size = new_size;
        new_vector.clear();
        std::cout << "Hash-table resized to: " << new_size << "\n";
    }

    void Add(const T &key, const V &value)
    {
        double size = this->GetSize();
        double not_empty_count = GetNotEmptyCount();
        double loadFactor = not_empty_count / size;
        if (loadFactor >= 0.7)
        {
            this->Resize();
        }
        std::size_t hashIndex = HashFunction(key);
        while (this->data[hashIndex].isUsed == true && this->data[hashIndex].key.getName() != key.getName())
        {
            hashIndex = (hashIndex + 1) % this->size;
        }
        std::cout << "Add: (" << key.getName() << " -> " << value << ") at the index: " << hashIndex << "\n";
        Element<T, V> *new_node = new Element<T, V>(key, value);
        this->data[hashIndex] = *new_node;
        this->data[hashIndex].isUsed = true;
    }

    Element<T, V> *Search(const T &key)
    {
        std::size_t hashIndex = HashFunction(key);
        std::size_t counter = 0;
        std::size_t capacity = this->GetNotEmptyCount();

        while (true)
        {
            if (counter++ > capacity)
            {
                return NULL;
            }
            if (data[hashIndex].key.getName() == key.getName())
            {
                return &data[hashIndex];
            }
            hashIndex = (hashIndex + 1) % this->size;
        }
        return NULL;
    }

    void DeleteNode(const T &key)
    {
        std::size_t hashIndex = HashFunction(key);
        std::size_t counter = 0;
        std::size_t capacity = this->GetNotEmptyCount();
        // when dont have element that want to delete
        while (true)
        {
            if (counter++ > capacity)
            {
                return;
            }
            if ((this->data[hashIndex]).key.getName() == key.getName())
            {
                this->data[hashIndex].isUsed = false;
                this->data[hashIndex].isDeleted = true;
                std::cout << "Delete: (" << this->data[hashIndex].key.getName() << " -> "
                          << this->data[hashIndex].value << ") "
                          << "at the index: " << hashIndex << "\n";
                return;
            }
            hashIndex = (hashIndex + 1) % this->size;
        }
        return;
    }

    bool IsEmpty(const std::size_t &index)
    {
        return !data[index].isUsed;
    }

    bool IsDeleted(const std::size_t &index)
    {
        return data[index].isDeleted;
    }

    void Print()
    {
        std::cout << "Full HashTable: \n";
        for (std::size_t i = 0; i < this->size; ++i)
        {
            if (this->data[i].isUsed && !(this->data[i].isDeleted))
            {
                std::cout << "(" << this->data[i].key.getName() << " -> " << this->data[i].value << ")\n";
            }
        }
        std::cout << "\n";
    }
};
