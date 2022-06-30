/*
 * @Description:
 * @Version: 1.0
 * @Autor: i_mailang
 * @Date: 2022-05-22 16:56:51
 * @LastEditors: i_mailang
 * @LastEditTime: 2022-05-25 23:19:21
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll qp(ll x, ll y)
{
    ll res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
struct node
{
public:
    int x, y, z;
    void opt(char ch, int n)
    {
        if (ch == 'U')
            y += n;
        else if (ch == 'D')
            y -= n;
        else if (ch == 'L')
            x -= n;
        else if (ch == 'R')
            x += n;
        else if (ch == 'A')
            z -= n;
        else
            z += n;
    }
    bool operator==(const node &A) const
    {
        return A.x == x && A.y == y && A.z == z;
    }
};

char _opts[6] = {'U', 'D', 'L', 'R', 'A', 'B'};

const int dx[8] = {0, 1, 0, 1, 0, 1, 0, 1};
const int dy[8] = {0, 0, 1, 1, 0, 0, 1, 1};
const int dz[8] = {0, 0, 0, 0, 1, 1, 1, 1};
class block
{
public:
    node nd1, nd2;
    bool vis[8];
    block *son[8];
    node entry, ext;
    char toword, lasttoword;
    void setedge(int _x1, int _x2, int _y1, int _y2, int _z1, int _z2)
    {
        nd1.x = _x1;
        nd2.x = _x2;
        nd1.y = _y1;
        nd2.y = _y2;
        nd1.z = _z1;
        nd2.z = _z2;
    }
    void setedge(block *nd)
    {
        int x1 = nd1.x, x2 = nd2.x, y1 = nd1.y, y2 = nd2.y, z1 = nd1.z, z2 = nd2.z;
        int xm = (x1 + x2) >> 1, ym = (y1 + y2) >> 1, zm = (z1 + z2) >> 1;
        if (nd->entry.x <= xm)
        {
            nd->nd1.x = x1;
            nd->nd2.x = xm;
        }
        else
        {
            nd->nd1.x = xm + 1;
            nd->nd2.x = x2;
        }
        if (nd->entry.y <= ym)
        {
            nd->nd1.y = y1;
            nd->nd2.y = ym;
        }
        else
        {
            nd->nd1.y = ym + 1;
            nd->nd2.y = y2;
        }
        if (nd->entry.z <= zm)
        {
            nd->nd1.z = z1;
            nd->nd2.z = zm;
        }
        else
        {
            nd->nd1.z = zm + 1;
            nd->nd2.z = z2;
        }
        // switch (id)
        // {
        // case 0:
        //     nd->setedge(x1, xm, y1, ym, z1, zm);
        //     break;
        // case 1:
        //     nd->setedge(xm + 1, x2, y1, ym, z1, zm);
        //     break;
        // case 2:
        //     nd->setedge(x1, xm, ym + 1, y2, z1, zm);
        //     break;
        // case 3:
        //     nd->setedge(xm + 1, x2, ym + 1, y2, z1, zm);
        //     break;
        // case 4:
        //     nd->setedge(x1, xm, y1, ym, zm + 1, z2);
        //     break;
        // case 5:
        //     nd->setedge(xm + 1, x2, y1, ym, zm + 1, z2);
        //     break;
        // case 6:
        //     nd->setedge(x1, xm, ym + 1, y2, zm + 1, z2);
        //     break;
        // case 7:
        //     nd->setedge(xm + 1, x2, ym + 1, y2, zm + 1, z2);
        //     break;

        // default:
        //     break;
        // }
    }
    void setentry(node nd)
    {
        entry = nd;
    }
    char st[10];
    char top = 0;
    bool ans = false;
    int n;
    int getid(node nd)
    {
        for (int i = 0; i < 8; i++)
        {
            node tmp = nd1;
            tmp.x += dx[i] * n;
            tmp.y += dy[i] * n;
            tmp.z += dz[i] * n;
            if (tmp == nd)
                return i;
        }
        return -1;
    }
    bool checkin(node nd)
    {
        return nd.x >= nd1.x && nd.x <= nd2.x && nd.y >= nd1.y && nd.y <= nd2.y && nd.z >= nd1.z && nd.z <= nd2.z;
    }
    void dfs(node nd)
    {
        // cout << nd.x << " " << nd.y << " " << nd.z << endl;
        if (top == 1 && st[0] == lasttoword)
        {
            return;
        }
        if (ans)
            return;
        if (top == 7)
        {
            if (st[6] == toword)
                return;
            if (nd == ext)
            {
                // for (int i = 0; i < 7; i++)
                //     putchar(st[i]);
                // puts("");
                ans = true;
                st[7] = st[6];
            }
            return;
        }
        if (nd == ext)
            return;
        for (int i = 0; i < 6; i++)
        {
            node tmp = nd;
            tmp.opt(_opts[i], n);
            if (checkin(tmp))
            {
                int id = getid(tmp);
                if (!vis[id])
                {
                    st[top++] = _opts[i];
                    vis[id] = true;
                    dfs(tmp);
                    if (ans)
                        return;
                    top--;
                    vis[id] = false;
                }
            }
        }
    }
    void calexit()
    {
        n = nd2.x - nd1.x;
        ext = entry;
        ext.opt(toword, n);
        if (checkin(ext))
            return;
        ext = entry;
        if (toword == 'L' || toword == 'R')
            ext.y ^= nd1.y ^ nd2.y;
        else if (toword == 'U' || toword == 'D')
            ext.z ^= nd1.z ^ nd2.z;
        else if (toword == 'A' || toword == 'B')
            ext.x ^= nd1.x ^ nd2.x;
    }
    void getopts()
    {
        for (int i = 0; i < 8; i++)
            vis[i] = false;
        vis[getid(entry)] = true;
        dfs(entry);
    }
    void split()
    {
        // cout << nd1.x << " " << nd1.y << " " << nd1.z << " ; " << nd2.x << " " << nd2.y << " " << nd2.z << endl;
        // cout << entry.x << " " << entry.y << " " << entry.z << " ; " << ext.x << " " << ext.y << " " << ext.z << endl;
        getopts();
        if (n == 1)
            return;
        node cur = entry;
        char t = lasttoword;
        for (int i = 0; i < 8; i++)
        {
            son[i] = new block();
            son[i]->setentry(cur);
            setedge(son[i]);
            son[i]->lasttoword = t;
            if (i < 7)
                son[i]->toword = st[i];
            else
                son[i]->toword = toword;
            t = st[i];
            son[i]->calexit();
            if (i == 7)
                son[i]->ext = ext;
            cur = son[i]->ext;
            cur.opt(st[i], 1);
            son[i]->split();
        }
    }
    void show()
    {
        if (n == 1)
        {
            for (int i = 0; i < 7; i++)
            {
                putchar(st[i]);
            }
            return;
        }
        for (int i = 0; i < 8; i++)
        {
            son[i]->show();
            if (i < 7)
                putchar(st[i]);
        }
    }
};

int main()
{
    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    int n;
    int m;
    cin >> m;

    cout << ((2 * ((((qp(2, m) * qp(2, m)) % mod) * qp(2, m)) % mod + mod - 1) % mod) % mod - 1 + mod) % mod << endl;
    if (m <= 5)
    {
        n = 1 << m;
        block b;
        b.nd1 = node{1, 1, 1};
        b.nd2 = node{n, n, n};
        b.setentry(node{1, 1, 1});
        b.toword = 'R';
        b.calexit();
        b.split();
        b.show();
        puts("");
    }
    // }
    return 0;
}
/*
RUBDLUAUBUARBDARURDBULDBRUBDLUALBDLUADRDLDBURDARUBDRUADAULDAURD
*/