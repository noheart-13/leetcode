2 sum -leetcode 167： 相向双指针 从一个数和最后一个数计算加和，若数值大于target，则最后数值过大，指针前移，若小于target，则最前数值过小，指针后移，直至目标大于target（时间复杂度：O（n）；空间复杂度：O（1））

3 sum -leetcode 15 ： 双指针＋剪枝 先进行排序方便进行双指针和两数相同时去重，固定第一个数然后变成两数之和解决，去重则是遇到前一个数字和自己一样时，跳过当前数字。两个优化：1.固定的一个数和最后两个数相加大于0，则不存在三数之和等于0，break（剪枝算法）；2.固定的数和最后面两个最大的数相加时小于0，则内层枚举不存在三数和等于0，但是nums[i]可变大，所以后面任有机会三数和等于0，continue。

统计和小于目标的下标对数目 -leetcode 2824 ：双指针 大致思路如2 sum leetcode 167 先排序形成一个单调数组，相加条件如果符合题意，则让数目+=右指针下标-左指针下标，如何左++，反之则右--。直至完成循环然后return数目

最接近的三数之和 -leetcode16 ： 双指针 可参考3sum，排序，枚举第一个数，找另外两个数使这三个数的和最接近target s=nums[i]+nums[j]+nums[k]。如果 ∣s−target∣<∣ans−target∣，那么更新 ans=s。ans 初始值为 ∞.然后分类讨论：
如果 s=target，那么答案就是 target，直接返回 target。
如果 s>target，那么和三数之和一样，把 k 减一。
否则 s<target，那么和三数之和一样，把 j 加一。

4 sum -leetcode 18 ：类3 sum。排序后，枚举 nums[a] 作为第一个数，枚举 nums[b] 作为第二个数，那么问题变成找到另外两个数，使得这四个数的和等于 target，这可以用双指针解决

有效三角形的个数 -leetcode 611 ：先对数组从小到大排序。外层循环枚举最长边 c=nums[k]，内层循环用相向双指针枚举 a=nums[i] 和 b=nums[j]

盛最多水的容器 -leetcode 11 ：双指针，分别从两头开始，记录最大的盛水容量。若左边数组值小，向右移动；右边反之。同时利用max函数，取一开始容量和后续数组移动后容量两者的最大值，然后return

接雨水 -leetcode 42 法一（前后缀分解）：定义两个数组，一个从前往后确立的最大高度，一个从后往前遍历最大高度。将两数组同一位置取最小值-该位置上的初始数组值，即为水含量。
                    法二（相向双指针）：基于法一的优化，仅进行一次遍历。
如果 preMax[left]≤sufMax[right]，由于 sufMax[right]≤sufMax[left]（包含的数越多，最大值越大），所以 preMax[left]≤sufMax[right]≤sufMax[left]，所以 min(preMax[left],sufMax[left])=preMax[left]，left 处的接水量就是 preMax[left]−height[left]。
如果 preMax[left]≥sufMax[right]，由于 preMax[left]≤preMax[right]（包含的数越多，最大值越大），所以 sufMax[right]≤preMax[left]≤preMax[right]，所以 min(preMax[right],sufMax[right])=sufMax[right]，right 处的接水量就是 sufMax[right]−height[right]。
