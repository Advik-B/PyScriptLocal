#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void print(const string text, bool flush = false, bool newline = true, string endl="\n") {
    for (char s: text){
        cout << s;
    }
    if (newline) cout << endl;
    if (flush) cout.flush();
}

void print_vector(const vector<string> &v, bool flush = false, bool newline = true) {
    for (string s: v){
        print(s, flush, newline);
    }
}

int main()
{
    string text {"A long time ago in a galaxy far, far away..."};
    print(text);
    return 0;
}
