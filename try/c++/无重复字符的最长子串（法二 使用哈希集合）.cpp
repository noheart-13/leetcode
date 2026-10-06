class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0;
        int ans = 0;
        unordered_set<char> windows;
        for (int right = 0; right < n; right++) {
            char c = s[right];
            while (windows.contains(c)) {
                windows.erase(s[left]);
                left++;
            }
            windows.insert(c);
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};