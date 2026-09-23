class Solution {
public:
    bool isPalindrome(string s) {
        int n = 0, m = s.size() - 1;
        while (n < m) {
            if (!isalnum(s[n]))
                n++;
            else if (!isalnum(s[m]))
                m--;
            else if (tolower(s[n]) == tolower(s[m])) {
                n++;
                m--;
            }
            else {
                return false;
            }
        }
        return true;
    }
};