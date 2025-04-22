#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>

// 生成随机输入数据的函数


// 核心算法实现
std::vector<int> baseline(int n, const std::vector<int>& data) {
    // 创建带索引的数据结构
    std::vector<std::pair<int, int>> indexed_data;
    indexed_data.reserve(n);
    for (int i = 0; i < n; ++i) {
        indexed_data.emplace_back(data[i], i);
    }

    // 按数值排序确定中位数分界
    std::sort(indexed_data.begin(), indexed_data.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    // 计算两个中位数值
    const int right_median = indexed_data[n/2].first;
    const int left_median = indexed_data[(n-1)/2].first;

    // 构建结果数组
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        // 根据排序位置选择中位数值
        const int original_index = indexed_data[i].second;
        result[original_index] = (i < n/2) ? right_median : left_median;
    }

    return result;
}