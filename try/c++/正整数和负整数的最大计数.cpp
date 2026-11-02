class Solution {
    int lower_bound(const vector<int>& nums, int target) {
        int left = -1, right = nums.size();
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        return right;
    }
public:
    int maximumCount(vector<int>& nums) {
        int fu = lower_bound(nums, 0);
        int n = lower_bound(nums, 1);
        int zhen = nums.size() - n;
        if (fu >= zhen)
            return fu;
        else
            return zhen;
    }
};