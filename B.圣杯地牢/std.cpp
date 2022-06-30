/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-29 22:25:35
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-05-29 23:36:06
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300000 + 10;
long long n, m, ans;
long long a[maxn], b[maxn], c[maxn], d[maxn];
string slove()
{
    long long cnt = ans / ((n + 1) * n / 2);
    for (int i = 1; i <= n; ++i)
    {
        if ((cnt - d[i]) % n != 0)
            return "NO";
        m += (cnt - d[i]) / n;
    }
    if (m == cnt)
        return "YES";
    else
        return "NO";
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
        c[i] = b[i] - a[i], ans += c[i];
    for (int i = 1; i <= n; ++i)
        d[i] = c[i] - c[(i - 2 + n) % n + 1];
    if (ans % ((n + 1) * n / 2) == 0)
        cout << slove() << '\n';
    else
        printf("NO\n");
    return 0;
}
/*
1   2   3   4   5
6   3   5   7   9
8   6   9   12  10
9 8 12 16 15


*/