#include "Dictionary.hpp"

Dictionary* Dictionary::sInstance = nullptr;

Dictionary* Dictionary::Instance() {

    if(sInstance==nullptr)
        sInstance = new Dictionary();

    return sInstance;
}

void Dictionary::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void Dictionary::Update(const std::string& s) {

    if(s.compare("Vote,A")==0) {
        mtx.lock();
        mA++;
        mtx.unlock();
    } else {
        mtx.lock();
        mB++;
        mtx.unlock();
    }
}

void Dictionary::Print() {

    mtx.lock();
    std::cout << "{A:" << mA << ",B:" << mB << "}" << std::endl;
    mtx.unlock();
}

Dictionary::Dictionary() {

    mA = 0;
    mB = 0;
}

Dictionary::~Dictionary() {
}