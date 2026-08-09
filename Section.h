#pragma once
#include "Paragraph.h"
#include <vector>
class Section {
private:
   vector<Paragraph> paragraphs;
public:
    Section();
    Section(const Section& other);
    ~Section();
    Section& operator=(const Section& other);
    Paragraph& getParagraph(int index);
    const Paragraph& getParagraph(int index) const;
    int getParagraphCount() const;
    bool isEmpty() const;
    void insertParagraph(int index, const Paragraph& para);
    void appendParagraph(const Paragraph& para);
    void removeParagraph(int index);
    int getTotalLineCount() const;
    Line& getLineByGlobalIndex(int globalIndex);
    void locate(int globalIndex, int& paraIndex, int& lineIndex) const;
    friend ostream& operator<<(ostream& out, const Section& sec);
};