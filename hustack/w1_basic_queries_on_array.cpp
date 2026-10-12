#include<bits/stdc++.h>
using namespace std;

const int MN = 1e4 + 1;
const int MM = 1e3;
int n;
int a[MN];

int maxx = -MN;
int minn = MN;
int sum = 0;

void findSumMaxMin() {
    for (int i = 0; i < n; i++) {
        sum += a[i];
        maxx = max(a[i], maxx);
        minn = min(a[i], minn);
    }
}

int findMaxSegment(int l, int r) {
    int mx = -MN;
    for (int i = l-1; i <= r-1; i++) {
        mx = max(a[i], mx);
    }
    return mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    findSumMaxMin();

    string tmp;
    cin >> tmp;

    string command;
    int l, r;

    while (cin >> command) {
        if (command == "find-max") cout << maxx << "\n";
        else if (command == "find-min") cout << minn << "\n";
        else if (command == "sum") cout << sum << "\n";
        else if (command == "find-max-segment") {
            cin >> l >> r;
            cout << findMaxSegment(l, r) << "\n";
        }
        else break;
    }

    return 0;
}
