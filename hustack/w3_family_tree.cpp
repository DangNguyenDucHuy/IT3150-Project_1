#include<bits/stdc++.h>
using namespace std;

class PersonNode {
public:
    string name;
    vector<PersonNode*> children;

    PersonNode(string name) {
        this->name = name;
    }

    int countDescendants() {
        int des = this->children.size();
        for (PersonNode* child : this->children) {
            des += child->countDescendants();
        }
        return des;
    }

    int countGeneration() {
        int gen = 0;
        for (PersonNode* child : this->children) {
            gen = max(gen, child->countGeneration() + 1);
        }
        return gen;
    }
};

map<string, PersonNode*> personList;

PersonNode* getPerson(string name) {
    if (personList.find(name) == personList.end()) {
        personList[name] = new PersonNode(name);
    }
    return personList[name];
}

void addRelationship(string childName, string parentName) {
    PersonNode* child = getPerson(childName);
    PersonNode* parent = getPerson(parentName);
    parent->children.push_back(child);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string childName, parentName;
    while (cin >> childName) {
        if (childName == "***") break;
        cin >> parentName;
        addRelationship(childName, parentName);
    }

    string cmd, name;
    while (cin >> cmd) {
        if (cmd == "***") break;
        cin >> name;

        PersonNode* parent = personList[name];
        if (parent == NULL) {
            cout << "0\n";
            continue;
        }

        if (cmd == "descendants") {
            cout << parent->countDescendants() << "\n";
        }
        if (cmd == "generation") {
            cout << parent->countGeneration() << "\n";
        }
    }

    return 0;
}
