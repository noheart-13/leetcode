class Solution {
public:
    int minLength(vector<int>& nums, int k) {
        int ans = nums.size() + 1;
        int left = 0;
        int sum = 0;
        unordered_map<int, int> cnt;
        for (int right = 0; right < nums.size(); right++) {
            int c = nums[right];
            cnt[c]++;
            if (cnt[c] == 1)
                sum += c;
            while (sum >= k) {
                ans = min(ans, right - left + 1);
                int out = nums[left];
                cnt[out]--;
                if (cnt[out] == 0) {
                    sum -= out;
                }
                left++;
            }
        }
        return ans == nums.size() + 1 ? -1 : ans;
    }
};