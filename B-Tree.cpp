#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class BTree {
    class Node {
    public:
        vector<int> keys;
        vector<shared_ptr<Node>> children;
        bool isLeaf;

        Node(bool isLeaf = false): isLeaf(isLeaf){} 
    };

public:
    BTree (int minimumDegree) : minimumDegree(minimumDegree) {
        root = make_shared<Node>(true);
    }

    pair<shared_ptr<Node>, int> search(int key, shared_ptr<Node> node = nullptr) {
        shared_ptr<Node> currentNode = (node == nullptr)? root : node;

        int i = 0;
        while (i < currentNode->keys.size() && key > currentNode->keys[i]) {
           i++; 
        }

        if (i < currentNode->keys.size() && key == currentNode->keys[i]) {
            return pair<shared_ptr<Node>, int> (currentNode, i);
        } else if (currentNode == nullptr) {
            return NOTFOUND;
        } else {
            search(key, currentNode->children[i]);
        }

    }

public:
    pair<shared_ptr<Node>, int> NOTFOUND = pair<shared_ptr<Node>, int> (nullptr, -1);
private:
    int minimumDegree;
    shared_ptr<Node> root;

};
