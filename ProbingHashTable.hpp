#pragma once
#include <iostream>
#include <vector>

bool CheckPrime(int n)
{
    if (n == 2 || n == 3)
    {
        return true;
    }
    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

template <class T, class V>
struct Element
{
    T key;
    V value;
    bool isUsed = false;
    bool isDeleted = false;
    Element()
    {
    }
    Element(const T& key, const V& value)
    {
        this->key = key;
        this->value = value;
        isUsed = false;
        isDeleted = false;
    }
};

template <class T, class V>
class HashTable
{
private:
    std::size_t size;
    std::vector<Element<T, V>> data;

public:
    HashTable()
    {
        this->size = 7;
        this->data.resize(size);
    }

    HashTable(int size)
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
        std::hash<T> hasher;
        std::size_t hashIndex = hasher(key);
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
                while (new_vector[hashIndex].isUsed && new_vector[hashIndex].key != this->data[i].key)
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
        if (Search(key))
        {
            Element<T, V> *found_node = Search(key);
            found_node->value = value; 
            found_node->isUsed = true;
            found_node->isDeleted = false;
            std::size_t hashIndex = HashFunction(key);
            std::cout << "Insert: (" << key << " -> " << value << ") at the index: " << hashIndex << "\n";
            return;
        }
        double size = this->GetSize();
        double not_empty_count = GetNotEmptyCount();
        double loadFactor = not_empty_count / size;
        if (loadFactor >= 0.7)
        {
            this->Resize();
        }
        std::size_t hashIndex = HashFunction(key);
        while (this->data[hashIndex].isUsed == true && this->data[hashIndex].key != key)
        {
            hashIndex = (hashIndex + 1) % this->size;
        }
        Element<T, V> *new_node = new Element<T, V>(key, value);
        new_node->isUsed = true;
        new_node->isDeleted = false;
        this->data[hashIndex] = *new_node;
        std::cout << "Add: (" << key << " -> " << value << ") at the index: " << hashIndex << "\n";
        return;
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
            if (data[hashIndex].key == key)
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
            if ((this->data[hashIndex]).key == key)
            {
                this->data[hashIndex].isUsed = false;
                this->data[hashIndex].isDeleted = true;
                std::cout << "Delete: (" << this->data[hashIndex].key << " -> "
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
                std::cout << "(" << this->data[i].key << " -> " << this->data[i].value << ")\n";
            }
        }
        std::cout << "\n";
    }
};
