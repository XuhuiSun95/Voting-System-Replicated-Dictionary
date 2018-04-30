#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <mutex>

class Dictionary {

public:

    static Dictionary* Instance();
    static void Release();

    void Print();

private:

    static Dictionary* sInstance;
    
    std::mutex mtx;
    int mA;
    int mB;

    Dictionary();
    ~Dictionary();
};

#endif
