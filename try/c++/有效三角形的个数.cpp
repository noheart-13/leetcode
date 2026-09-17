class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        int m = 0;
        for (int i = n - 1; i > 1; i--) {
            int j = i - 1, k = 0;
            while (k < j) {
                if (nums[k] + nums[j] > nums[i]) {
                    m += j - k;
                    j--;
                }
                else {
                    k++;
                }
            }
        }
        return m;
    }
};