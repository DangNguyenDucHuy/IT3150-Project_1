#include <bits/stdc++.h>
using namespace std;

map<string, bool> keys;

bool findKey(string key) {
    return (keys.find(key) != keys.end());
}

bool insertKey(string key) {
    if (findKey(key)) return false;
    keys[key] = true;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string cmd, k;

    while (cin >> k) {
        if (k == "*") break;
        insertKey(k);
    }

    while (cin >> cmd) {
        if (cmd == "***") break;
        cin >> k;
        if (cmd == "find") cout << findKey(k);
        if (cmd == "insert") cout << insertKey(k);
        cout << "\n";
    }

    return 0;
}
