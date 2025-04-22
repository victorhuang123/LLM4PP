#pragma once

#include <vector>
#include <string>
#include <algorithm>

struct process {
    std::string name;
    int time;
};

int baseline(int n, int q, const std::vector<process>& processes) {
    std::vector<process> Q = processes;
    int total_time = 0;
    int head = 0, tail = n;

    while (head != tail) {
        process crt = Q[head];
        head = (head + 1) % n;
        int need = std::min(crt.time, q);
        crt.time -= need;
        total_time += need;
        if (crt.time > 0) {
            Q[tail] = crt;
            tail = (tail + 1) % n;
        }
    }
    return total_time;
}

std::vector<process> generateInput(int n) {
    std::vector<process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i] = {"p" + std::to_string(i + 1), (i + 1) * 10};
    }
    return processes;
}