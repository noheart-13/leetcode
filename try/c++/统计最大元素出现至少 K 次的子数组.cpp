class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int maxNum = *max_element(nums.begin(), nums.end());
        long long ans = 0;
        int left = 0;
        int countMax = 0;
        for (int right = 0; right < nums.size(); right++)
        {
            if (nums[right] == maxNum) {
                countMax++;
            }
            while (countMax >= k) {
                if (nums[left] == maxNum) {
                    countMax--;
                }
                left++;
            }
            ans += left;
        }
        return ans;
    }
};