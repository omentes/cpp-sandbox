/*
 *
    Implement strStr().

    Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

    Clarification:
    What should we return when needle is an empty string? This is a great question to ask during an interview.
    For the purpose of this problem, we will return 0 when needle is an empty string.
    This is consistent to C's strstr() and Java's indexOf().

    Example 1:
    Input: haystack = "hello", needle = "ll"
    Output: 2

    Example 2:
    Input: haystack = "aaaaa", needle = "bba"
    Output: -1

    Example 3:
    Input: haystack = "", needle = ""
    Output: 0

    Constraints:
    0 <= haystack.length, needle.length <= 5 * 104
    haystack and needle consist of only lower-case English characters.
    https://leetcode.com/problems/implement-strstr
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class Solution {
 public:
  int strStr(string haystack, string needle) {
    if ((haystack.empty() && needle.empty()) || needle.empty()) {
      return 0;
    }
    if (haystack == needle) {
      return 0;
    }
    if (haystack.size() < needle.size()) {
      return -1;
    }
    int res = -1;
    for (int i = 0; i < haystack.size(); ++i) {
      if (haystack[i] == needle[0]) {
        int j = 0;
        int nsize = needle.size();
        while(j < nsize) {
          if (haystack[i + j] == needle[j]) {
            j++;
            continue;
          }
          break;
        }
        if (j == nsize) {
          return i;
        }
      }
    }
    return res;
  }
};