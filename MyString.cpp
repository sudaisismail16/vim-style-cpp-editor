#include"MyString.h"


MyString::MyString() {
	this->length = 0;
	data = new char[length + 1] {};
}
MyString::MyString(const char* str) {
	data = nullptr;
	length = 0;
	this->allocateAndCopy(str);
}
MyString::MyString(const MyString& other) {
	this->length = other.length;
	data = nullptr;
	this->allocateAndCopy(other.data);
}
MyString::~MyString() {
	length = 0;
	delete[]data;
	data = nullptr;
}
MyString& MyString::operator=(const MyString& other) {
	if (this == &other) {
		return *this;
	}
	this->allocateAndCopy(other.data);
	return *this;
}
MyString& MyString::operator=(const char* str) {
	this->allocateAndCopy(str);
	return *this;
}
MyString MyString::operator+(const MyString& other) const {
	char* temp = new char[length + other.length + 1] {};
	for (int i = 0; i < length; i++) {
		temp[i] = data[i];
	}
	for (int i = 0; i < other.length; i++) {
		temp[length + i] = other.data[i];
	}
	MyString result(temp);
	delete[] temp;
	return result;
}
MyString& MyString::operator+=(const MyString& other) {
	char* temp = new char[length + other.length + 1] {};
	for (int i = 0; i < length; i++) {
		temp[i] = data[i];
	}
	for (int i = 0; i < other.length; i++) {
		temp[length + i] = other.data[i];
	}
	delete[] data;
	data = temp;
	length += other.length;
	return *this;
}
MyString& MyString::operator+=(char c) {
	insertAt(length, c);
	return *this;
}
bool MyString::operator==(const MyString& other) const {
	if (this->length != other.length) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (this->data[i] != other.data[i]) {
			return false;
		}
	}
	return true;
}
bool MyString::operator!=(const MyString& other) const {
	return !(*this == other);
}
char& MyString::operator[](int index) {
	return data[index];
}
char MyString::operator[](int index) const {
	return data[index];
}
int MyString::getLength() const {
	return length;
}
bool MyString::isEmpty() const {
	return length == 0;
}
const char* MyString::c_str() const {
	return data;
}
void MyString::insertAt(int index, char c) {
	char* temp = new char[length + 2] {};
	for (int i = 0; i < index; i++) {
		temp[i] = data[i];
	}
	temp[index] = c;
	for (int i = index; i < length; i++) {
		temp[i + 1] = data[i];
	}
	delete[] data;
	data = temp;
	length += 1;
}
void MyString::removeAt(int index) {
	char* temp = new char[length] {};
	for (int i = 0; i < index; i++) {
		temp[i] = data[i];
	}
	for (int i = index + 1; i < length; i++) {
		temp[i - 1] = data[i];
	}
	delete[] data;
	data = temp;
	length -= 1;
}
void MyString::clear() {
	delete[] data;
	length = 0;
	data = new char[1] {};
}
MyString MyString::substring(int start, int count) const {
	char* temp = new char[count + 1] {};
	for (int i = 0; i < count; i++) {
		temp[i] = data[start + i];
	}
	MyString result(temp);
	delete[] temp;
	return result;
}
int MyString::find(const MyString& pattern, int startIndex) const {
	if (pattern.length == 0) {
		return startIndex;
	}
	for (int i = startIndex; i <= length - pattern.length; i++) {
		bool match = true;
		for (int j = 0; j < pattern.length; j++) {
			if (data[i + j] != pattern.data[j]) {
				match = false;
				break;
			}
		}
		if (match == true) {
			return i;
		}
	}
	return -1;
}
void MyString::replaceAt(int index, int oldLen, const MyString& newStr) {
	for (int i = 0; i < oldLen; i++) {
		removeAt(index);
	}
	for (int i = 0; i < newStr.length; i++) {
		insertAt(index + i, newStr.data[i]);
	}
}

ostream& operator<<(ostream& out, const MyString& str) {
	out << str.c_str();
	return out;
}