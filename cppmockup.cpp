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

void print(const string text, bool flush = false, bool newline = true, string endl="\n")
{
    for (char s: text){
        cout << s;
    }
    if (newline) cout << endl;
    if (flush) cout.flush();
}

void print_vector(const vector<string> &v, bool flush = false, bool newline = true)
{
    for (string s: v){
        print(s, flush, newline);
    }
}

vector<string> read_text_file_vec(const string &filename)
{
    vector<string> lines;
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

string convert_vector_to_string(const vector<string> &v)
{
    string s;
    for (string line: v)
    {
        s += line + "\n";
    }
    return s;
}

string read_text_file(const string &filename)
{
    string content;
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
        content += line + "\n";
    }
    return content;

}

int main()
{
    print("This script does a lot more than you think!");
    return 0;
}
