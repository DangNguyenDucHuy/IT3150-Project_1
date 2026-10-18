#include <bits/stdc++.h>
using namespace std;

const int MN = 1e6 + 1;
int n, m;
int a[MN];
bool nums[MN];
int res = 0;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        int num = m - a[i];
        if (num <= 0) continue;

        if (nums[num]) res++;
        nums[a[i]] = true;
    }

    cout << res;

    return 0;
}
