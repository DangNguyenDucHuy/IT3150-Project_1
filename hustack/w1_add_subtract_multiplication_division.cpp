#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    
    if (a < 1 || b < 1 || a > 1000 || b > 1000) return 1;
    
    cout << a+b << " " << a-b << " " << a*b << " " << a/b;
    return 0;
}
