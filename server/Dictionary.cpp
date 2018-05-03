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

    if(s.compare("Vote,A")==0)
        mA++;
    else
        mB++;
}

void Dictionary::Print() {

    std::cout << "{A:" << mA << ",B:" << mB << "}" << std::endl;
}

Dictionary::Dictionary() {

    mA = 0;
    mB = 0;
}

Dictionary::~Dictionary() {
}
