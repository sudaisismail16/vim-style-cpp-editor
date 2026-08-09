#pragma once
#include "Chapter.h"
#include <vector>

class Document {
private:
    vector<Chapter> chapters;
    MyString filename;
public:
    Document();
    Document(const MyString& filename);
    ~Document();
    Chapter& getChapter(int index);
    int getChapterCount() const;
    void appendChapter(const Chapter& chap);
    int getTotalLineCount() const;
    Line& getLineByGlobalIndex(int globalIndex);
    bool loadFromFile(const MyString& path);
    bool saveToFile(const MyString& path) const;
    MyString getFilename() const;
    friend ostream& operator<<(ostream& out, const Document& doc);
};