#pragma once
#include <iostream>
#include "ProbingHashTable_People.hpp"
#include "LRU_Cache.hpp"

template <class K, class V>
class LRUCacheObject
{
public:
    LRUCacheObject(int cap);
    void get(const K &key);
    void set(const K &key, const V &value);
    void print();

private:
    dll<K> *head, *tail;
    int capacity;
    HashTableObject<K, dll<K> *> q_map;
    HashTableObject<K, V> cache;
};

template <class K, class V>
LRUCacheObject<K, V>::LRUCacheObject(int cap)
{
    this->head = NULL;
    this->tail = NULL;
    this->capacity = cap;
}

template <class K, class V>
void LRUCacheObject<K, V>::set(const K &key, const V &value)
{
    if (cache.Search(key)) // Found key somewhere in cache
    {
        cache.Add(key, value);
        dll<K> *node = q_map.Search(key)->value,
               *prev = node->left,
               *next = node->right;

        if (node == head)
        {
            return;
        }

        if (node == tail)
        {
            tail = node->left;
        }

        if (prev)
        {
            prev->right = next;
        }

        if (next)
        {
            next->left = prev;
        }

        node->left = NULL;
        node->right = head;
        head->left = node;
        head = node;
        return;
    }

    if (cache.GetNotEmptyCount() < capacity) // can't find key in cache
    {
        cache.Add(key, value);
        dll<K> *node = new dll<K>(key, NULL, head);
        if (!tail) // initially cache is empty
        {
            tail = node;
        }
        else
        {
            head->left = node;
        }
        head = node;
        q_map.Add(key, node);
        return;
    }

    // cache is full and there is a page fault
    K key_del = tail->key;
    if (head == tail)
    {
        delete tail;
        head = NULL;
        tail = NULL;
    }
    else
    {
        tail = tail->left;
        delete tail->right;
        tail->right = NULL;
    }
    q_map.DeleteNode(key_del);
    cache.DeleteNode(key_del);
    cache.Add(key, value);
    dll<K> *node = new dll<K>(key, NULL, head);
    if (!tail) // when the cache is empty
    {
        tail = node;
    }
    else
    {
        head->left = node;
    }
    head = node;
    q_map.Add(key, node);
    return;
}

template <class K, class V>
void LRUCacheObject<K, V>::get(const K &key)
{
    if (!cache.Search(key)) // key is absent from cache
    {
        std::cout << "Can not find " << key.getName() << " in Cache\n";
        return;
    }
    if (cache.GetSize() == 1)
    {
        std::cout << "Get: Key: " << key.getName() << " Value: " << cache.Get(key) << "\n";
        return;
    }
    dll<K> *node = q_map.Get(key),
           *prev = node->left,
           *next = node->right;
    if (node == head)
    {
        std::cout << "Get: Key: " << key.getName() << " Value: " << cache.Get(key) << "\n";
        return;
    }
    // if key is not in the head we need to move it to head
    if (node == tail)
    {
        tail = node->left;
    }

    if (prev)
    {
        prev->right = next;
    }

    if (next)
    {
        next->left = prev;
    }

    node->left = NULL;
    node->right = head;
    head->left = node;
    head = node;
    std::cout << "Key: " << key.getName() << " -> Value: " << cache.Get(key) << "\n";
}

template <class K, class V>
void LRUCacheObject<K, V>::print()
{
    std::cout << "Full Cache with capacity: " << capacity << "\n";
    dll<K> *p = head;
    int count = 1;
    while (p != NULL)
    {
        std::cout << count << ":"
                  << "[" << p->key.getName() << " -> " << cache.Get(p->key) << "]"
                  << "\n";
        p = p->right;
        ++count;
    }
    std::cout << "\n";
}