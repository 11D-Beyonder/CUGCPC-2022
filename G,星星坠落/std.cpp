/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-25 14:45:48
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-06-03 16:10:56
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const int N = 100005;
const bool debug = false;
struct hashVal
{
    ull hash1, hash2;
    bool operator<(const hashVal &A) const
    {
        if (hash1 == A.hash1)
            return hash2 < A.hash2;
        return hash1 < A.hash1;
    }
};
struct node
{
    int id, siz;
    ll val;
    ull hash1, hash2;
    bool operator<(const node &A) const
    {
        return val < A.val;
    }
    hashVal getHashVal()
    {
        return hashVal{hash1, hash2};
    }
} nodes[N];
struct path
{
    int u, v;
    ll val;
    bool operator<(const path &A) const
    {
        return v < A.v;
    }
} paths[N];
class tree
{
public:
    int n;
    int _cnt;
    int lson[N * 32], rson[N * 32];
    ll val[N * 32];
    int root[N];
    int curroot = 0;
    void push(int pos = -1, ll val = -1)
    {
        if (pos == -1)
        {
            empty(root[curroot + 1], root[curroot]);
        }
        else
        {
            update(root[curroot + 1], root[curroot], 1, n, pos, val);
        }
        curroot++;
    }
    void pushup(int now)
    {
        val[now] = val[lson[now]] + val[rson[now]];
    }
    void update(int &now, int la, int l, int r, int pos, ll v)
    {
        now = ++_cnt;
        lson[now] = lson[la];
        rson[now] = rson[la];
        val[now] = val[la];
        if (l == r)
        {
            val[now] += v;
            return;
        }
        int m = (l + r) >> 1;
        if (pos <= m)
            update(lson[now], lson[la], l, m, pos, v);
        else
            update(rson[now], rson[la], m + 1, r, pos, v);
        pushup(now);
    }
    void empty(int &now, int la)
    {
        now = ++_cnt;
        lson[now] = lson[la];
        rson[now] = rson[la];
        val[now] = val[la];
    }
    ll query(int now, int l, int r, int L, int R)
    {
        if (l >= L && r <= R)
        {
            return val[now];
        }
        ll ans = 0;
        int m = (l + r) >> 1;
        if (L <= m)
            ans += query(lson[now], l, m, L, R);
        if (R > m)
            ans += query(rson[now], m + 1, r, L, R);
        return ans;
    }
    ll query(int lr, int rr, int L, int R)
    {
        ll ans = query(root[rr], 1, n, L, R);
        if (lr == 1)
            return ans;
        return ans - query(root[lr - 1], 1, n, L, R);
    }
} tr;
class treeshow
{
public:
    struct pos
    {
        int x;
        ll val;
    };
    vector<vector<pos>> vec;
    int off = 0;
    int dfs(tree &tr, int now, int dep, int l, int r)
    {
        while (vec.size() < dep)
        {
            vec.push_back(vector<pos>());
        }
        if (l == r)
        {
            vec[dep - 1].push_back(pos{off, tr.val[now]});
            off += 2;
            return off - 2;
        }
        int m = (l + r) >> 1;
        pos ps{0, tr.val[now]};
        ps.x += dfs(tr, tr.lson[now], dep + 1, l, m);
        ps.x += dfs(tr, tr.rson[now], dep + 1, m + 1, r);
        ps.x /= 2;
        vec[dep - 1].push_back(ps);
        return ps.x;
    }
    void show(tree &tr, int root, int n)
    {
        vec.clear();
        off = 0;
        dfs(tr, tr.root[root], 1, 1, n);
        for (int i = 0; i < vec.size(); i++)
        {
            int pos = 0;
            for (auto &it : vec[i])
            {
                while (pos < it.x)
                {
                    putchar('\t');
                    pos++;
                }
                cout << it.val;
            }
            puts("");
        }
    }
} ts;
int fa[N], indegree[N], prime[N], in[N], out[N];
vector<int> vec[N];
map<hashVal, int> discret;
set<node> st[N];
int n, cnt = 0, seed, pathtot = 0, dfscnt = 0;
ll ans = 0;
bool vis[N];
void Euler_prime()
{
    for (int i = 2; i <= 100000; ++i)
    {
        if (!vis[i])
        {
            prime[cnt++] = i;
            vis[i] = true;
        }
        for (int j = 0; j < cnt; ++j)
        {
            if (i * prime[j] > 100000)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        if (prime[i] > n)
        {
            seed = prime[i];
            break;
        }
    }
}
void getsize(int cur)
{
    dfscnt++;
    in[cur] = dfscnt;
    nodes[cur].siz = 1;
    if (vec[cur].size() == 0)
    {
        out[cur] = dfscnt;
        return;
    }
    for (auto &it : vec[cur])
    {
        getsize(it);
        nodes[cur].siz += nodes[it].siz;
        nodes[cur].val += nodes[it].val;
    }
    out[cur] = dfscnt;
}
void input()
{
    cin >> n;
    tr.n = n;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &fa[i]);
        vec[fa[i]].push_back(i);
        indegree[fa[i]]++;
    }
    for (int i = 1; i <= n; i++)
    {
        nodes[i].id = i;
        scanf("%lld", &nodes[i].val);
    }
}
void hash1(int id)
{
    nodes[id].hash1 = 1;
    for (auto &it : vec[id])
    {
        nodes[id].hash1 += nodes[it].hash1 * prime[nodes[it].siz];
    }
}
void hash2(int id)
{
    for (auto &it : vec[id])
    {
        nodes[id].hash2 ^= nodes[it].hash2 * seed + nodes[it].siz;
    }
}
void hashTree()
{
    queue<int> qu;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            qu.push(i);
            nodes[i].hash1 = nodes[i].hash2 = 1;
        }
    }
    while (!qu.empty())
    {
        int cur = qu.front();
        qu.pop();
        // sort(vec[cur].begin(), vec[cur].end(), [](int a, int b)
        //      {
        //         node &aa = nodes[a], &bb = nodes[b];
        //         if(aa.hash1==bb.hash1)
        //         return aa.hash2<bb.hash2;
        //         return aa.hash1<bb.hash1; });
        hash1(cur);
        hash2(cur);
        indegree[fa[cur]]--;
        if (indegree[fa[cur]] == 0)
            qu.push(fa[cur]);
    }
}
void createPath()
{
    for (int i = 1; i <= n; i++)
    {
        int pos = discret[nodes[i].getHashVal()];
        ll val = nodes[i].val;
        if (st[pos].size() != 0)
        {
            auto it = st[pos].lower_bound(nodes[i]);
            if (it == st[pos].end())
            {
                it--;
            }
            auto tmp = it;
            if (it->val < val)
            {
                tmp++;
                if (tmp != st[pos].end() && abs(tmp->val - val) <= abs(it->val - val) && tmp->id < it->id)
                    it = tmp;
            }
            else if (it->val > val)
            {
                if (tmp != st[pos].begin())
                {
                    tmp--;
                    if (abs(tmp->val - val) <= abs(it->val - val) && tmp->id < it->id)
                    {
                        it = tmp;
                    }
                }
            }
            paths[pathtot++] = path{in[it->id], in[i], it->val + val};
        }
        auto item = st[pos].find(nodes[i]);
        if (item == st[pos].end())
            st[pos].insert(nodes[i]);
    }
}
void discretization()
{
    int tot = 1;
    for (int i = 1; i <= n; i++)
    {
        auto val = nodes[i].getHashVal();
        if (discret[val] == 0)
            discret[val] = tot++;
    }
}
ll qp(ll x, ll y)
{
    ll res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}
