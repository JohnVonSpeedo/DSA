#include <bits/stdc++.h>

struct Node{
    int data;
    Node* next;
    Node* prev;

    Node(int val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList{
    private:
        Node* head;
        Node* tail;

        void freeMemory(){
            Node* curr = head;
            while (curr != nullptr){
                Node* nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
        }

    public:
        DoublyLinkedList(){
            head = nullptr;
            tail = nullptr;
        }

        void insert_front(int val){
            Node* newNode = new Node(val);
            
            if(head == nullptr){
                head = newNode;
                tail = newNode;
                return;
            }

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        void insert_back(int val){
            Node* newNode = new Node(val);

            if(tail == nullptr){
                head = newNode;
                tail = newNode;
                return;
            }

            tail->next = newNode;
            newNode->prev = tail;

            tail = newNode;
        }

        void print_forward(){
            if(head == nullptr){
                std::cout << "Empty list!" << std::endl;
                return;
            }

            Node* curr = head;

            std::cout << "Forward: ";
            while(curr != nullptr){
                std::cout << curr->data;
                if(curr->next != nullptr)
                    std::cout << " <-> ";
                curr = curr->next;
            }
            std::cout << std::endl;
        }

        void print_backward(){
            if(tail == nullptr){
                std::cout << "Empty list!" << std::endl;
                return;
            }

            Node* curr = tail;

            std::cout << "Backward: ";
            while(curr != nullptr){
                std::cout << curr->data;
                if(curr->prev != nullptr)
                    std::cout << " <-> ";
                curr = curr->prev;
            }
            std::cout << std::endl;
        }

        ~DoublyLinkedList(){
            freeMemory();
        }
};

int main(){
    DoublyLinkedList list;

    list.insert_back(10);
    list.insert_back(20);
    list.insert_front(5);
    list.insert_back(30);

    // Expected: 5 <-> 10 <-> 20 <-> 30
    list.print_forward();
    
    // Expected: 30 <-> 20 <-> 10 <-> 5
    list.print_backward();

    return 0;
}