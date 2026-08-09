#include"Chapter.h"

Chapter::Chapter(){
	sections.clear();
}
Chapter::Chapter(const Chapter& other) {
	this->sections = other.sections;
}
Chapter::~Chapter() {

}
Chapter& Chapter::operator=(const Chapter& other) {
    if (this == &other) {
        return *this;
    }
    this->sections = other.sections;
    return *this;
}
Section& Chapter::getSection(int index) {
    return sections[index];
}
const Section& Chapter::getSection(int index) const {
    return sections[index];
}
int Chapter::getSectionCount() const {
    return sections.size();
}
bool Chapter::isEmpty() const {
    return sections.empty();
}
void Chapter::insertSection(int index, const Section& sec) {
    sections.insert(sections.begin() + index, sec);
}
void Chapter::appendSection(const Section& sec) {
    sections.push_back(sec);
}
void Chapter::removeSection(int index) {
    sections.erase(sections.begin() + index);
}
int Chapter::getTotalLineCount() const {
    int total = 0;
    for (int i = 0; i < (int)sections.size(); i++) {
        total += sections[i].getTotalLineCount();
    }
    return total;
}
Line& Chapter::getLineByGlobalIndex(int globalIndex) {
    int sectionIndex, paraIndex, lineIndex;
    locate(globalIndex, sectionIndex, paraIndex, lineIndex);
    return sections[sectionIndex].getParagraph(paraIndex).getLine(lineIndex);
}
void Chapter::locate(int globalIndex, int& sectionIndex, int& paraIndex, int& lineIndex) const {
    int remaining = globalIndex;
    for (int i = 0; i < (int)sections.size(); i++) {
        int count = sections[i].getTotalLineCount();
        if (remaining < count) {
            sectionIndex = i;
            sections[i].locate(remaining, paraIndex, lineIndex);
            return;
        }
        remaining -= count;
    }
    sectionIndex = -1;
    paraIndex = -1;
    lineIndex = -1;
}
ostream& operator<<(ostream& out, const Chapter& chap) {
    for (int i = 0; i < (int)chap.sections.size(); i++) {
        out << chap.sections[i];
    }
    return out;
}




