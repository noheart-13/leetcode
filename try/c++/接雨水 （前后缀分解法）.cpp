class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> pre_max(n);
        vector<int> suf_max(n);
        pre_max[0] = height[0];
        suf_max[n - 1] = height[n - 1];
        for (int i = 1; i < n; i++)
            pre_max[i] = max(pre_max[i - 1], height[i]);
        for (int i = n - 2; i >= 0; i--)
            suf_max[i] = max(suf_max[i + 1], height[i]);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += min(pre_max[i], suf_max[i]) - height[i];
        }
        return ans;
    }
};