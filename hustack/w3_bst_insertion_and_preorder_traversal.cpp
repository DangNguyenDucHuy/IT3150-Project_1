#include<bits/stdc++.h>
using namespace std;

const int DEFAULT_VALUE = 0;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int val) {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};

Node* root = new Node(DEFAULT_VALUE);

void insertNode(Node* cur, int val) {
    if (cur->val == DEFAULT_VALUE) {
        cur->val = val;
        return;
    }

    if (cur->val == val) return;

    if (val > cur->val) {
        if (cur->right == NULL) {
            cur->right = new Node(val);
        } else {
            insertNode(cur->right, val);
        }
        return;
    }

    if (val < cur->val) {
        if (cur->left == NULL) {
            cur->left = new Node(val);
        } else {
            insertNode(cur->left, val);
        }
        return;
    }
}

void BSTPreorderTraversal(Node* cur) {
    if (cur == NULL) return;
    cout << cur->val << " ";
    BSTPreorderTraversal(cur->left);
    BSTPreorderTraversal(cur->right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string command;
    int k;

    while ((cin >> command) && (command != "#")) {
        cin >> k;
        insertNode(root, k);
    }

    BSTPreorderTraversal(root);

    return 0;
}
