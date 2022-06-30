/*
 * @author: 11D_Beyonder
 */
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll quickPow(ll a, ll b)
{
    ll res = 1;
    a %= MOD;
    while (b)
    {
        if (b & 1)
        {
            res = res * a % MOD;
        }
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}
int main()
{
    ll m, n;
    scanf("%lld %lld", &n, &m);
    n %= MOD;
    m %= MOD;
    printf("%lld\n", n * m % MOD * (m + 1) % MOD * (n + 1) % MOD * quickPow(4, MOD - 2) % MOD);
    return 0;
}