/*
 * @author: 11D_Beyonder
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int MAX_N = 3004;
ll a[MAX_N], b[MAX_N];
int n;
int t[MAX_N];
vector<pair<int, int>> opts;
unordered_map<ll, vector<int>> poses;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        // poses[x]为a中x出现的所有位置
        poses[a[i]].emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    // 找每个x的目标位
    for (const auto &p : poses)
    {
        for (int i = 1; i <= n; i++)
        {
            if (b[i] == p.first)
            {
                for (int j = i; j <= n && b[i] == b[j]; j++)
                {
                    // 得到目标位
                    t[p.second[j - i]] = j;
                }
                break;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += abs(t[i] - i);
    }
    ans >>= 1;
    cout << ans << endl;
    while (true)
    {
        int r = -1;
        for (int i = n; i >= 1; i--)
        {
            // 找到最右需要向右的位置
            if (t[i] > i)
            {
                r = i;
                break;
            }
        }
        if (r == -1)
        {
            break;
        }
        for (int i = r; i <= t[r]; i++)
        {
            // 找到目标位在[1,r]的位置
            if (t[i] <= r)
            {
                opts.emplace_back(make_pair(r, i));
                // 交换两个位置
                swap(a[r], a[i]);
                swap(t[r], t[i]);
                // 最右需要向右移的指针位置跟着移动
                r = i;
            }
        }
    }
    cout << opts.size() << endl;
    for (const auto &p : opts)
    {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}