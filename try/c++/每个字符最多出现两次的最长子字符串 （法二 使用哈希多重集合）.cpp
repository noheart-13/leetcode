class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        unordered_multiset<char> windows;
        int ans = 0;
        int left = 0;
        for (int right = 0; right < n; right++) {
            windows.insert(s[right]);
            while (windows.count(s[right]) > 2) {
                auto it = windows.find(s[left]);
                windows.erase(it);
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};