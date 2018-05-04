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

void Dictionary::Load(const int& a, const int& b) {

    mA = a;
    mB = b;
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

std::string Dictionary::Record() {

    return std::to_string(mA) + " " + std::to_string(mB) + "\n";
}

Dictionary::Dictionary() {

    mA = 0;
    mB = 0;
}

Dictionary::~Dictionary() {
}
