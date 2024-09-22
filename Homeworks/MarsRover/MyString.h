# ifndef MYSTRING_H
# define MYSTRING_H

# include <iostream>

typedef unsigned long size_t;
using namespace std;

class MyString {
    private:
        size_t strsize;
        size_t strcapacity;
        char* string;
    public:
        MyString();
        MyString(const MyString& str);
        MyString(const char* s);
        ~MyString() {delete[] string;};
        void resize (int n) {strsize = n;};
        size_t capacity() const {return strcapacity;};
        size_t size() const {return strsize;};
        size_t length() const {return strsize;};
        const char* data() const {return string;};
        bool empty() const {return this->length() == 0;};
        const char& front() const {return string[0];};
        const char& at (int pos) const;
        void clear();
        friend ostream& operator<< (ostream& os, const MyString& str);
        MyString& operator= (const MyString& str);
        MyString& operator+= (const MyString& str);
        size_t find (const MyString& str, size_t pos = 0) const noexcept;
        friend bool operator== (const MyString& lhs, const MyString& rhs) noexcept;
        friend MyString operator+ (const MyString& lhs, const MyString& rhs);
};

# endif
