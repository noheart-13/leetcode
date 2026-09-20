class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans = 0, left = 0;
        int right = height.size() - 1;
        while (left < right) {
            int area = (right - left) * min(height[right], height[left]);
            ans = max(ans, area);
            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }
        return ans;
    }
};