#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        std::ranges::sort(nums);
        int left = 0, right = nums.size() - 1, ans = 0;
        while (left < right) {
            if (nums[left] + nums[right] < target) {
                ans += right - left;
                left++;
            }
            else {
                right--;
            }
        }
        return ans;
    }
};
