#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    vector<Node*> child;
    Node(int id) : id(id) {}
};

map<int, Node*> nodes;
Node* root = nullptr;

Node* getNode(int id) {
    if (!nodes.count(id)) nodes[id] = new Node(id);
    return nodes[id];
}

void preOrder(Node* u) {
    if (!u) return;
    cout << u->id << " ";
    for (Node* v : u->child) preOrder(v);
}

void inOrder(Node* u) {
    if (!u) return;
    if (u->child.empty()) {
        cout << u->id << " ";
        return;
    }
    inOrder(u->child[0]);
    cout << u->id << " ";
    for (int i = 1; i < (int)u->child.size(); i++)
        inOrder(u->child[i]);
}

void postOrder(Node* u) {
    if (!u) return;
    for (Node* v : u->child) postOrder(v);
    cout << u->id << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string cmd;
    int u, v;

    while (cin >> cmd && cmd != "*") {
        if (cmd == "MakeRoot") {
            cin >> u;
            if (!nodes.count(u)) root = getNode(u);
        } else if (cmd == "Insert") {
            cin >> u >> v;
            if (nodes.count(u) || !nodes.count(v)) continue;
            getNode(v)->child.push_back(getNode(u));
        } else {
            if (cmd == "PreOrder") preOrder(root);
            else if (cmd == "InOrder") inOrder(root);
            else if (cmd == "PostOrder") postOrder(root);
            cout << '\n';
        }
    }

    return 0;
}
