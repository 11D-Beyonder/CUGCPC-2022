/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-22 01:26:46
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-05-22 14:04:56
 */
#include <bits/stdc++.h>
using namespace std;
int dp[1005][105];
struct node
{
    int w, atk, as;
};
node a[1005];
int n, m, H;
bool check(int t)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= 100; j++)
            dp[i][j] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        if (a[i].as > t)
            continue;
        for (int j = n - 1; j >= 0; j--)
        {
            for (int k = 99; k >= 0; k--)
            {
                int tmp = k + a[i].w;
                if (tmp <= 100)
                    dp[j + 1][tmp] = max(dp[j + 1][tmp], dp[j][k] + a[i].atk);
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 100; j >= 0; j--)
        {
            if (j <= 30)
            {
                dp[i][j] = max(dp[i][j], int(dp[i][j - 2] * (100.0 + 30 - j) / 100.0));
            }

            if (dp[i][j] >= H)
                return true;
        }
    }
    return false;
}
int main()
{
    cin >> n >> m >> H;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &a[i].w, &a[i].atk, &a[i].as);
    }
    int l = 1, r = 1000000;
    while (r > l)
    {
        int m = (l + r) >> 1;
        if (check(m))
        {
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }
    if (check(r))
    {
        cout << r << endl;
    }
    else
        puts("YOU DIED");
    return 0;
}