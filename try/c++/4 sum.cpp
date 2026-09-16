#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        ranges::sort(nums);
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n - 3; i++) {
            long long x = nums[i];
            if (i > 0 && x == nums[i - 1]) continue;
            if (x + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
            if (x + nums[n - 1] + nums[n - 2] + nums[n - 3] < target) continue;
            for (int j = i + 1; j < n - 2; j++) {
                long long y = nums[j];
                if (j > i + 1 && y == nums[j - 1]) continue;
                if (x + y + nums[j + 1] + nums[j + 2] > target) break;
                if (x + y + nums[n - 2] + nums[n - 1] < target) continue;
                int k = j + 1, l = n - 1;
                while (k < l) {
                    long long s = x + y + nums[k] + nums[l];
                    if (s == target) {
                        ans.push_back({ (int)x,(int)y,nums[k],nums[l] });
                        for (k++; k < l && nums[k] == nums[k - 1]; k++);
                        for (l--; l > k && nums[l] == nums[l + 1]; l--);
                    }
                    else if (s < target) {
                        k++;
                    }
                    else {
                        l--;
                    }
                }
            }
        }
        return ans;
    }
};