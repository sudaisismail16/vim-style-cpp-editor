#pragma once
#include <iostream>
using namespace std;
class MyString {
private:
    char* data = nullptr;
    int length = 0;
    void allocateAndCopy(const char* src) {
        delete[] data;
        length = strlen(src);
        data = new char[length + 1] {};
        for (int i = 0; i < length; i++) {
            data[i] = src[i];
        }
    }

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();
    MyString& operator=(const MyString& other);
    MyString& operator=(const char* str);
    MyString operator+(const MyString& other) const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(char c);
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    char& operator[](int index);
    char operator[](int index) const;
    int getLength() const;
    bool isEmpty() const;
    const char* c_str() const;
    void insertAt(int index, char c);
    void removeAt(int index);
    void clear();
    MyString substring(int start, int count) const;
    int find(const MyString& pattern, int startIndex) const;
    void replaceAt(int index, int oldLen, const MyString& newStr);
    friend ostream& operator<<(ostream& out, const MyString& str);
};

