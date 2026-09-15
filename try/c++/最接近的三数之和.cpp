class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        ranges::sort(nums);
        int n = nums.size();
        int ans = INT_MAX / 2;
        for (int i = 0; i < n - 2; i++) {
            int x = nums[i];
            if (i > 0 && x == nums[i - 1]) {
                continue;
            }
            int s = x + nums[i + 1] + nums[i + 2];
            if (s >= target) {
                if (s - target < abs(ans - target)) {
                    ans = s;
                }
                break;
            }
            s = nums[i] + nums[n - 2] + nums[n - 1];
            if (s <= target) {
                if (target - s < abs(ans - target)) {
                    ans = s;
                }
                continue;
            }
            int j = i + 1, k = n - 1;
            while (j < k) {
                s = x + nums[j] + nums[k];
                if (s == target)
                    return target;
                if (abs(s - target) < abs(ans - target)) {
                    ans = s;
                }
                if (s < target) {
                    j++;
                }
                else {
                    k--;
                }
            }
        }
        return ans;
    }
};