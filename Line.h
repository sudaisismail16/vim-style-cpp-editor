#pragma once
#include "MyString.h"
#include <iostream>

class Line {
private:
    MyString content;
    int lineNumber = 0;
public:
    Line();
    Line(const MyString& text);
    Line(const char* text);
    Line(const Line& other);
    ~Line();
    Line& operator=(const Line& other);
    MyString getContent() const;
    void setContent(const MyString& text);
    int getLength() const;
    bool isEmpty() const;
    void clear();
    void insertChar(int col, char c);   
    void deleteChar(int col);           
    void deleteToEnd(int col);          
    void toggleCase(int col);           
    int nextWordStart(int col) const;   
    int prevWordStart(int col) const;   
    int startOfLine() const;            
    int endOfLine() const;              
    int find(const MyString& pattern, int startCol) const;
    void setLineNumber(int num);
    int getLineNumber() const;
    friend ostream& operator<<(ostream& out, const Line& line);
};