#pragma once
#include <vector>
#include <algorithm>

struct Point {
    double x, y;
};

/* Find the set of points that defined the smallest convex polygon that contains all the points in the vector points. Store the result in `hull`.
   Example:

   input: [{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}]
   output: [{0, 3}, {4, 4}, {3, 1}, {0, 0}]
*/

inline double cross(Point const& a, Point const& b, Point const& c) {
    static const double EPS = 1e-9;
    double crossVal = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return crossVal;
}

void NO_INLINE convexHull(std::vector<Point> const& points, std::vector<Point>& hull) {

    if (points.size() < 3) {
        hull = points;
        return;
    }


    std::vector<Point> pts = points;
    std::sort(pts.begin(), pts.end(), [](auto &a, auto &b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });
    pts.erase(std::unique(pts.begin(), pts.end(), [](auto &a, auto &b){
        return std::fabs(a.x - b.x) < 1e-12 && std::fabs(a.y - b.y) < 1e-12;
    }), pts.end());
    if (pts.size() < 3) {
        hull = pts;
        return;
    }


    std::vector<Point> lower, upper;

    for (auto &p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < -1e-9) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    for (int i = (int)pts.size() - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), pts[i]) < -1e-9) {
            upper.pop_back();
        }
        upper.push_back(pts[i]);
    }


    lower.pop_back();
    upper.pop_back();
    hull.clear();
    hull.reserve(lower.size() + upper.size());
    hull.insert(hull.end(), lower.begin(), lower.end());
    hull.insert(hull.end(), upper.begin(), upper.end());
}
