#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

typedef long long int ll;

ll baseline(int N) {
    const int MOD = 1e9 + 7;
    vector<string> perms;
    map<string, ll> M[110];
    string ch[] = { "A", "C", "G", "T" };

    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
            for (int c = 0; c < 4; c++)
                perms.push_back(ch[a] + ch[b] + ch[c]);

    auto can_add_c = [](string p) {
        bool b1 = p[0] == 'A' && (p[1] == 'G' || p[2] == 'G');
        bool b2 = p[1] == 'A' && p[2] == 'G';
        bool b3 = p[2] == 'A' && p[1] == 'G';
        return !(b1 || b2 || b3);
    };

    auto can_add_g = [](string p) {
        return !(p[1] == 'A' && p[2] == 'C');
    };

    auto valid = [](string p) {
        if (p == "AGC" || p == "ACG" || p == "GAC") return false;
        return true;
    };

    for (int i = 0; i < perms.size(); i++) {
        if (valid(perms[i])) M[3][perms[i]] = 1;
    }

    for (int i = 4; i <= N; i++) {
        for (int j = 0; j < perms.size(); j++) {
            string p = perms[j];
            string q = p.substr(1);
            ll cnt = M[i - 1][p];
            vector<int> can = { 0, 3 };
            if (can_add_c(p)) can.push_back(1);
            if (can_add_g(p)) can.push_back(2);
            for (int z : can) {
                string tmp = q + ch[z];
                M[i][tmp] = (M[i][tmp] + cnt) % MOD;
            }
        }
    }

    ll ans = 0;
    for (auto it = M[N].begin(); it != M[N].end(); it++) ans = (ans + it->second) % MOD;
    return ans;
}