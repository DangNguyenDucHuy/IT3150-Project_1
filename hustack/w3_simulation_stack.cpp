#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    stack<int> s;

    string cmd;
    int v;

    while (cin >> cmd) {
        if (cmd == "#") break;

        if (cmd == "PUSH") {
            cin >> v;
            s.push(v);
        } else if (cmd == "POP") {
            if (!s.empty()) {
                cout << s.top() << "\n";
                s.pop();
            } else {
                cout << "NULL\n";
            }
        }
    }

    return 0;
}
