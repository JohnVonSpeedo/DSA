#include<bits/stdc++.h>

struct Node{
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = nullptr;
    }
};

class LinkedList{
    private:
        Node* head;

        void freeMemory(){
            Node* curr = head;
            while(curr->next != nullptr){
                Node* nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
        }

        void copy(const LinkedList &other){
            if(other.head == nullptr){
                head = nullptr;
                return;
            }

            head = new Node(other.head->data);

            Node* currentNew = head;
            Node* currentOther = other.head->next;

            while(currentOther != nullptr){
                currentNew->next = new Node(currentOther->data);
                currentNew = currentNew->next;
                currentOther = currentOther->next;
            }
        }

    public:
        LinkedList(){
            head = nullptr;
        }

        LinkedList(const LinkedList &other){
            copy(other);
        }

        void insert_back(int val){
            Node* newNode = new Node(val);

            Node* curr = head;

            if(head == nullptr){
                head = newNode;
                return;
            }

            while(curr->next != nullptr)
                curr = curr->next;

            curr->next = newNode;
        }

        void insert_front(int val){
            Node* newNode = new Node(val);
            newNode->next = head;
            head = newNode;
        }

        void print(){
            if(head == nullptr){
                std::cout << "Empty list!" << std::endl;
                return;
            }

            Node* curr = head;
            while(curr->next != nullptr){
                std::cout << curr->data << " -> ";
                curr = curr->next;
            }
            std::cout << curr->data << std::endl;
        }

        LinkedList& operator=(const LinkedList &other){
            if(this != &other){
                freeMemory();
                copy(other);
            }
            return *this;
        }

        ~LinkedList(){
            freeMemory();
        }
};

int main(){
    return 0;
}