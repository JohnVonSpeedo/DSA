#include <bits/stdc++.h>

struct Node{
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = nullptr;
    }
};

class Queue{
    private:
        Node* front;
        Node* back;
        int currentSize;

        void copy(const Queue &other){
            if(other.isEmpty()){
                front = nullptr;
                back = nullptr;
                currentSize = 0;
                return;
            }

            front = new Node(other.front->data);
            back = front;
            currentSize = other.currentSize;

            Node* currentNode = other.front->next;
            while(currentNode != nullptr){
                back->next = new Node(currentNode->data);
                back = currentNode;
                currentNode = currentNode->next;
            }
        }

        void freeMemory(){
            while(!isEmpty())
                dequeue();
        }

    public:
        Queue(){
            front = nullptr;
            back = nullptr;
            currentSize = 0;
        }

        Queue(const Queue &other){
            copy(other);
        }

        void enqueue(int val){
            Node* newNode = new Node(val);

            if(isEmpty()){
                front = newNode;
                back = newNode;
            }
            else{
                back->next = newNode;
                back = newNode;
            }
            currentSize++;
        }

        void dequeue(){
            if(isEmpty())
                throw std::underflow_error("Queue is empty!");

            Node* temp = front;
            front = front->next;
            delete temp;
            currentSize--;

            if(currentSize == 0){
                back = nullptr;
            }
        }

        int getFront() const {
            if(isEmpty())
                throw std::underflow_error("Queue is empty!");

            return front->data;
        }

        int getback() const {
            if(isEmpty())
                throw std::underflow_error("Queue is empty!");

            return back->data;
        }

        int size() const {
            return currentSize;
        }

        bool isEmpty() const {
            return currentSize == 0;
        }

        Queue& operator=(const Queue &other){
            if(this != &other){
                freeMemory();
                copy(other);
            }
            return *this;
        }

        ~Queue(){
            freeMemory();
        }
};


int main(){
    return 0;
}