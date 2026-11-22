//二分答案
class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
        auto check = [&](long long limit) ->bool {
            long long extra = 0;
            for (int i = nums.size() - 1; i > 0; i--) {
                long long new_nums = nums[i] + extra;
                extra = max(new_nums - limit, 0LL);
            }
            return nums[0] + extra <= limit;
            };
        int left = nums[0] - 1, right = ranges::max(nums);
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};
//前缀和+贪心
class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
        long long ans = 0, s = 0;
        for (int i = 0; i < nums.size(); i++) {
            s += nums[i];
            ans = max(ans, (s + i) / (i + 1));
        }
        return ans;
    }
};