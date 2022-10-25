#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::ifstream;
using std::getline;

// using for file I/O

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

vector<string> read_text_file(const string &filename) {
    vector<string> lines;
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    // Read the bee movie script
    vector<string> lines = read_text_file("bee_movie_script.txt");
    print_vector(lines);
    print("Done", true);
    return 0;
}
