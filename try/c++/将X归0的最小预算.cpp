//逆向思维
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int left = 0, total = 0, sum = 0, ans = -1;
        for (int num : nums) {
            total += num;
        }
        int target = total - x;
        if (target == 0)
            return nums.size();
        if (target < 0)
            return -1;
        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];
            while (sum > target) {
                sum -= nums[left];
                left++;
            }
            if (sum == target)
                ans = max(ans, right - left + 1);
        }
        return ans == -1 ? -1 : nums.size() - ans;
    }
};
//正向双指针
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0, n = nums.size(), right = n;
        while (right > 0 && sum + nums[right - 1] <= x) { // 计算最长后缀
            right--;
            sum += nums[right];
        }
        if (right == 0 && sum < x) {
            return -1; // 全部移除也无法满足要求
        }

        int ans = sum == x ? n - right : n + 1;
        for (int left = 0; left < n; left++) {
            sum += nums[left];
            while (right < n && sum > x) {
                sum -= nums[right];
                right++; // 缩小后缀长度
            }
            if (sum > x) {
                break; // 缩小失败，说明前缀过长
            }
            if (sum == x) {
                ans = min(ans, left + 1 + n - right); // 前缀+后缀长度
            }
        }
        return ans > n ? -1 : ans;
    }
};
