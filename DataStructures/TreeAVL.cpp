#include <bits/stdc++.h>

struct Node{
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree{
    private:
        Node* root;

        int height(Node* node) const {
            if(node == nullptr)
                return 0;
            return node->height;
        }

        int getBalancedFactor(Node* node) const {
            if(node == nullptr)
                return 0;
            return height(node->left) - height(node->right);
        }

        Node* rightRotate(Node* oldRoot){
            Node* newRoot = oldRoot->left;
            Node* orphanedSubtree = newRoot->right;

            newRoot->right = oldRoot;
            oldRoot->left = orphanedSubtree;

            oldRoot->height = std::max(height(oldRoot->left), height(oldRoot->right)) + 1;
            newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

            return newRoot;
        }

        Node* leftRotate(Node* oldRoot){
            Node* newRoot = oldRoot->right;
            Node* orphanedSubtree = newRoot->left;

            newRoot->left = oldRoot;
            oldRoot->right = orphanedSubtree;

            oldRoot->height = std::max(height(oldRoot->left), height(oldRoot->right)) + 1;
            newRoot->height = std::max(height(newRoot->left), height(newRoot->left)) + 1;

            return newRoot;
        }

        Node* insertHelper(Node* node, int val){
            if(node == nullptr)
                return new Node(val);

            if(val < node->data)
                node->left = insertHelper(node->left, val);
            else if (val > node->data)
                node->right = insertHelper(node->right, val);
            else
                return node;

            node->height = std::max(height(node->left), height(node->right)) + 1;

            int balance = getBalancedFactor(node);

            // Case 1: Left-Left Heavy
            if(balance > 1 && val < node->left->data)
                return rightRotate(node);

            // Case 2: Right-Right Heavy
            if(balance < -1 && val > node->right->data)
                return leftRotate(node);

            //Case 3: Left-Right Heavy
            if(balance > 1 && val > node->left->data){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // Case 4: Right-Left Heavy
            if(balance < -1 && val < node->right->data){
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        void preOrderHelper(Node* node) const{
            if(node != nullptr){
                std::cout << node->data << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        void freeMemory(Node* node){
            if(node != nullptr){
                freeMemory(node->left);
                freeMemory(node->right);
                delete node;
            }
        }

    public:
        AVLTree(){
            root = nullptr;
        }   

        void insert(int val){
            root = insertHelper(root, val);
        }

        void preOrder() const {
            preOrderHelper(root);
            std::cout << std::endl;
        }

        ~AVLTree(){
            freeMemory(root);
        }
};

int main(){
    AVLTree tree;

    // We will insert elements in ascending order: 10, 20, 30, 40, 50, 25.
    // In a standard BST, this would create a stick (a straight line to the right).
    // In an AVL tree, it will continuously rotate to stay perfectly balanced.
    
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Triggers a Left Rotation
    tree.insert(40);
    tree.insert(50); // Triggers another Left Rotation
    tree.insert(25); // Triggers a Right-Left Rotation

    std::cout << "Pre-Order Traversal of the balanced AVL tree is: \n";
    // Expected output: 30 20 10 25 40 50
    // Because 30 has been promoted to the root!
    tree.preOrder(); 

    return 0;
}