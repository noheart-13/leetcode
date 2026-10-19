//AI+我的解法
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
//官方解法
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int mx = ranges::max(nums);
        long long ans = 0;
        int cnt_mx = 0, left = 0;
        for (int x : nums) {
            cnt_mx += x == mx;
            while (cnt_mx == k) {
                cnt_mx -= nums[left] == mx;
                left++;
            }
            ans += left;
        }
        return ans;
    }
};