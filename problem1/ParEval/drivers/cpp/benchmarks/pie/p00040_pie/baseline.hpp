#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

string baseline(const string& inputCode, int n) {
    map<int, char> AlphabetTable;
    map<int, int> table;

    auto decode = [&](char a) {
        int z = a - 'a';
        for(int i = 0; i < 26; i++){
            if(table[i] == z) return AlphabetTable[i];
        }
        return '\0';
    };

    auto makeTable = [&](int a, int b) {
        for(int i = 0; i < 26; i++){
            table[i] = (a*i+b) % 26;
        }
    };

    auto makeAlphabetTable = [&]() {
        char c = 'a';
        for(int i = 0; i < 26; i++){
            AlphabetTable[i] = c;
            c++;
        }
    };

    makeAlphabetTable();
    for(int i = 0; i < n; i++){
        string code = inputCode;
        string tmp = code;
        for(int b = 0; b < 26; b++){
            for(int a = 1; a < 26; a+=2){
                if(a%13 != 0){
                    makeTable(a, b);
                    code = tmp;
                    for(int j = 0; j < code.length(); j++){
                        if('a' <= code[j] && code[j] <= 'z'){
                            code[j] = decode(code[j]);
                        }
                    }
                    if(code.find("this") != string::npos || code.find("that") != string::npos){
                        return code;
                    }
                }
            }
        }
    }
    return "";
}

vector<string> generateExampleInput() {
    vector<string> inputs;
    string largeInput(1000000, 'a'); // Create a large input string
    inputs.push_back(largeInput);
    inputs.push_back("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    return inputs;
}