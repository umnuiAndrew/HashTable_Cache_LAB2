#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
public:
    struct dll
    {
        int key;
        dll *left, *right;
        dll(int k, dll *prev, dll *next)
        {
            key = k;
            left = prev;
            right = next;
        }
    };
    LRUCache(int cap);
    int get(int key);
    void set(int key, int value);

private:
    dll *head, *tail;
    int capacity;
    unordered_map<int, dll *> q_map;
    unordered_map<int, int> cache;
};

LRUCache::LRUCache(int cap)
{
    head = NULL;
    tail = NULL;
    capacity = cap;
    q_map.clear();
    cache.clear();
}

int LRUCache::get(int key)
{
    if (cache.find(key) == cache.end()) // if the value is absent from the cache
        return -1;
    if (cache.size() == 1) // trivial case of only 1 value being present in the cache
        return cache[key];
    dll *node = q_map[key], *prev = node->left, *next = node->right;
    if (node == head) // if the value is present at the head of the cache only
        return cache[key];
    // now, we start considering for the general case, 
    //where the value is present somewhere in the cache and not at the head
    if (node == tail)
        tail = node->left;
    if (prev)
        prev->right = next;
    if (next)
        next->left = prev;
    node->left = NULL;
    node->right = head;
    head->left = node;
    head = node;
    return cache[key];
}

void LRUCache::set(int key, int value)
{
    if (cache.find(key) != cache.end()) // meaning, the key is present somewhere in the cache
    {
        cache[key] = value;
        dll *node = q_map[key],
            *prev = node->left,
            *next = node->right;
        if (node == head) // the key is present at the beginning only, so no need to do anything
            return;
        if (node == tail)
            tail = node->left;
        if (prev)
            prev->right = next;
        if (next)
            next->left = prev;
        node->left = NULL;
        node->right = head;
        head->left = node;
        head = node;
        return;
    }
    if (cache.size() < capacity) // the value ain't present, but it can be inserted as the cache isn't full till now
    {
        cache[key] = value;
        dll *node = new dll(key, NULL, head);
        if (!tail) // this happens if the cache is initially empty
            tail = node;
        else
            head->left = node;
        head = node;
        q_map[key] = node;
        return;
    }
    // now, we consider the case when the cache is full and there is a page fault
    int key_del = tail->key;
    if (head == tail) // when there is only 1 element in the cache
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
    q_map.erase(key_del);
    cache.erase(key_del);
    cache[key] = value;
    dll *node = new dll(key, NULL, head);
    if (!tail) // when the cache is empty
        tail = node;
    else
        head->left = node;
    head = node;
    q_map[key] = node;
}

int main()
{
    int sz, noq, qt, a, b;
    cin >> sz >> noq; // sz = maximum cache capacity and noq = number of queries
    LRUCache obj(sz);
    while (noq--)
    {
        cin >> qt;
        if (qt == 1) // get(val)
        {
            cin >> a;
            cout << obj.get(a) << endl;
        }
        else // set(key,val)
        {
            cin >> a >> b;
            obj.set(a, b);
        }
    }
}