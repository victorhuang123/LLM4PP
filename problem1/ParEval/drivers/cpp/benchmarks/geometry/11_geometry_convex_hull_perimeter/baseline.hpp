#pragma once
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    double x, y;
};

/* Return the perimeter of the smallest convex polygon that contains all the points.
   Handles duplicates, collinear points, and general boundary conditions.
   Example:
   input: [{0,3}, {1,1}, {2,2}, {4,4}, {0,0}, {1,2}, {3,1}, {3,3}]
   output: 13.4477
*/
double NO_INLINE convexHullPerimeter(std::vector<Point> const& points) {
    if (points.size() < 3) {
        return 0.0;
    }

    // 去重 & 排序
    std::vector<Point> pts = points;
    std::sort(pts.begin(), pts.end(), [](auto &a, auto &b){
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });
    pts.erase(std::unique(pts.begin(), pts.end(), [](auto &a, auto &b){
        return std::fabs(a.x - b.x) < 1e-12 && std::fabs(a.y - b.y) < 1e-12;
    }), pts.end());
    if (pts.size() < 2) {
        return 0.0;
    }

    auto cross = [](Point const& a, Point const& b, Point const& c) {
        // 叉积
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    };
    auto dist = [](Point const& p1, Point const& p2) {
        return std::hypot(p2.x - p1.x, p2.y - p1.y);
    };

    // 分别构造下凸包与上凸包
    std::vector<Point> lower, upper;
    for (auto &p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower.back(), p) <= 1e-12) {
            lower.pop_back();
        }
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper.back(), pts[i]) <= 1e-12) {
            upper.pop_back();
        }
        upper.push_back(pts[i]);
    }
    // 去掉末尾重复点
    lower.pop_back();
    upper.pop_back();

    // 生成凸包
    std::vector<Point> hull;
    hull.reserve(lower.size() + upper.size());
    hull.insert(hull.end(), lower.begin(), lower.end());
    hull.insert(hull.end(), upper.begin(), upper.end());

    // 计算周长
    double perimeter = 0.0;
    for (size_t i = 0; i < hull.size(); i++) {
        perimeter += dist(hull[i], hull[(i + 1) % hull.size()]);
    }
    return perimeter;
}
