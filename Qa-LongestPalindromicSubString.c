#include <stdio.h>
#include <string.h>

int expandAroundCenter(char *str, int left, int right)
{
    while (left >= 0 && right < strlen(str) && str[left] == str[right])
    {
        left--;
        right++;
    }
    return right - left - 1;
}

void longestPalindrome(char *str, char *result)
{
    int n = strlen(str);
    int start = 0;
    int maxLength = 1;

    for (int i = 0; i < n; i++)
    {
        int len1 = expandAroundCenter(str, i, i);
        int len2 = expandAroundCenter(str, i, i + 1);

        int len = (len1 > len2) ? len1 : len2;

        if (len > maxLength)
        {
            maxLength = len;
            start = i - (len - 1) / 2;
        }
    }

    for (int i = 0; i < maxLength; i++)
    {
        result[i] = str[start + i];
    }
    result[maxLength] = '\0';
}

int main()
{
    char string[1000];
    char result[1000];

    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    longestPalindrome(string, result);

    printf("Longest palindromic substring: %s\n", result);

    return 0;
}
