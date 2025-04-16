/**
Parallel DFS and BFS for binary-trees
@author shubham0204 (Shubham Panchal)
@date   04/02/2024

Compilation:
$ g++ par_dfs_bfs.cpp -fopenmp
$ ./a.out
*/

#include <iostream>
#include <memory>
#include <omp.h>
#include <queue>
#include <stack>
#include <vector>

class TreeNode {
  public:
    int id;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int _id) : id(_id), left(nullptr), right(nullptr){};
};

class BinaryTree {
    TreeNode* _rootNode = nullptr;

  public:
    BinaryTree(const std::vector<int>& nodeIds) {
        if (nodeIds.empty()) {
            throw std::invalid_argument("nodes cannot be empty");
        }
        _rootNode = new TreeNode(nodeIds[0]);
        std::queue<TreeNode*> q;
        q.push(_rootNode);
        size_t i = 1;
        while (i < nodeIds.size()) {
            size_t queueSize = q.size();
            for (int j = 0; j < queueSize; j++) {
                TreeNode* node = q.front();
                q.pop();
                if (i < nodeIds.size() && nodeIds[i] != -1) {
                    node->left = new TreeNode(nodeIds[i]);
                    q.push(node->left);
                }
                i++;
                if (i < nodeIds.size() && nodeIds[i] != -1) {
                    node->right = new TreeNode(nodeIds[i]);
                    q.push(node->right);
                }
                i++;
            }
        }
    }

    ~BinaryTree() {
        if (_rootNode == nullptr)
            return;
        std::queue<TreeNode*> q;
        q.push(_rootNode);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            TreeNode* leftNode = node->left;
            TreeNode* rightNode = node->right;
            delete node;
            if (leftNode != nullptr) {
                q.push(leftNode);
            }
            if (rightNode != nullptr) {
                q.push(rightNode);
            }
        }
    }

    void parallelBFS(int numThreads) {
        if (_rootNode == nullptr)
            return;
        std::vector<TreeNode*> frontier;
        frontier.push_back(_rootNode);
        omp_set_num_threads(numThreads);
        while (!frontier.empty()) {
            size_t frontierSize = frontier.size();
// process all nodes in the frontier parallelly
#pragma omp parallel for
            for (size_t i = 0; i < frontierSize; i++) {
                // shared read-access to the frontier by all threads
                TreeNode* node = frontier[i];
// write-access needs to be atomic for the frontier
// hence, we start a critical section
#pragma omp critical
                {
                    std::cout << "node " << node->id << " traversed by thread " << omp_get_thread_num() << '\n';
                    if (node->left != nullptr) {
                        frontier.push_back(node->left);
                    }
                    if (node->right != nullptr) {
                        frontier.push_back(node->right);
                    }
                }
            }
            // remove visited nodes from the frontier
            frontier.erase(frontier.begin(), frontier.begin() + frontierSize);
        }
    }

    void parallelDFS(int numThreads) {
        if (_rootNode == nullptr)
            return;
        std::stack<TreeNode*> s;
        s.push(_rootNode);
        omp_set_num_threads(numThreads);
#pragma omp parallel
        {
            TreeNode* currentNode = nullptr;
#pragma omp critical
            {
                // pop a new node from the stack (frontier)
                // for expansion
                if (!s.empty()) {
                    currentNode = s.top();
                    s.pop();
                }
            }
            while (currentNode != nullptr) {
                std::cout << "node " << currentNode->id << " visited by thread " << omp_get_thread_num() << '\n';
                if (currentNode->right != nullptr) {
#pragma omp critical
                    {
                        // right child-node for currentNode
                        // will be picked up by another thread
                        // for further expansion
                        s.push(currentNode->right);
                    }
                }
                if (currentNode->left != nullptr) {
                    // the current thread keeps moving
                    // down the tree, in a depth-first manner
                    // extending the frontier of nodes
                    currentNode = currentNode->left;
                } else {
#pragma omp critical
                    {
                        if (!s.empty()) {
                            currentNode = s.top();
                            s.pop();
                        } else {
                            currentNode = nullptr;
                        }
                    }
                }
            }
        }
    }
};

int main(int argc, char* argv[]) {
    // A -1 indicates no child node
    // the following sequence is breadth-first representation
    // of the binary tree
    std::vector<int> nodeIds = {1, 4, 5, 6, -1, -1, 7, -1, 8, 9, -1};
    std::unique_ptr<BinaryTree> binaryTree = std::make_unique<BinaryTree>(nodeIds);

    int numThreads = 4;
    binaryTree->parallelBFS(numThreads);
    binaryTree->parallelDFS(numThreads);
}