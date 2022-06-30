/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-28 22:09:46
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-05-29 19:11:39
 */
#include <bits/stdc++.h>
#define lson n << 1
#define rson n << 1 | 1
#define mid (l + r) >> 1
using namespace std;
const int N = 100005 << 2;
class tree
{
public:
    int val[N], lval[N], rval[N], num[N];
    void pushup(int n, int l, int r)
    {
        val[n] = max(val[lson], val[rson]);
        val[n] = max(val[n], lval[rson] + rval[lson]);
        lval[n] = lval[lson], rval[n] = rval[rson];
        int m = mid;
        if (lval[n] == m - l + 1)
            lval[n] += lval[rson];
        if (rval[n] == r - m)
            rval[n] += rval[lson];
    }
    int query()
    {
        return val[1];
    }
    void update(int n, int l, int r, int pos, int v)
    {
        if (l == r)
        {
            num[n] += v;
            num[n] = max(num[n], 0);
            lval[n] = rval[n] = val[n] = num[n] != 0;
            return;
        }
        int m = mid;
        if (pos <= m)
            update(lson, l, m, pos, v);
        else
            update(rson, m + 1, r, pos, v);
        pushup(n, l, r);
    }
} tr[2];
int main(int argc, char *agrv[])
{
    if (argc == 3)
    {
        freopen(agrv[1], "r", stdin);
        freopen(agrv[2], "w", stdout);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            int x;
            scanf("%d", &x);
            tr[x & 1].update(1, 1, 100000, x / 2 + 1, 1);
        }
        else if (opt == 2)
        {
            int x;
            scanf("%d", &x);
            tr[x & 1].update(1, 1, 100000, x / 2 + 1, -1);
        }
        else
        {
            printf("%d\n", max(tr[0].query(), tr[1].query()));
        }
    }
    return 0;
}