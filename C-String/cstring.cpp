#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    count++;
  }
  return count;
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == character) {
      return i;
    }
    count++;
  }
  return count;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  for (int i = 0; str1[i] != '\0'; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}