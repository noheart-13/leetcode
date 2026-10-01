class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int ans = n + 1;
        int s = 0;
        int left = 0;
        for (int right = 0; right < n; right++) {
            s += nums[right];
            while (s >= target) {
                ans = min(ans, right - left + 1);
                s -= nums[left];
                left++;
            }
        }
        if (ans <= n)
            return ans;
        else {
            return 0;
        }
    }
};