#include <iostream>
#include <string>

using std::cout;
using std::string;

void print(const string text, bool flush = false, bool newline = true) {
    for (char s: text){
        cout << s;
    }
    if (newline) cout << "\r\n";
    if (flush) cout.flush();
}