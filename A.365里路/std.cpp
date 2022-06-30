/*
 * @author: 11D_Beyonder
 */
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_N = 100001;
const int MAX_M = 300001;
const int MAX_D = 21;
struct Edge
{
    int from;
    int to;
    int next;
};
int n, m, d, g, t;
int timer;
int f[MAX_N * MAX_D];
int stack[MAX_N * MAX_D], top;
bool in_stack[MAX_N * MAX_D];
int dfn[MAX_N * MAX_D], low[MAX_N * MAX_D];
int head[MAX_N * MAX_D], tot;
int val[MAX_N * MAX_D];
int representative[MAX_N * MAX_D];
int new_head[MAX_N * MAX_D], new_tot;
Edge edge[MAX_M * MAX_D], new_edge[MAX_M * MAX_D];
bool vis[MAX_N * MAX_D];
int max_val[MAX_N];
inline int cal_id(int point_id, int day)
{
    return (point_id - 1) * d + day;
}
inline int get_point(int id)
{
    return (id + d - 1) / d;
}
inline void add_edge(int u, int v)
{
    ++tot;
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}
inline void add_new_edge(int u, int v)
{
    ++new_tot;
    new_edge[new_tot].from = u;
    new_edge[new_tot].to = v;
    new_edge[new_tot].next = new_head[u];
    new_head[u] = new_tot;
}
void tarjan(int x)
{
    dfn[x] = low[x] = ++timer;
    stack[++top] = x;
    in_stack[x] = true;
    for (int i = head[x]; ~i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (in_stack[y])
        {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (dfn[x] == low[x])
    {
        int start = top;
        int y;
        do
        {
            y = stack[top--];
            representative[y] = x;
            in_stack[y] = false;
            max_val[get_point(y)] = max(max_val[get_point(y)], val[y]);
        } while (x != y);
        val[x] = 0;
        for (int i = top + 1; i <= start; i++)
        {
            if (~max_val[get_point(stack[i])])
            {
                val[x] += max_val[get_point(stack[i])];
                max_val[get_point(stack[i])] = -1;
            }
        }
    }
}
inline void init()
{
    tot = 0;
    new_tot = 0;
    timer = 0;
    top = 0;
    memset(head, -1, sizeof(head));
    memset(new_head, -1, sizeof(new_head));
    memset(f, 0, sizeof(f));
    memset(dfn, 0, sizeof(dfn));
    memset(in_stack, false, sizeof(in_stack));
    memset(representative, 0, sizeof(representative));
    memset(max_val, -1, sizeof(max_val));
    memset(val, 0, sizeof(val));
    memset(vis, false, sizeof(vis));
}
int dfs(int x)
{
    if (vis[x])
    {
        return f[x];
    }
    vis[x] = true;
    for (int i = new_head[x]; ~i; i = new_edge[i].next)
    {
        f[x] = max(f[x], dfs(new_edge[i].to));
    }
    f[x] += val[x];
    return f[x];
}
int main()
{
    init();
    cin >> n >> m >> d >> g >> t;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        for (int day = 1; day <= d; day++)
        {
            add_edge(cal_id(x, day), cal_id(y, day % d + 1));
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int day = 1; day <= d; day++)
        {
            scanf("%d", &val[cal_id(i, day)]);
        }
    }
    for (int i = 1; i <= n * d; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }
    for (int i = 1; i <= m * d; i++)
    {
        int x = representative[edge[i].from];
        int y = representative[edge[i].to];
        if (x != y)
        {
            add_new_edge(x, y);
        }
    }
    cout << dfs(representative[cal_id(g, t)]) << endl;
    return 0;
}