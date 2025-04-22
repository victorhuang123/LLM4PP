#pragma once
#include <bits/stdc++.h>
using namespace std;

/* 算法说明：
   环形最大值问题解决方案，纯函数实现
   输入要求：
   - x 需为有序坐标数组
   - v 为对应位置的数值
   典型测试参数：
   N=5e5, C=1e18, x递增排列，v随机大数
*/

long long baseline(int N, long long C, vector<long long>& x, vector<long long>& v) {
    vector<long long> tmp_x(N), tmp_v(N), prefix(N+1);
    long long result = numeric_limits<long long>::min();

    // 双向处理循环
    for (int iteration = 0; iteration < 2; ++iteration) {
        // 复制当前方向数据
        for (int i = 0; i < N; ++i) {
            tmp_x[i] = x[i];
            tmp_v[i] = v[i];
        }

        // 计算前缀和
        prefix[0] = 0;
        for (int i = 0; i < N; ++i) {
            prefix[i+1] = prefix[i] + tmp_v[i];
        }

        // 逆向扫描求最大值
        long long max_reverse = numeric_limits<long long>::min();
        for (int i = N-1; i >= 0; --i) {
            // 直接计算两种路径方案
            const long long current = prefix[i+1] - tmp_x[i];
            if (current > result) result = current;
            
            const long long loop_case = current - tmp_x[i] + max_reverse;
            if (loop_case > result) result = loop_case;

            // 维护反向路径最大值
            const long long reverse_value = prefix[N] - prefix[i] + tmp_x[i] - C;
            if (reverse_value > max_reverse) max_reverse = reverse_value;
        }

        // 反转坐标处理反方向
        for (auto& pos : x) pos = C - pos;
        reverse(x.begin(), x.end());
        reverse(v.begin(), v.end());
    }

    return result;
}