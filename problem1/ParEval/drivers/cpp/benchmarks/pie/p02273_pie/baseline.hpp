#pragma once

#include<vector>
#include<queue>
#include<cmath>
#include<utility>

using namespace std;

typedef pair<double, double> P;

vector<P> baseline(int N) {
    queue<P> S;
    S.push(make_pair(0, 0));
    S.push(make_pair(100.0, 0));
    P s, t;

    for (; N--;) {
        s = S.front(); S.pop();
        queue<P> T;
        do {
            t = S.front(); S.pop();
            P s1 = make_pair(s.first + (t.first - s.first) / 3, s.second + (t.second - s.second) / 3);
            P s2 = make_pair(s.first + (t.first - s.first) / 3 * 2, s.second + (t.second - s.second) / 3 * 2);

            T.push(s);
            T.push(s1);

            T.push(make_pair(s1.first + (s2.first - s1.first) * cos(M_PI / 3.0) - (s2.second - s1.second) * sin(M_PI / 3.0),
                            s1.second + (s2.first - s1.first) * sin(M_PI / 3.0) + (s2.second - s1.second) * cos(M_PI / 3.0)));
            T.push(s2);
            s = t;
        } while (!S.empty());
        T.push(t);
        S = T;
    }

    vector<P> result;
    while (!S.empty()) {
        result.push_back(S.front());
        S.pop();
    }
    return result;
}

vector<P> generateInput() {
    return baseline(10); // Example input with N=10 to maximize problem scale
}