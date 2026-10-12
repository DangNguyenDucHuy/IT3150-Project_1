#include<bits/stdc++.h>
using namespace std;

int n;

void backtrack(int cur, string s) {
    if (cur == n) {
        cout << s << "\n";
        return;
    }

    backtrack(cur+1, s + "0");
    backtrack(cur+1, s + "1");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    backtrack(0, "");

    return 0;
}
