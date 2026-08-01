#include <bits/stdc++.h>

struct Task{
    int priority;
    std::string data;

    Task(int p, std::string val){
        priority = p;
        data = val;
    }
};



class PriorityQueue{

    private:
        std::vector<Task> heap;

        int parent(int i){
            return (i - 1) / 2;
        }

        int leftChild(int i){
            return 2 * i + 1;
        }

        int rightChild(int i){
            return 2 * i + 2;
        }

        void siftUp(int i){
            while(i > 0 && heap[i].priority > heap[parent(i)].priority){
                std::swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }

        void siftDown(int i){
            int maxIndex = i;
            int left = leftChild(i);
            int right = rightChild(i);

            if(left < heap.size() && heap[left].priority > heap[maxIndex].priority)
                maxIndex = left;

            if(right < heap.size() && heap[right].priority > heap[maxIndex].priority)
                maxIndex = right;

            if(i != maxIndex){
                std::swap(heap[i], heap[maxIndex]);
                siftDown(maxIndex);
            }
        }

        void copy(const PriorityQueue &other){
            heap = other.heap;
        }

        void freeMemory(){

        }

    public:
        PriorityQueue(){
            heap = std::vector<Task>();
        }

        PriorityQueue(const PriorityQueue &other){
            copy(other);
        }

        void enqueue(Task task){
            heap.push_back(task);
            siftUp(heap.size() - 1);
        }

        Task dequeue(){
            if(isEmpty())
                throw std::underflow_error("Priority queue is empty!");

            Task root = heap[0];
            heap[0] = heap.back();
            heap.pop_back();

            if(!isEmpty())
                siftDown(0);

            return root;
        }

        Task peek() const {
            if(isEmpty())
                throw std::underflow_error("Priority queue is empty!");

            return heap[0];
        }

        bool isEmpty() const {
            return heap.empty();
        }

        PriorityQueue& operator=(const PriorityQueue &other){
            if(this != &other){
                freeMemory();
                copy(other);
            }
            return *this;
        }
};

int main() {
    PriorityQueue pq;
    Task task1(3, "Update documentation");
    Task task2(1, "Fix critical server crash");
    Task task3(5, "Refactor old code");
    Task task4(2, "Respond to client email");


    // Enqueue tasks out of order
    pq.enqueue(task1);
    pq.enqueue(task2);
    pq.enqueue(task3);
    pq.enqueue(task4);

    // Dequeue them (they will come out in priority order 1, 2, 3, 5)
    while(!pq.isEmpty()) {
        Task t = pq.dequeue();
        std::cout << "Priority " << t.priority << ": " << t.data << std::endl;
    }

    return 0;
}