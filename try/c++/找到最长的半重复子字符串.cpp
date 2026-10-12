class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size();
        int left = 0;
        int ans = 1;
        int rep = 0;
        for (int right = 0; right < n; right++) {
            if (right > 0 && s[right - 1] == s[right]) {
                rep++;
            }
            while (rep > 1) {
                if (s[left + 1] == s[left]) {
                    rep--;
                }
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};