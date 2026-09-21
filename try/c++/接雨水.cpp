class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        int per_max = 0;
        int suf_max = 0;
        int left = 0, right = n - 1;
        while (left <= right) {
            per_max = max(per_max, height[left]);
            suf_max = max(suf_max, height[right]);
            if (per_max < suf_max) {
                ans += per_max - height[left];
                left++;
            }
            else {
                ans += suf_max - height[right];
                right--;
            }
        }
        return ans;
    }
};