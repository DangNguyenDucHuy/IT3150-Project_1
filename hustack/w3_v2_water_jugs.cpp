#include<bits/stdc++.h>
using namespace std;

int a, b, c;

// ax + by = c
// -> a | (c - by)
// -> try y = -(a-1), -(a-2), ..., -1, 0, 1, ..., a-1
void process() {
    for (int i = 0; i <= (a-1); i++) {
        int tp = c + b * i;
        if (tp % a == 0) {
            // steps = x1 + x2
            cout << tp / a + i;
            return;
        }

        int tn = c - b * i;
        if (tn % a == 0) {
            cout << tn / a + i;
            return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b >> c;
    process();

    return 0;
}
