# include "MyString.h"
# include <iostream>
# include <stdexcept>

using namespace std;

MyString::MyString() : strcapacity(1), strsize(0), string(new char[1]{'\0'}) {
}
MyString::MyString(const MyString& str) : strsize(str.size()), strcapacity(str.capacity()), string(new char[strcapacity]) {
    for (size_t i = 0; i < str.size(); i++) {
        string[i] = str.at(i);
    }
    string[strsize] = '\0';
}
MyString::MyString(const char* s) {
    strsize = 0;
    while (s[strsize] != '\0') {
        strsize++;
    }
    strcapacity = strsize + 1;
    string  = new char[strcapacity];
    for (size_t i = 0; i < strsize; i++) {
        string[i] = s[i];
    }
    string[strcapacity - 1] = '\0';
}
const char& MyString::at(int pos) const {
    if (pos < 0 || pos >= strsize) {
        throw out_of_range("Invalid value");
    }
    return string[pos];
}
void MyString::clear() {
    delete[] string;
    string = new char[1];
    string[0] = '\0';
    strsize = 0;
    strcapacity = 1;
}
ostream& operator<< (ostream& os, const MyString& str) {
    os << str.data();
    return os;
}
size_t MyString::find (const MyString& str, size_t pos) const noexcept {

    while (string[pos] != '\0') {
        if (string[pos] == str.at(0)) {
            for (size_t i = 1; i < str.size(); i++) {
                if (string[pos + i] != str.at(i)) {
                    return -1;
                }
            }
            return pos;
        }
        pos++;
    }
    return -1;
}
MyString& MyString::operator= (const MyString& str) {
    delete[] string;
    string = new char[str.capacity()];
    this->strcapacity = str.capacity();
    this->strsize = str.size();
    for (size_t i = 0; i < str.size(); i++) {
        string[i] = str.at(i);
    }
    string[strsize] = '\0';
    return *this;
}
MyString& MyString::operator+= (const MyString& str) {
    char* temp = new char[str.size() + strsize + 1];
    for (size_t i = 0; i < strsize; i++) {
        temp[i] = string[i];
    }
    for (size_t i = 0; i < str.size(); i++) {
        temp[i + strsize] = str.at(i);
    }
    temp[str.size() + strsize] = '\0';
    delete[] string;
    this->strsize = str.size() + strsize;
    this->strcapacity = this->strsize + 1;
    this->string = temp;
    return *this;
}
bool operator== (const MyString& lhs, const MyString& rhs) noexcept {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    else {
        for (size_t i = 0; i < lhs.size(); i++) {
            if(lhs.at(i) != rhs.at(i)) {
                return false;
            }
        }
        return true;
    }
}
MyString operator+ (const MyString& lhs, const MyString& rhs) {
    char* temp = new char[lhs.size() + rhs.size() + 1];
    for (size_t i = 0; i < lhs.size(); i++) {
        temp[i] = lhs.at(i);
    }
    for (size_t i = 0; i < rhs.size(); i++) {
        temp[lhs.size() + i] = rhs.at(i);
    }
    temp[lhs.size() + rhs.size()] = '\0';
    MyString result(temp);
    delete[] temp;
    temp = nullptr;
    return result;
}