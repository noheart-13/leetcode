class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr2);
        int ans = 0;
        for (int x : arr1) {
            auto num = ranges::lower_bound(arr2, x - d);
            if (num == arr2.end() || *num > x + d) {
                ans++;
            }
        }
        return ans;
    }
};