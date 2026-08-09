#pragma once
#include "Section.h"
#include <vector>
class Chapter {
private:
    vector<Section> sections;
public:
    Chapter();
    Chapter(const Chapter& other);
    ~Chapter();
    Chapter& operator=(const Chapter& other);
    Section& getSection(int index);
    const Section& getSection(int index) const;
    int getSectionCount() const;
    bool isEmpty() const;
    void insertSection(int index, const Section& sec);
    void appendSection(const Section& sec);
    void removeSection(int index);
    int getTotalLineCount() const;
    Line& getLineByGlobalIndex(int globalIndex);
    void locate(int globalIndex, int& sectionIndex, int& paraIndex, int& lineIndex) const;
    friend ostream& operator<<(ostream& out, const Chapter& chap);
};