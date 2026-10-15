#include<bits/stdc++.h>
using namespace std;

const int MN = 901;

int a, b, c;
int dist[MN][MN];

int bfs() {
    memset(dist, -1, sizeof(dist));

    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == c || y == c) {
            return dist[x][y];
        }

        vector<pair<int, int>> nextStates;

        // 1. Fill jug A
        nextStates.push_back({a, y});

        // 2. Fill jug B
        nextStates.push_back({x, b});

        // 3. Empty jug A
        nextStates.push_back({0, y});

        // 4. Empty jug B
        nextStates.push_back({x, 0});

        // 5. Pour A -> B
        int pour = min(x, b - y);
        nextStates.push_back({x - pour, y + pour});

        // 6. Pour B -> A
        pour = min(y, a - x);
        nextStates.push_back({x + pour, y - pour});

        for (auto [nx, ny] : nextStates) {
            if (dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b >> c;
    cout << bfs();

    return 0;
}
