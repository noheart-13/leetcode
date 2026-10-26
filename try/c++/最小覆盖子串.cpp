//我的解法
class Solution {
public:
    string minWindow(string s, string t) {
        int left = 0;
        int formed = 0;
        unordered_map<char, int> cnt;
        unordered_map<char, int> need;
        int bestStart = -1;
        int bestLength = static_cast<int>(s.size()) + 1;
        for (char character : t) {
            need[character]++;
        }
        int require = static_cast<int>(need.size());
        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            if (need.count(c) > 0) {
                cnt[c]++;
                if (cnt[c] == need[c]) {
                    formed++;
                }
            }
            while (formed == require) {
                int length = right - left + 1;
                if (length < bestLength) {
                    bestStart = left;
                    bestLength = length;
                }
                int out = s[left];
                if (need.count(out) > 0) {
                    cnt[out]--;
                    if (cnt[out] < need[out]) {
                        formed--;
                    }
                }
                left++;
            }
        }
        if (bestStart == -1)
            return "";
        return s.substr(bestStart, bestLength);
    }
};
//官方解法（未优化）
class Solution {
    bool is_covered(int cnt_s[], int cnt_t[]) {
        for (int i = 'A'; i <= 'Z'; i++) {
            if (cnt_s[i] < cnt_t[i]) {
                return false;
            }
        }
        for (int i = 'a'; i <= 'z'; i++) {
            if (cnt_s[i] < cnt_t[i]) {
                return false;
            }
        }
        return true;
    }

public:
    string minWindow(string s, string t) {
        int cnt_s[128]{}; // s 子串字母的出现次数
        int cnt_t[128]{}; // t 中字母的出现次数
        for (char c : t) {
            cnt_t[c]++;
        }

        int m = s.size();
        int ans_left = -1, ans_right = m;
        int left = 0;

        for (int right = 0; right < m; right++) { // 移动子串右端点
            cnt_s[s[right]]++; // 右端点字母移入子串
            while (is_covered(cnt_s, cnt_t)) { // 涵盖
                if (right - left < ans_right - ans_left) { // 找到更短的子串
                    ans_left = left; // 记录此时的左右端点
                    ans_right = right;
                }
                cnt_s[s[left]]--; // 左端点字母移出子串
                left++;
            }
        }

        return ans_left < 0 ? "" : s.substr(ans_left, ans_right - ans_left + 1);
    }
};
//官方解法（优化）
class Solution {
public:
    string minWindow(string s, string t) {
        int diff[128]{}; // 窗口每种字母个数 - t 每种字母个数
        int kinds = 0;
        for (char c : t) {
            if (diff[c] == 0) {
                kinds++; // 统计 t 有多少个不同的字母
            }
            diff[c]--;
        }

        int m = s.size();
        int ans_left = -1, ans_right = m;
        int ge_cnt = 0; // 窗口内有 ge_cnt 种字母的出现次数 >= t 中相应字母的出现次数
        int left = 0;

        for (int right = 0; right < m; right++) { // 移动子串右端点
            char c = s[right]; // 右端点字母
            diff[c]++; // 右端点字母移入子串
            if (diff[c] == 0) { // 原来窗口内 c 的出现次数比 t 的少，现在一样多
                ge_cnt++; // 从 < 变成 >=
            }

            while (ge_cnt == kinds) { // 涵盖：所有字母的出现次数都是 >=
                if (right - left < ans_right - ans_left) { // 找到更短的子串
                    ans_left = left; // 记录此时的左右端点
                    ans_right = right;
                }

                char x = s[left]; // 左端点字母
                if (diff[x] == 0) {
                    // x 移出窗口之前，检查出现次数，
                    // 如果窗口内 x 的出现次数和 t 一样，
                    // 那么 x 移出窗口后，窗口内 x 的出现次数比 t 的少
                    ge_cnt--; // 从 >= 变成 <
                }
                diff[x]--; // 左端点字母移出子串
                left++;
            }
        }

        return ans_left < 0 ? "" : s.substr(ans_left, ans_right - ans_left + 1);
    }
};