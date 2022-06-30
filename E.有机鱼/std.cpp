/*
 * @author: 11D_Beyonder
 */
#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.1415926535897932384626433832795;
int main()
{
    double n, r;
    cin >> r >> n;
    printf("%.2lf\n", n / 2 * r * r * sin(2 * PI / n));
    return 0;
}