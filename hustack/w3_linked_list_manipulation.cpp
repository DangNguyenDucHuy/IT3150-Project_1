#include<bits/stdc++.h>
using namespace std;

const int MN = 1e4 + 1;
int n;
int a[MN];



class LinkedNode {
public:
    int key;
    LinkedNode* prev;
    LinkedNode* next;

    LinkedNode(int key = 0) {
        this->key = key;
        this->prev = NULL;
        this->next = NULL;
    }
};

map<int, LinkedNode*> mapKeyToNode;



class LinkedList {
public:
    LinkedNode* head;
    LinkedNode* tail;

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
    }

    LinkedNode* getNode(int key) {
        if (mapKeyToNode.find(key) == mapKeyToNode.end()) return NULL;
        return mapKeyToNode[key];
    }

    LinkedNode* addNode(int key) {
        LinkedNode* foundNode = getNode(key);
        if (foundNode != NULL) return NULL;

        LinkedNode* newNode = new LinkedNode(key);
        mapKeyToNode[key] = newNode;

        return newNode;
    }

    void addLast(int key) {
        LinkedNode* newNode = addNode(key);
        if (newNode == NULL) return;

        if (head == NULL) head = newNode;
        if (tail == NULL) {
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = tail->next;
        }
    }

    void addFirst(int key) {
        LinkedNode* newNode = addNode(key);
        if (newNode == NULL) return;

        if (tail == NULL) this->tail = newNode;
        if (head == NULL) {
            this->head = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = head->prev;
        }
    }

    void addAfter(int pos, int key) {
        LinkedNode* posNode = getNode(pos);
        if (posNode == NULL) return;

        LinkedNode* newNode = addNode(key);
        if (newNode == NULL) return;

        LinkedNode* nextPosNode = posNode->next;

        posNode->next = newNode;
        newNode->prev = posNode;

        if (nextPosNode != NULL) {
            newNode->next = nextPosNode;
            nextPosNode->prev = newNode;
        } else {
            tail = newNode;
        }
    }

    void addBefore(int pos, int key) {
        LinkedNode* posNode = getNode(pos);
        if (posNode == NULL) return;

        LinkedNode* newNode = addNode(key);
        if (newNode == NULL) return;

        LinkedNode* prevPosNode = posNode->prev;

        newNode->next = posNode;
        posNode->prev = newNode;

        if (prevPosNode != NULL) {
            newNode->prev = prevPosNode;
            prevPosNode->next = newNode;
        } else {
            head = newNode;
        }
    }

    void removeNode(int key) {
        LinkedNode* foundNode = getNode(key);
        if (foundNode == NULL) return;

        LinkedNode* prevNode = foundNode->prev;
        LinkedNode* nextNode = foundNode->next;

        if (prevNode != NULL) prevNode->next = nextNode;
            else head = nextNode;
        if (nextNode != NULL) nextNode->prev = prevNode;
            else tail = prevNode;

        mapKeyToNode.erase(key);
        delete foundNode;
    }

    void reverseList() {
        LinkedNode* cur = head;

        while (cur != NULL) {
            swap(cur->prev, cur->next);
            cur = cur->prev;
        }

        swap(head, tail);
    }

    void printList() {
        LinkedNode* cur = head;

        while (cur != NULL) {
            cout << cur->key << " ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

LinkedList* llist = new LinkedList();


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        llist->addLast(a[i]);
    }

    string cmd;
    int k, v;

    while (cin >> cmd) {
        if (cmd == "#") break;

        if (cmd == "reverse") {
            llist->reverseList();
            continue;
        }

        cin >> k;

        if (cmd == "addlast") llist->addLast(k);
        else if (cmd == "addfirst") llist->addFirst(k);
        else if (cmd == "addafter") { cin >> v; llist->addAfter(v, k); }
        else if (cmd == "addbefore") { cin >> v; llist->addBefore(v, k); }
        else if (cmd == "remove") llist->removeNode(k);
    }

    llist->printList();

    return 0;
}
