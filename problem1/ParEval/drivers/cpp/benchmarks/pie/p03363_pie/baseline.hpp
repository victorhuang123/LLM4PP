#pragma once

#include<vector>
#include<cstring>
#define ll long long
#define Hsize 100009
#define MAXN 210001

struct T {
    ll number, times;
    int next;
};

int hashFunc(ll x) {
    if (x < 0) x = -x;
    return (x % 100007);
}

void addToHash(ll sumZ, std::vector<T>& hashBucket, std::vector<int>& hashIndex, int &top) {
    int index, HsumZ, beginP;
    HsumZ = hashFunc(sumZ);
    for (beginP = index = hashIndex[HsumZ]; index > 0; index = hashBucket[index].next)
        if (hashBucket[index].number == sumZ) {
            hashBucket[index].times += 1;
            return;
        }
    hashIndex[HsumZ] = (++top);
    hashBucket[top].number = sumZ;
    hashBucket[top].times = 1;
    hashBucket[top].next = beginP;
}

ll baseline(int N, const std::vector<int>& Ai) {
    std::vector<T> hashBucket(MAXN, {-1, 0, 0});
    std::vector<int> hashIndex(Hsize, 0);
    int top = 0;
    ll sumZ = 0;
    addToHash(0, hashBucket, hashIndex, top);
    for (int i = 0; i < N; ++i) {
        sumZ = sumZ + Ai[i];
        addToHash(sumZ, hashBucket, hashIndex, top);
    }

    ll answer = 0;
    for (int i = 1; i <= top; ++i)
        answer = answer + (((hashBucket[i].times) * (hashBucket[i].times - 1)) >> 1;
    return answer;
}

std::vector<int> generateInput() {
    std::vector<int> input(100000, 1);
    return input;
}