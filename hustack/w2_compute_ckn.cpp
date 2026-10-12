#include<bits/stdc++.h>
using namespace std;

const int MN = 1e4+1;
const long MOD = 1e9 + 7;
int c[MN][MN];
int K, N;

int compute_ckn(int k, int n) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    int r1 = c[k-1][n-1];
    if (r1 == 0) {
        r1 = compute_ckn(k-1, n-1);
        c[k-1][n-1] = r1;
    }

    int r2 = c[k][n-1];
    if (r2 == 0) {
        r2 = compute_ckn(k, n-1);
        c[k][n-1] = r2;
    }

    long res = r1 + r2;
    if (res > MOD) res -= MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> N;
    cout << compute_ckn(K, N);

    return 0;
}
