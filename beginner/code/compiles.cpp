#include <iostream>
#include <vector>
#include <algorithm> // for std::is_sorted
#include <random>
#include <sstream>
#include <cassert>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <queue>


using namespace std;

int trap(vector<int>& height) {
    int n = height.size();

    vector<pair<int, int>> tallest_wall_after(n);
    for (int i = 0; i < n; i++) {
        int elevation_between = 0;
        int max_height = i + 1;
        for (int j = i + 1; j < n; j++) {
            if (height[j] >= height[i]) {
                tallest_wall_after[i] = {j, elevation_between};
                break;
            } else if (height[j] >= height[max_height]) {
                tallest_wall_after[i] = {j, elevation_between};
                max_height = j;
            } 
            elevation_between += height[j];
        }
    }

    int total_capacity = 0;
    int i = 0;
    while (i < n - 1) {
        int next_tallest_wall = tallest_wall_after[i].first;
        int elevation_between = tallest_wall_after[i].second;

        int width = (next_tallest_wall - i - 1);
        // if (width < 0) width = 0;
        int h_i = height[i];
        int h_ntw = height[next_tallest_wall];
        int height = min(h_i, h_ntw);
        int capacity = (width * height) - elevation_between;
        total_capacity += max(0, capacity);

        cout << "From wall " << i << " to wall " << next_tallest_wall << endl;
        cout << "Capacity = " << width << " * " << height << " - " << elevation_between 
        << " = " << (width * height) - elevation_between << endl;
        cout << "Current total = " << total_capacity << endl;

        i = next_tallest_wall;
    }

    return total_capacity;
}

int main() {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(height) << endl;
    return 0;
}