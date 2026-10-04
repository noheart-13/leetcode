class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int ans = 0;
        int sum = 1;
        int n = nums.size();
        int left = 0;
        if (k <= 1)
            return 0;
        for (int right = 0; right < n; right++) {
            sum *= nums[right];
            while (sum >= k) {
                sum /= nums[left];
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }
};