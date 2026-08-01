#include <bits/stdc++.h>

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree{
    private:
        Node* root;

        Node* insertRecursive(Node* current, int key){
            if(current = nullptr)
                return new Node(key);

            if(key < current->data)
                current->left = insertRecursive(current->left, key);
            else if(key > current->data)
                current->right = insertRecursive(current->right, key);

            return current;
        }

        Node* searchRecursive(Node* current, int key){
            if(current == nullptr || current->data == key)
                return current;

            if(key < current->data)
                return searchRecursive(current->left, key);
            else
                return searchRecursive(current->right, key);
        }

        void inOrderRecursive(Node* current, std::vector<int> &result){
            if(current != nullptr){
                inOrderRecursive(current->left, result);
                result.push_back(current->data);
                inOrderRecursive(current->right, result);
            }
        }

        void destroyRecursive(Node* current){
            if(current != nullptr){
                destroyRecursive(current->left);
                destroyRecursive(current->right);
                delete current;
            }
        }

    public:
        BinaryTree(){
            root = nullptr;
        }

        void insert(int key){
            root = insertRecursive(root, key);
        }

        Node* search(int key){
            return searchRecursive(root, key);
        }

        std::vector<int> inOrderTraversal(){
            std::vector<int> result;
            inOrderRecursive(root, result);
            return result;
        }
};