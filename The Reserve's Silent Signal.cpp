#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    long long x, y;
    };

    // Squared Euclidean distance between two points
    inline long long distSq(const Point& a, const Point& b) {
        long long dx = a.x - b.x;
            long long dy = a.y - b.y;
                return dx * dx + dy * dy;
                }

                int main() {
                    // Fast I/O
                        ios_base::sync_with_stdio(false);
                            cin.tie(NULL);

                                int n;
                                    if (!(cin >> n) || n < 2) return 0;

                                        vector<Point> points(n);
                                            for (int i = 0; i < n; ++i) {
                                                    cin >> points[i].x >> points[i].y;
                                                        }

                                                            // Sort points primarily by x-coordinate, secondary by y-coordinate
                                                                sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                                                                        if (a.x != b.x) return a.x < b.x;
                                                                                return a.y < b.y;
                                                                                    });

                                                                                        // Check for exact duplicates first (distance = 0)
                                                                                            for (int i = 0; i < n - 1; ++i) {
                                                                                                    if (points[i].x == points[i + 1].x && points[i].y == points[i + 1].y) {
                                                                                                                cout << 0 << "\n";
                                                                                                                            return 0;
                                                                                                                                    }
                                                                                                                                        }

                                                                                                                                            // Custom comparator for the active set (ordered primarily by y, then x)
                                                                                                                                                auto cmpY = [](const Point& a, const Point& b) {
                                                                                                                                                        if (a.y != b.y) return a.y < b.y;
                                                                                                                                                                return a.x < b.x;
                                                                                                                                                                    };

                                                                                                                                                                        set<Point, decltype(cmpY)> active_set(cmpY);

                                                                                                                                                                            long long min_d2 = distSq(points[0], points[1]);
                                                                                                                                                                                active_set.insert(points[0]);
                                                                                                                                                                                    active_set.insert(points[1]);

                                                                                                                                                                                        int left = 0;

                                                                                                                                                                                            for (int i = 2; i < n; ++i) {
                                                                                                                                                                                                    Point current = points[i];

                                                                                                                                                                                                            // Maintain the sliding window: remove points with dx^2 >= min_d2
                                                                                                                                                                                                                    while (left < i) {
                                                                                                                                                                                                                                long long dx = current.x - points[left].x;
                                                                                                                                                                                                                                            if (dx * dx >= min_d2) {
                                                                                                                                                                                                                                                            active_set.erase(points[left]);
                                                                                                                                                                                                                                                                            left++;
                                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                                                        break;
                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                                    // Only inspect candidate points in active_set within dy in [-ceil(sqrt(min_d2)), ceil(sqrt(min_d2))]
                                                                                                                                                                                                                                                                                                                                            long long d = static_cast<long long>(ceil(sqrt(static_cast<double>(min_d2))));
                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                            Point lower_bound_pt = {current.x, current.y - d};
                                                                                                                                                                                                                                                                                                                                                                    Point upper_bound_pt = {current.x, current.y + d};

                                                                                                                                                                                                                                                                                                                                                                            auto it_start = active_set.lower_bound(lower_bound_pt);
                                                                                                                                                                                                                                                                                                                                                                                    auto it_end = active_set.upper_bound(upper_bound_pt);

                                                                                                                                                                                                                                                                                                                                                                                            for (auto it = it_start; it != it_end; ++it) {
                                                                                                                                                                                                                                                                                                                                                                                                        min_d2 = min(min_d2, distSq(current, *it));
                                                                                                                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                                                                                                                        active_set.insert(current);
                                                                                                                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                                                                                                                                cout << min_d2 << "\n";

                                                                                                                                                                                                                                                                                                                                                                                                                                    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                
