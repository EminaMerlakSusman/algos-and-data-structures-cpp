#ifndef BST_H
#define BST_H
#include <vector>
#include <queue>
#include <algorithm>

class Node {
public:
    int value;
    Node* left;
    Node* right;
    int time;

    Node(int val, int t);
};

class BinarySearchTree {
public:
    BinarySearchTree();
    std::vector<int> findClosestNums(int time, int num, int k);
    void insert(int val, int time);

private:
    Node* root;

    Node* insert(Node* node, int val, int time);
    void inorderTraversal(Node* node);
    void findClosestNumsUtil(Node* node, int time, int num, int k, std::vector<int>& closest);
    void findClosestNumsHelper(Node* node, int time, int num, int k, std::priority_queue<std::pair<int, int>>& maxHeap, int& count);
    void findKthSmallestUtil(Node* node, int k, std::vector<int>& res);
};

#endif // BST_H