#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::ranges::sort(nums);
        int n = nums.size();
        int s = nums[n - 1] + nums[n - 2] + nums[n - 3];
        int diffs;
        for (int i = 0; i < n - 2; i++) {
            int x = nums[i], j = i + 1, k = n - 2;
            while (j < k) {
                int closenset = x + nums[j] + nums[k];
                int diff = std::abs(closenest - target);
                if (diff == 0)
                    return target;
                else  if (closenest < target) {
                    j++;
                }
                else {
                    k--;
                }
                if (diff < diffs) {
                    diffs = diff;
                    s = x + nums[j] + nums[k];
                }
            }
        }
        return s;
    }
};