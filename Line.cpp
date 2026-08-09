#include"Line.h"

Line::Line() {
	lineNumber = 0;
	content.clear();
}
Line::Line(const MyString& text) {
	content = text;
}
Line::Line(const char* text) {
	content = text;
}
Line::Line(const Line& other) {
	lineNumber = other.lineNumber;
	this->content = other.content;
}
Line::~Line() {
	this->clear();
}
Line& Line::operator=(const Line& other) {
	if (this == &other) {
		return *this;
	}
	this->lineNumber = other.lineNumber;
	this->content = other.content;
	return *this;
}
MyString Line::getContent() const {
	return content;
}
void Line::setContent(const MyString& text) {
	this->content = text;
}
int Line::getLength() const {
	return content.getLength();
}
bool Line::isEmpty() const {
	return content.isEmpty();
}
void Line::clear() {
	content.clear();
}
void Line::insertChar(int col, char c) {
	content.insertAt(col, c);
}
void Line::deleteChar(int col) {
	content.removeAt(col);
}
void Line::deleteToEnd(int col) {
	int len = content.getLength();
	for (int i = len - 1; i >= col; i--) {
		content.removeAt(i);
	}
}
void Line::toggleCase(int col) {
	char c = content[col];
	if (c >= 'a' && c <= 'z') {
		content[col] = c - 'a' + 'A';
	}
	else if (c >= 'A' && c <= 'Z') {
		content[col] = c - 'A' + 'a';
	}
}
bool isWordChar(char c) {
	if (c >= 'a' && c <= 'z') {
		return true;
	}
	if (c >= 'A' && c <= 'Z') {
		return true;
	}
	if ((c >= '0' && c <= '9') || c == '_') {
		return true;
	}
	return false;
}
int Line::nextWordStart(int col) const {
	int len = content.getLength();
	int i = col;
	while (i < len && isWordChar(content[i])) {
		i++;
	}
	while (i < len && !isWordChar(content[i])) {
		i++;
	}
	return i; 
}
int Line::prevWordStart(int col) const {
	int i = col - 1;
	while (i >= 0 && !isWordChar(content[i])) {
		i--;
	}
	while (i >= 0 && isWordChar(content[i - 1 >= 0 ? i - 1 : 0]) && i > 0) {
		i--;
	}
	if (i < 0) {
		return 0;
	}
	return i;
}
int Line::startOfLine() const {
	return 0;
}
int Line::endOfLine() const {
	return content.getLength() - 1;
}
int Line::find(const MyString& pattern, int startCol) const {
	return content.find(pattern, startCol);
}
void Line::setLineNumber(int num) {
	lineNumber = num;
}
int Line::getLineNumber() const {
	return lineNumber;
}
ostream& operator<<(ostream& out, const Line& line) {
	out << line.content;
	return out;
}