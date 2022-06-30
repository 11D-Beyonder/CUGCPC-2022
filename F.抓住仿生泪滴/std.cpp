/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-24 00:58:26
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-05-24 01:03:49
 */
#include <bits/stdc++.h>
using namespace std;
typedef double db;
db ans[1000005];
int a[1000005];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    ans[0] = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] == 0)
        {
            ans[i] = ans[i - 1] + 1 + (i - ans[i - 1]) / i;
        }
        else
        {
            ans[i] = ans[i - 1];
        }
    }

    printf("%.6lf ", ans[n - 1]);

    puts("");
    return 0;
}
/*

*/