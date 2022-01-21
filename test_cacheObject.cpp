#include <iostream>
#include "LRU_Cache_Object.hpp"

int main()
{
    People per1("Andrew", 20);
    People per2("Bob", 23);
    People per3("John", 21);
    People per4("Scarlet", 19);
    People per5("Stuart", 25);
    People per6("Tom", 26);
    People per7("Jenny", 24);
    People per8("Steve", 28);
    People per9("Mark", 27);
    People per10("Anastasya", 23);
    People per11("Oha", 21);
    People per12("Karry", 19);
    LRUCacheObject<People, std::string> myCache(5);
    myCache.set(per1, "Student");
    myCache.set(per2, "Engineer");
    myCache.set(per3, "Student");
    myCache.set(per4, "Pupil");
    myCache.set(per4, "Baby");
    myCache.set(per5, "Doctor");
    myCache.set(per6, "Fire fighter");
    myCache.set(per7, "Fammer");
    myCache.set(per8, "Director");
    myCache.set(per9, "Teacher");
    myCache.set(per10, "Master student");
    myCache.set(per11, "Scientist");
    myCache.set(per12, "Nurse");
    myCache.get(per1); // Canot find in cache
    myCache.get(per2);
    myCache.print();
}