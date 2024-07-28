#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "bst.h"

using namespace std;

Node::Node(int val, int t) {
        value = val;
        time = t;
        left = nullptr;
        right = nullptr;
    };


BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

Node* BinarySearchTree::insert(Node* node, int val, int time) {
        if (node == nullptr) {
            node = new Node(val, time);
        } else if (val < node->value) {
            node->left = insert(node->left, val, time);
        } else {
            node->right = insert(node->right, val, time);
        }
        return node;
    }

void BinarySearchTree::insert(int val, int time) {
        root = insert(root, val, time);
    }

void BinarySearchTree::inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->value << " ";
        inorderTraversal(node->right);
    }
    
void BinarySearchTree::findClosestNumsHelper(Node* node, int time, int num, int k, priority_queue<pair<int, int>>& maxHeap, int& count) {
        if (node == nullptr) {
            return;
        }
        cout << "Kličem funkcijo za vozlišče: "<< node->value << endl;
        // cout << "Finding closest nums to the left of:" << node->value << endl;
        findClosestNumsHelper(node->left, time, num, k, maxHeap, count);
        if (node->time > time) {
            return;
        }
        maxHeap.push({ abs(node->value - num), node->value });
        
        count++;
        if (count > k) {
            maxHeap.pop();
        }
        // cout << "Finding closest nums to the right of:" << node->value << endl;
        findClosestNumsHelper(node->right, time, num, k, maxHeap, count);
    }
    
vector<int> BinarySearchTree::findClosestNums(int time, int num, int k) {
        if (root == nullptr) {
            return vector<int>();
        }
        std::priority_queue<std::pair<int, int>> maxHeap;
        int count = 0;
        // cout << "root:" << root->value << endl;
        findClosestNumsHelper(root, time, num, k, maxHeap, count);
        std::vector<int> closestNums;
        while (!maxHeap.empty()) {
            closestNums.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        reverse(closestNums.begin(), closestNums.end());
        return closestNums;
    }
