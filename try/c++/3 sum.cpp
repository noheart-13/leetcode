#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::ranges::sort(nums);
        vector<vector<int>> ans;
		int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            int x = nums[i];
            if (i&&x == nums[i - 1]) continue;
            if (x + nums[i + 1] + nums[i + 2] > 0) break;
            if (x+nums[n - 2]+nums[n - 1] < 0) continue;
			int j = i + 1, k = n - 1;
            while (j < k) {
                int s = x + nums[j] + nums[k];
                if (s == 0) {
                    ans.push_back({x, nums[j], nums[k]});
                    while (j < k && nums[j] == nums[j + 1]) ++j;
                    while (j < k && nums[k] == nums[k - 1]) --k;
                    ++j; --k;
                } else if (s < 0) {
                    ++j;
                } else {
                    --k;
                }
			}
        }
        return ans;
    }
};