#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string sum(string a, string b) {
    if (a.size() > b.size()) swap(a, b);
    int c = 0;
    
    string res = "";
    for (int i = 0; i < a.size(); i++) {
        int x = a[a.size() - 1 - i] - '0' + b[b.size() - 1 - i] - '0' + c;
        res.push_back(x % 10 + '0');
        c = x / 10;
    }
    for (int i = a.size(); i < b.size(); i++) {
        int x = b[b.size() - 1 - i] - '0' + c;
        res.push_back(x % 10 + '0');
        c = x / 10;
    }
    if (c > 0) res.push_back(c + '0');
    
    reverse(res.begin(), res.end());
    return res;
}

string kake(string a, string b) {
    if (a == "0" || b == "0") return "0";
    string res = "";
    if (a.size() > b.size()) swap(a, b);
    
    string s = "0";
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            int tmp = (a[a.size() - j - 1] - '0') * (b[b.size() - i - 1] - '0');
            if (tmp > 0) {
                stringstream ss;
                ss << tmp;
                for (int k = 0; k < j; k++) ss << "0";
                s = sum(s, ss.str());
            }
        }
        res.push_back(s[s.size() - 1]);
        s.erase(s.end() - 1);
        if (s.empty()) s = "0";
    }
    
    while (s != "0") {
        res.push_back(s[s.size() - 1]);
        
        s.erase(s.end() - 1);
        if (s.empty()) s = "0";
    }
    reverse(res.begin(), res.end());
    return res;
}

string pow(string x, int n) {
    if (n == 0) return "1";
    string res = pow(kake(x, x), n / 2);
    if (n & 1) res = kake(res, x);
    return res;
}

string baseline(string m, int n) {
    string num = pow(m, n);
    int pos = (num.size() - 1) / 4;
    string result = num.substr(0, (num.size() - 1) % 4 + 1) + jin[pos];
    while (--pos >= 0) {
        string out = num.substr((num.size() - 1) % 4 + 1 + ((num.size() - 1) / 4 - pos - 1) * 4, 4);
        if (atoi(out.c_str()) > 0) result += to_string(atoi(out.c_str())) + jin[pos];
    }
    return result;
}

vector<string> generateInput() {
    return {"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", "100"};
}