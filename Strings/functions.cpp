# include "functions.h"

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    string input;
    string output;
    string details;
    cout << "Please enter obfuscated sentence: ";
    cin >> input;
    cout << "Please enter deobfuscation details: ";
    cin >> details;

    output = input;
    int index;
    int pos = 0;
    for (unsigned int i = 0; i < details.length(); i++) {
        index = (details.at(i) - '0');
        output.insert(pos + index, " ");
        pos += (details.at(i) - '0') + 1;
    }

    cout << "Deobfuscated sentence: " << output << endl;
}

void wordFilter() {
    // TODO
}

void passwordConverter() {
    string input;
    string output;
    cout << "Please enter your text input: ";
    cin >> input;
    cout << "input: " << input << endl;
    output = input;

    for (unsigned int i = 0; i < output.length(); i++) {
        char test = output.at(i);
        switch (test) {
            case 'a':
                output.at(i) = '@';
                break;
            case 'e':
                output.at(i) = '3';
                break;
            case 'i':
                output.at(i) = '!';
                break;
            case 'o':
                output.at(i) = '0';
                break;
            case 'u':
                output.at(i) = '^';
                break;
        }
    }

    int size = output.length();
    for (int i = size-1; i >= 0; i--) {
        output += output.at(i);
    }

    cout << "output: " << output << endl;

}

void wordCalculator() {
    // TODO
}

void palindromeCounter() {
    // TODO
}