#pragma once
#include "Line.h"
#include <vector>

class Paragraph {
private:
    vector<Line> lines;
public:
    Paragraph();
    Paragraph(const Paragraph& other);
    ~Paragraph();
    Paragraph& operator=(const Paragraph& other);
    Line& getLine(int index);
    const Line& getLine(int index) const;
    int getLineCount() const;
    bool isEmpty() const;
    void insertLine(int index, const Line& line);   
    void appendLine(const Line& line);               
    void removeLine(int index);                      
    Line removeAndReturnLine(int index);            
    void splitLine(int lineIndex, int col);          
    void mergeWithNext(int lineIndex);               
    void renumberFrom(int startingNumber);
    friend ostream& operator<<(ostream& out, const Paragraph& para);
};
