#include <bits/stdc++.h>
using namespace std;

const int BASE = 256;
const int MK = 201;
int base[MK];
int n, m;

int computeBase(int k) {
    if (base[k] != 0) return base[k];
    base[k] = (computeBase(k-1) * BASE) % m;
    return base[k];
}

void process(string s) {
    int k = s.length();
    int h = 0;

    for (int i = 0; i < k; i++) {
        int c = s[i];
        h += c * computeBase(k-i-1);
        h %= m;
    }

    cout << h << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    base[0] = 1;

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        process(s);
    }

    return 0;
}
