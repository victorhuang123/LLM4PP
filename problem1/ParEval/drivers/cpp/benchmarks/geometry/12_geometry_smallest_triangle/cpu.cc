// Driver for 12_geometry_smallest_triangle for Serial, OpenMP, MPI, and MPI+OpenMP
// struct Point {
//     double x, y;
// };
//
// double triangleArea(Point const& A, Point const& B, Point const& C) {
//   return 0.5 * std::abs( A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y) );
// }
//
// /* Return the area of the smallest triangle that can be formed by any 3 points.
//    Example:
//
//    input: [{0, 10}, {5, 5}, {1,0}, {-1, 1}, {-10, 0}]
//    output: 5.5
// */
// double smallestArea(std::vector<Point> const& points) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "generated-code.hpp"   // code generated by LLM
#include "baseline.hpp"

struct Context {
    std::vector<baseline::Point> points;
    std::vector<generated::Point> points_test;
    std::vector<double> x, y;
};

void reset(Context *ctx) {
    fillRand(ctx->x, -1000.0, 1000.0);
    fillRand(ctx->y, -1000.0, 1000.0);
    BCAST(ctx->x, DOUBLE);
    BCAST(ctx->y, DOUBLE);

    for (size_t i = 0; i < ctx->points.size(); i++) {
        ctx->points[i].x = ctx->x[i];
        ctx->points[i].y = ctx->y[i];
        ctx->points_test[i].x = ctx->x[i];
        ctx->points_test[i].y = ctx->y[i];
    }
}

Context *init() {
    Context *ctx = new Context();

    ctx->points.resize(DRIVER_PROBLEM_SIZE);
    ctx->points_test.resize(DRIVER_PROBLEM_SIZE);
    ctx->x.resize(DRIVER_PROBLEM_SIZE);
    ctx->y.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    double area = generated::smallestArea(ctx->points_test);
    (void)area;
}

void NO_OPTIMIZE best(Context *ctx) {
    double area = baseline::smallestArea(ctx->points);
    (void)area;
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<baseline::Point> points(TEST_SIZE);
    std::vector<generated::Point> points_test(TEST_SIZE);
    std::vector<double> x(TEST_SIZE), y(TEST_SIZE);
    double correct = 0.0, test = 0.0;

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(x, -1000.0, 1000.0);
        fillRand(y, -1000.0, 1000.0);
        test = 0.0;
        correct = 0.0;
        BCAST(x, DOUBLE);
        BCAST(y, DOUBLE);

        for (size_t i = 0; i < points.size(); i++) {
            points[i].x = x[i];
            points[i].y = y[i];
            points_test[i].x = x[i];
            points_test[i].y = y[i];
        }

        // compute correct result
        correct = baseline::smallestArea(points);

        // compute test result
        test = generated::smallestArea(points_test);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank) && std::abs(correct - test) > 1e-4) {
            isCorrect = false;
        }
        BCAST_PTR(&isCorrect, 1, CXX_BOOL);
        if (!isCorrect) {
            return false;
        }
    }

    return true;
}

void destroy(Context *ctx) {
    delete ctx;
}