void getans()
{
    sort(paths, paths + pathtot);
    int pos = 0;
    for (int i = 1; i <= n; i++)
    {
        if (paths[pos].v == i)
        {
            tr.push(paths[pos].u, paths[pos].val);
            pos++;
        }
        else
        {
            tr.push();
        }
    }
    for (int i = 0; i < pathtot; i++)
    {
        int u = paths[i].u, v = paths[i].v;
        if (debug)
        {
            cout << u << " " << v << " " << paths[i].val << endl;
            cout << "query(" << in[v] << "," << out[v] << "," << in[u] << "," << out[u] << ")=" << tr.query(in[v], out[v], in[u], out[u]) << endl;
        }
        ans += tr.query(in[v], out[v], in[u], out[u]);
        ans %= mod;
    }
    if (debug)
        cout << ans << endl;
    ans = ans * qp(pathtot, mod - 2) % mod;
    cout << ans << endl;
}
void func()
{
    Euler_prime();
    getsize(1);
    hashTree();
    discretization();
    createPath();
    getans();
}
int main(int argc, char *agrv[])
{
    if (argc == 3)
    {
        freopen(agrv[1], "r", stdin);
        freopen(agrv[2], "w", stdout);
    }
    input();
    func();

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << in[i] << " " << out[i] << endl;
    // }
    if (debug)
    {
        puts("---------------------------------------------------------------------------");
        for (int i = 1; i <= n; i++)
        {
            ts.show(tr, i, n);
            puts("---------------------------------------------------------------------------");
        }
    }
    return 0;
}
/*
11
1 2 3 3 2 6 6 1 9 9
3 4 9 1 5 3 7 6 5 2 2

*/