#include"Section.h"

Section::Section() {
	paragraphs.clear();
}
Section::Section(const Section& other) {
	this->paragraphs = other.paragraphs;
}
Section::~Section() {

}
Section& Section::operator=(const Section& other) {
    if (this == &other) {
        return *this;
    }
    this->paragraphs = other.paragraphs;
    return *this;
}
Paragraph& Section::getParagraph(int index) {
    return paragraphs[index];
}
const Paragraph& Section::getParagraph(int index) const {
    return paragraphs[index];
}
int Section::getParagraphCount() const {
    return paragraphs.size();
}
bool Section::isEmpty() const {
    return paragraphs.empty();
}
void Section::insertParagraph(int index, const Paragraph& para) {
    paragraphs.insert(paragraphs.begin() + index, para);
}
void Section::appendParagraph(const Paragraph& para) {
    paragraphs.push_back(para);
}
void Section::removeParagraph(int index) {
    paragraphs.erase(paragraphs.begin() + index);
}
int Section::getTotalLineCount() const {
    int total = 0;
    for (int i = 0; i < (int)paragraphs.size(); i++) {
        total += paragraphs[i].getLineCount();
    }
    return total;
}
Line& Section::getLineByGlobalIndex(int globalIndex) {
    int paraIndex, lineIndex;
    locate(globalIndex, paraIndex, lineIndex);
    return paragraphs[paraIndex].getLine(lineIndex);
}
void Section::locate(int globalIndex, int& paraIndex, int& lineIndex) const {
    int remaining = globalIndex;
    for (int i = 0; i < (int)paragraphs.size(); i++) {
        int count = paragraphs[i].getLineCount();
        if (remaining < count) {
            paraIndex = i;
            lineIndex = remaining;
            return;
        }
        remaining -= count;
    }
    paraIndex = -1;
    lineIndex = -1;
}
ostream& operator<<(ostream& out, const Section& sec) {
    for (int i = 0; i < (int)sec.paragraphs.size(); i++) {
        out << sec.paragraphs[i];
    }
    return out;
}
