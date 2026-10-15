#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    queue<int> q;

    string cmd;
    int v;

    while (cin >> cmd) {
        if (cmd == "#") break;

        if (cmd == "PUSH") {
            cin >> v;
            q.push(v);
        } else if (cmd == "POP") {
            if (!q.empty()) {
                cout << q.front() << "\n";
                q.pop();
            } else {
                cout << "NULL\n";
            }
        }
    }

    return 0;
}
