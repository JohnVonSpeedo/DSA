#include <bits/stdc++.h>

struct Node{
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = nullptr;
    }
};

class Stack{
    private:
        Node* topNode;
        int currentSize;

        void copy(const Stack& other){
            if(other.topNode == nullptr){
                topNode = nullptr;
                currentSize = 0;
                return;
            }

            topNode = new Node(other.topNode->data);
            currentSize = other.currentSize;

            Node* currentNode = topNode;
            Node* nextNode = other.topNode->next;

            while(nextNode != nullptr){
                currentNode->next = new Node(nextNode->data);
                currentNode = currentNode->next;
                nextNode = nextNode->next;
            }
        }

        void freeMemory(){
            while(!isEmpty()){
                pop();
            }
        }

    public:
        Stack(){
            topNode = nullptr;
            currentSize = 0;
        }

        Stack(const Stack& other){
            copy(other);
        }

        void push(int key){
            Node* newNode = new Node(key);
            newNode->next = topNode;
            topNode = newNode;
            currentSize++;
        }

        void pop(){
            if(isEmpty())
                throw std::underflow_error("Stack is empty!");

            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            currentSize--;
        }

        int peek() const{
            if(isEmpty())
                throw std::underflow_error("Stack is empty!");
            return topNode->data;
        }

        bool isEmpty() const{
            return topNode == nullptr;
        }

        int size() const{
            return currentSize;
        }

        Stack& operator=(const Stack& other){
            if (this != &other){
                freeMemory();
                copy(other);
            }

            return *this;
        }

        ~Stack(){
            freeMemory();
        }
};

int main(){
    return 0;
}