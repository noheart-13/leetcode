//二分法
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        ranges::sort(nums);
        long long ans = 0;
        for (int j = 0; j < nums.size(); j++) {
            auto r = upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            auto l = lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
            ans += r - l;
        }
        return ans;
    }
};
//双指针lambda表达式
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        ranges::sort(nums);
        auto count = [&](int upper) {
            long long ans = 0;
            int i = 0, j = nums.size() - 1;
            while (i < j) {
                if (nums[i] + nums[j] <= upper) {
                    ans += j - i;
                    i++;
                }
                else {
                    j--;
                }
            }
            return ans;
            };
        return count(upper) - count(lower - 1);
    }
};