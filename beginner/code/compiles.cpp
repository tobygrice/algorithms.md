#include <algorithm>
#include <set>
#include <vector>
using namespace std;
class Solution {
public:
    void balance_sets(multiset<double>& l_set, multiset<double>& r_set) {
        if (r_set.size() > l_set.size()) {
            double r_min = *r_set.begin();
            r_set.erase(r_min);
            l_set.insert(r_min);
        } else if (l_set.size() + 1 > r_set.size()) {
            double l_max = *l_set.rbegin();
            l_set.erase(l_max);
            r_set.insert(l_max);
        }
    }

    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans;
        ans.reserve(n);
        
        multiset<double> l_set, r_set;
        vector<int> init_window(nums.begin(), nums.begin() + k);
        sort(init_window.begin(), init_window.end());

        // build initial left set and right set
        int i = 0;
        int mid = (k % 2) ? k / 2 : (k / 2) + 1;
        for (i; i < mid; i++) l_set.insert(init_window[i]);
        for (i; i < k; i++) r_set.insert(init_window[i]);
        
        for (int l = 0, r = k; r <= n; l++, r++) {
            double median;
            if (l_set.size() == r_set.size()) {
                median = (*l_set.rbegin() + *r_set.begin()) / 2;
            } else {
                median = *l_set.rbegin();
            }
            ans.push_back(median);

            if (r >= n) break;

            // remove left value
            auto ind_in_lset = l_set.find(nums[l]);
            if (ind_in_lset != l_set.end()) {
                // element is in left set
                l_set.erase(ind_in_lset);
            } else {
                // element is in right set
                auto ind_in_rset = r_set.find(nums[l]);
                r_set.erase(ind_in_rset);
            }

            balance_sets(l_set, r_set);

            // insert right value
            if (nums[r] <= median) {
                l_set.insert(nums[r]);
            } else {
                r_set.insert(nums[r]);
            }

            balance_sets(l_set, r_set);
        }
    }
};

/*
sorted list from i to j
sorted list from i+1 to j+1 is the same, just need to insert j+1

can use multiset, remove value at i and insert value at j
then find median
- finding median is harder, cannot index into multiset, need to perform n/2 iterations through the set

solution: two multisets
m1 has lower half up to and including median
m2 has upper half following median

---

multisets can access by index, so everything above is useless.


// // Accesing the element at index i
// int i = 2;
// double median = *next(s.begin(), i);


*/