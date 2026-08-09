#include "Document.h"
#include <fstream>
#include <string>

Document::Document() {
    chapters.clear();
}

Document::Document(const MyString& filename) : Document() {
    this->filename = filename;
    loadFromFile(filename);
}

Document::~Document() {
}

Chapter& Document::getChapter(int index) {
    return chapters[index];
}

int Document::getChapterCount() const {
    return chapters.size();
}

void Document::appendChapter(const Chapter& chap) {
    chapters.push_back(chap);
}

int Document::getTotalLineCount() const {
    int total = 0;
    for (int i = 0; i < (int)chapters.size(); i++) {
        total += chapters[i].getTotalLineCount();
    }
    return total;
}

Line& Document::getLineByGlobalIndex(int globalIndex) {
    int remaining = globalIndex;
    for (int i = 0; i < (int)chapters.size(); i++) {
        int count = chapters[i].getTotalLineCount();
        if (remaining < count) {
            return chapters[i].getLineByGlobalIndex(remaining);
        }
        remaining -= count;
    }
    return chapters[0].getLineByGlobalIndex(0);
}

bool Document::loadFromFile(const MyString& path) {
    ifstream file(path.c_str());
    if (!file.is_open()) {
        return false;
    }
    Chapter chap;
    Section sec;
    Paragraph para;
    string lineStr;
    while (getline(file, lineStr)) {
        para.appendLine(Line(lineStr.c_str()));
    }
    if (para.isEmpty()) {
        para.appendLine(Line(""));
    }
    sec.appendParagraph(para);
    chap.appendSection(sec);
    chapters.clear();
    chapters.push_back(chap);
    filename = path;
    return true;
}
bool Document::saveToFile(const MyString& path) const {
    ofstream file(path.c_str());
    if (!file.is_open()) {
        return false;
    }
    for (int i = 0; i < (int)chapters.size(); i++) {
        file << chapters[i];
    }
    return true;
}

MyString Document::getFilename() const {
    return filename;
}

ostream& operator<<(ostream& out, const Document& doc) {
    for (int i = 0; i < (int)doc.chapters.size(); i++) {
        out << doc.chapters[i];
    }
    return out;
}