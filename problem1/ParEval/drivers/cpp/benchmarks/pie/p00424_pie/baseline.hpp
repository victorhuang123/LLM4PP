#pragma once

#include <map>
#include <string>

using namespace std;

string baseline(int N, int M, char A, char B, char C) {
    map<char, char> converse;

    for (char i = '0'; i <= 'z'; i++) {
        converse[i] = i;
    }

    for (int i = 0; i < N; i++) {
        converse[A] = B;
    }

    string result;
    for (int i = 0; i < M; i++) {
        result += converse[C];
    }

    return result;
}