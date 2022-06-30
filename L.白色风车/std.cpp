/*
 * @author: 11D_Beyonder
 */
#include <iostream>
#include <cstring>
using namespace std;
char s[1000004];
int main()
{
    cin >> (s + 1);
    int n = strlen(s + 1);
    int ans = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        if (s[i] == 'A' && s[i + 1] == '4')
        {
            ++ans;
        }
    }
    for (int i = 1; i <= n - 2; i++)
    {
        if (s[i] == '4' && s[i + 1] == '4' && s[i + 2] == '0')
        {
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}