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

    void splitChild(shared_ptr<Node> node, int index) {
        shared_ptr<Node> oldChild = node->children[index];

        shared_ptr<Node> newChild = make_shared<Node>(oldChild->isLeaf);

        node->children.insert(node->children.begin() + index + 1, newChild);
        node->keys.insert(node->keys.begin() + index + 1, oldChild->keys[minimumDegree - 1]);

        for (int i = minimumDegree; i < oldChild->keys.size(); i++) {
            newChild->keys.push_back(oldChild->keys[i]);
        } 

        for (int i = minimumDegree - 1; i < oldChild->keys.size(); i++) {
            newChild->keys.pop_back();
        } 

        if (!newChild->isLeaf) {
            for (int i = minimumDegree; i < oldChild->children.size(); i++) {
                newChild->children.push_back(oldChild->children[i]);
            } 

            for (int i = minimumDegree - 1; i < oldChild->children.size(); i++) {
                newChild->children.pop_back();
            } 
        }




        // for (int i = index + 1; i < oldChild->children.size(); i++) {
        //     newChild->children.push_back(oldChild->children[i]);
        // }


    }

public:
    pair<shared_ptr<Node>, int> NOTFOUND = pair<shared_ptr<Node>, int> (nullptr, -1);
private:
    int minimumDegree;
    shared_ptr<Node> root;

};
