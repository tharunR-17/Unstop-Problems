#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// A structure to represent a point
struct Point {
    int x, y;
    int index; // To preserve the original order for tie-breaking

    // Calculate and return the squared distance from origin
    int distanceSquared() const {
        return x * x + y * y;
    }
};

// Comparator function for sorting
bool comparePoints(const Point& a, const Point& b) {
    int distA = a.distanceSquared();
    int distB = b.distanceSquared();

    // First, compare distances
    if (distA != distB) {
        return distA < distB;
    }

    // If distances are equal, use the original index
    return a.index < b.index;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<Point> points(N);

    // Read input points
    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].index = i;
    }

    // Sort points based on distance from origin and tie-breaking by index
    sort(points.begin(), points.end(), comparePoints);

    // Output the K nearest points
    for (int i = 0; i < K; i++) {
        cout << points[i].x << " " << points[i].y << endl;
    }

    return 0;
}
