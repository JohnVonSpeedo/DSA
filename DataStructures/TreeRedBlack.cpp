#include<bits/stdc++.h>

enum Color{
    RED,
    BLACK
};

struct RBNode{
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int val){
        data = val;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree{
    private:
        RBNode* root;

        void freeMemory(RBNode* node){
            if(node != nullptr){
                freeMemory(node->left);
                freeMemory(node->right);
                delete node;
            }
        }

    void leftRotate(RBNode* oldRoot){
        RBNode* newRoot = oldRoot->right;
        oldRoot->right = newRoot->left;

        if(newRoot->left != nullptr)
            newRoot->left->parent = oldRoot;

        newRoot->parent = oldRoot->parent;

        if(oldRoot->parent == nullptr)
            root = newRoot;
        else if(oldRoot == oldRoot->parent->left)
            oldRoot->parent->left = newRoot;
        else
            oldRoot->parent->right = newRoot;

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(RBNode* oldRoot){
        RBNode* newRoot = oldRoot->left;
        oldRoot->left = newRoot->right;

        if(newRoot->right != nullptr)
            newRoot->right->parent = oldRoot;

        newRoot->parent = oldRoot->parent;

        if(oldRoot->parent == nullptr)
            root = newRoot;
        else if(oldRoot == oldRoot->parent->right)
            oldRoot->parent->right = newRoot;
        else
            oldRoot->parent->left = newRoot;

        newRoot->right = oldRoot;
        oldRoot->parent = newRoot;
    }

    void fixInsert(RBNode* node){
        while(node != root && node->parent->color == RED){
            RBNode* grandparent = node->parent->parent;

            if(node->parent == grandparent->left){
                RBNode* uncle = grandparent->right;

                if(uncle != nullptr && uncle->color == RED){
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else{
                    if(node == node->parent->right){
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            else{
                RBNode* uncle = grandparent->left;
                if(uncle != nullptr && uncle->color == RED){
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else{
                    if(node == node->parent->left){
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void inOrderHelper(RBNode* node){
        if(node == nullptr)
            return;
        inOrderHelper(node->left);
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")";
        inOrderHelper(node->right);
    }

    public:
        RedBlackTree(){
            root = nullptr;
        }

        void insert(int data){
            RBNode* newNode = new RBNode(data);

            RBNode* parent = nullptr;
            RBNode* current = root;

            while(current != nullptr){
                parent = current;
                if(newNode->data < current->data)
                    current = current->left;
                else
                    current = current->right;
            }

            newNode->parent = parent;

            if(parent == nullptr)
                root = newNode;
            else if(newNode->data < parent->data)
                parent->left = newNode;
            else
                parent->right = newNode;

            if(newNode->parent == nullptr){
                newNode->color = BLACK;
                return;
            }
            if(newNode->parent->parent == nullptr)
                return;

            fixInsert(newNode);
        }

        void printTree(){
            inOrderHelper(root);
            std::cout << std::endl;
        }

        ~RedBlackTree(){
            freeMemory(root);
        }
};

int main(){
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Triggers Uncle=Black, Line shape -> Rotation and recolor
    tree.insert(15); // Triggers Uncle=Red -> Recolor cascade

    std::cout << "In-Order Traversal (Value and Color): \n";
    tree.printTree();

    return 0;
}