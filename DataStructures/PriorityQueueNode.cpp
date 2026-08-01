#include<bits/stdc++.h>

struct Node{
    int data;
    int priority;
    Node* next;

    Node(int val, int p){
        data = val;
        priority = p;
        next = nullptr;
    }
};

class PriorityQueue{
    private:
        Node* head;

        void freeMemory(){
            while(!isEmpty()){
                pop();
            }
        }

    public:
        PriorityQueue(){
            head = nullptr;
        }

        void push(int val, int priority){
            Node* newNode = new Node(val, priority);

            if(head == nullptr || priority > head->priority){
                newNode->next = head;
                head = newNode;
                return;
            }

            Node* curr = head;

            while(curr->next != nullptr && curr->next->priority >= priority)
                curr = curr->next;

            newNode->next = curr->next;
            curr->next = newNode;
        }

        void pop(){
            if(head == nullptr)
                throw std::underflow_error("The queue is empty!");

            Node* temp = head;
            head = head->next;
            delete temp;
        }

        int top() const {
            if (head == nullptr)
                throw std::underflow_error("The queue is empty!");
            return head->data;
        }

        bool isEmpty() const{
            return head == nullptr;
        }

        void display(){
            if(head == nullptr){
                std::cout << "The queue is empty!" << std::endl;
                return;
            }

            Node* curr = head;

            while(curr != nullptr){
                std::cout << "[Data: " << curr->data << " | " << "Priority: " << curr->priority << "] -> ";
                curr = curr->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        ~PriorityQueue(){
            freeMemory();
        }
};

int main(){
    PriorityQueue pq;

    // Pushing data with varying priorities
    pq.push(100, 1);  // Low priority
    pq.push(200, 5);  // High priority
    pq.push(300, 3);  // Medium priority
    pq.push(400, 5);  // Tied for high priority

    std::cout << "Queue structure:" << std::endl;
    pq.display(); 
    // Expected order: 200(P5) -> 400(P5) -> 300(P3) -> 100(P1)

    std::cout << std::endl << "Processing top element: " << pq.top() << std::endl;
    pq.pop();

    std::cout << "Queue after one pop:\n";
    pq.display();

    return 0;
}