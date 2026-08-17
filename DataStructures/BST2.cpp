#include <iostream>

struct node
{
    node *parent; // родител
    node *left;   // ляв наследник
    node *right;  // десен наследник
    int value;    // стойност
    size_t size;  // брой елементи в дървото
                  // (1 + брой на елементите в двете поддървета)

    node(int v,
         node *p = nullptr,
         node *l = nullptr,
         node *r = nullptr) : value(v), parent(p), left(l),
                              right(r), size(1)
    {
        if (left)
            size += left->size;
        if (right)
            size += right->size;
    }
};

node *insert(node *&root, int value){
    if (root == nullptr)
        return new node(value);

    node *curr = root;
    node *p = nullptr;

    while (curr != nullptr){
        p = curr;
        if (value < curr->value)
            curr = curr->left;
        else if (value > curr->value)
            curr = curr->right;
        else
            return root;
    }

    node *newNode = new node(value, p);

    if (value < p->value)
        p->left = newNode;
    else if (value > p->value)
        p->right = newNode;

    curr = p;

    while (curr != nullptr){
        curr->size++;
        curr = curr->parent;
    }
    return root;
}

node *remove(node *root, int value){
    if (root == nullptr)
        throw std::invalid_argument("Error: Can't remove from empty tree!");

    node *curr = root;

    while (curr != nullptr && curr->value != value)
        if (value < curr->value)
            curr = curr->left;
        else
            curr = curr->right;

    if (curr == nullptr)
        return root;

    node *node_delete = curr;

    if (curr->left != nullptr && curr->right != nullptr){
        node *succ = curr->right;

        while (succ->left != nullptr)
            succ = succ->left;

        curr->value = succ->value;
        node_delete = succ;
    }

    node *child;

    if (node_delete->left != nullptr)
        child = node_delete->left;
    else
        child = node_delete->right;

    node *node_delete_parent = node_delete->parent;

    if (child != nullptr)
        child->parent = node_delete_parent;

    if (node_delete_parent == nullptr)
        root = child;
    else{
        if (node_delete == node_delete_parent->left)
            node_delete_parent->left = child;
        else
            node_delete_parent->right = child;
    }

    node *p = node_delete_parent;

    while (p != nullptr){
        p->size--;
        p = p->parent;
    }

    delete node_delete;
    return root;
}

int *to_array(const node *tree){
    if (tree == nullptr)
        throw std::invalid_argument("Error: Can't convert empty tree to array!");

    int *result = new int[tree->size];
    int idx = 0;

    const node *curr = tree;

    while (curr->left != nullptr)
        curr = curr->left;

    while (curr != nullptr){
        result[idx++] = curr->value;

        if (curr->right != nullptr){
            curr = curr->right;
            while (curr->left != nullptr)
                curr = curr->left;
        }
        else{
            const node *p = curr->parent;
            while (p != nullptr && curr == p->right){
                curr = p;
                p = p->parent;
            }
            curr = p;
        }
    }
    return result;
}

node *from_array(const int *arr, size_t size){
    node *root = nullptr;
    for (size_t i = 0; i < size; i++)
        root = insert(root, arr[i]);
    return root;
}

class Tree{
    private:
        node *root;

        void freeMemory(node *curr){
            if (curr != nullptr)
            {
                freeMemory(curr->left);
                freeMemory(curr->right);
                delete curr;
            }
        }

        void copy(const node *fromTree, node *&toTree, node *parent){
            if (fromTree == nullptr){
                toTree = nullptr;
                return;
            }

            toTree = new node(fromTree->value, parent);
            toTree->size = fromTree->size;

            copy(fromTree->left, toTree->left, toTree);
            copy(fromTree->right, toTree->right, toTree);
        }

    public:
        Tree(node *root = nullptr){
            this->root = root;
        }

        Tree(const Tree &other){
            copy(other.root, this->root, nullptr);
        }

        void insert(int value){
            this->root = ::insert(this->root, value);
        }

        void remove(int value){
            this->root = ::remove(this->root, value);
        }

        int *to_array(){
            return ::to_array(this->root);
        }

        void from_array(const int *arr, size_t size){
            freeMemory(this->root);
            this->root = ::from_array(arr, size);
        }

        int getSize(){
            if(root == nullptr)
                return 0;
            return root->size;
        }

        bool isEmpty(){
            return root == nullptr;
        }

        Tree &operator=(const Tree &other){
            if (this != &other){
                freeMemory(root);
                copy(other.root, this->root, nullptr);
            }
            return *this;
        }

        ~Tree(){
            freeMemory(root);
        }
};

int main(){
    // Създаваме дърво и добавяме 5 елемента в него
    Tree t;
    t.insert(10);
    t.insert(5);
    t.insert(7);
    t.insert(15);
    t.insert(3);

    int size = t.getSize();
    int *arr1 = t.to_array();

    // Принтираме размера и елементите на дървото
    std::cout << t.getSize() << std::endl;

    for (int i = 0; i < size; i++)
        std::cout << arr1[i] << " ";
    std::cout << std::endl;

    // Премахваме произволен елемент
    t.remove(10);

    size = t.getSize();
    int *arr2 = t.to_array();

    // Принтираме размера и елментите на дървото след промяната
    std::cout << size << std::endl;

    for (int i = 0; i < size; i++)
        std::cout << arr2[i] << " ";

    std::cout << std::endl;

    int source[4] = {12, 3, 5, 14};

    // Изчистваме дървото и зареждаме ново от масив
    t.from_array(source, 4);

    size = t.getSize();
    int *arr3 = t.to_array();

    std::cout << size << std::endl;

    for (int i = 0; i < size; i++)
        std::cout << arr3[i] << " ";
    std::cout << std::endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}