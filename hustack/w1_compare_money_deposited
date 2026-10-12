#include<bits/stdc++.h>
using namespace std;

const int MN = 1e5 + 2;
int n;
int a[MN];
int m;
int pref[MN];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;

    pref[0] = 0;
    pref[1] = a[1];
    for (int i = 2; i <= n; i++) {
        pref[i] = pref[i-1] + a[i];
    }

    int i1, j1, i2, j2;
    for (int i = 0; i < m; i++) {
        cin >> i1 >> j1 >> i2 >> j2;
        int sum1 = pref[j1] - pref[i1-1];
        int sum2 = pref[j2] - pref[i2-1];
        cout << (sum1 < sum2) << "\n";
    }

    return 0;
}
