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

vector<string> convert_string_to_vector(const string &s)
{
    vector<string> v;
    string line;
    for (char c: s)
    {
        if (c == '\n')
        {
            v.push_back(line);
            line = "";
        }
        else
        {
            line += c;
        }
    }
    return v;
}

vector<string> read_text_file_vec(const string &filename)
{
    string content;
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
        content += line + "\n";
    }
    return convert_string_to_vector(content);
}

void write_text_file(const string &filename, const string &content)
{
    std::ofstream file(filename);
    file << content;
}

void write_text_file_vec(const string &filename, const vector<string> &content)
{
    write_text_file(filename, convert_vector_to_string(content));
}

vector<string> split(const string &s, const string &delimiter)
{
    vector<string> v;
    string line;
    for (char c: s)
    {
        if (c == delimiter[0])
        {
            v.push_back(line);
            line = "";
        }
        else
        {
            line += c;
        }
    }
    return v;
}


// The below code is out of commission until I can figure out how to get the thing working

/*
string find_and_replace(const string &s, const string &find, const string &replace)
{
    string new_s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == find[0])
        {
            new_s += replace;
        }
        else
        {
            new_s += s[i];
        }
    }
    return new_s;
}
*/

int main()
{
    print("This script does a lot more than you think!");
    print("It can read and write files, split strings, etc!");
    print("It can even print vectors!");
    return 0;
}
