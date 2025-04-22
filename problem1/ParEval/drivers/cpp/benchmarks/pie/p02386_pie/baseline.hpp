#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

class Dice {
private:
    map<char, string> mp;
public:
    string d = "RENSWL";
    vector<int> v; //UFRLBD:123456
    Dice() {
        init();
        v.resize(6);
    };
    Dice(vector<int> v) :v(v) {
        init();
    };
    void init(){
        mp[d[0]] = "2354";
        mp[d[1]] = "1463";
        mp[d[2]] = "1265";
        mp[d[3]] = "1562";
        mp[d[4]] = "1364";
        mp[d[5]] = "2453";
    }
    void roll(char c) { roll(mp[c]); }
    void roll(string s) {
        int tmp = v[s[0] - '1'];
        for (size_t i = 1; i < s.size(); i++) v[s[i - 1] - '1'] = v[s[i] - '1'];
        v[s[s.size() - 1] - '1'] = tmp;
    }
    bool operator==(const Dice &D)const { return v == D.v; }
};

bool baseline(vector<Dice> &D) {
    int n = D.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < 1000; k++) {
                if (D[i] == D[j]) {
                    return false;
                }
                D[j].roll( D[j].d[rand() % 6] );
            }
        }
    }
    return true;
}

vector<Dice> generateInput() {
    vector<Dice> diceList;
    for (int i = 0; i < 1000; i++) {
        vector<int> faces = {rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1};
        diceList.push_back(Dice(faces));
    }
    return diceList;
}