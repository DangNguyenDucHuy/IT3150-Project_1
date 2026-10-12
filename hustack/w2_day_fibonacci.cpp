#include<bits/stdc++.h>
using namespace std;

int n;

int fib(int k) {
    if (k < 2) return k;
    return fib(k-1) + fib(k-2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cout << fib(n-1);

    return 0;
}
