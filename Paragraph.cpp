#include"Paragraph.h"

Paragraph::Paragraph() {
	lines.clear();
}
Paragraph::Paragraph(const Paragraph& other) {
	this->lines = other.lines;
}
Paragraph::~Paragraph() {

}

Paragraph& Paragraph::operator=(const Paragraph& other) {
    if (this == &other) {
        return *this;
    }
    this->lines = other.lines;
    return *this;
}
Line& Paragraph::getLine(int index){
    return lines[index];
}
const Line& Paragraph::getLine(int index) const {
    return lines[index];
}
int Paragraph::getLineCount() const {
    return lines.size();
}
bool Paragraph::isEmpty() const {
    return lines.empty();
}

void Paragraph::insertLine(int index, const Line& line) {
    lines.insert(lines.begin() + index, line);
}
void Paragraph::appendLine(const Line& line) {
    lines.push_back(line);
}
void Paragraph::removeLine(int index) {
    lines.erase(lines.begin() + index);
}
Line Paragraph::removeAndReturnLine(int index) {
    Line removed = lines[index];
    lines.erase(lines.begin() + index);
    return removed;
}
void Paragraph::splitLine(int lineIndex, int col) {
    MyString fullText = lines[lineIndex].getContent();
    MyString firstHalf = fullText.substring(0, col);
    MyString secondHalf = fullText.substring(col, fullText.getLength() - col);

    lines[lineIndex].setContent(firstHalf);
    lines.insert(lines.begin() + lineIndex + 1, Line(secondHalf));
}
void Paragraph::mergeWithNext(int lineIndex) {
    MyString combined = lines[lineIndex].getContent() + lines[lineIndex + 1].getContent();
    lines[lineIndex].setContent(combined);
    lines.erase(lines.begin() + lineIndex + 1);
}
void Paragraph::renumberFrom(int startingNumber) {
    for (int i = 0; i < (int)lines.size(); i++) {
        lines[i].setLineNumber(startingNumber + i);
    }
}
ostream& operator<<(ostream& out, const Paragraph& para) {
    for (int i = 0; i < (int)para.lines.size(); i++) {
        out << para.lines[i] << endl;
    }
    return out;
}