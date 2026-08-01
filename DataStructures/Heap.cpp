#include <bits/stdc++.h>

class MinHeap{
    private:
        std::vector<int> heap;

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
            while(i > 0 && heap[i] < heap[parent(i)]){
                std::swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }

        void siftDown(int i){
            int minIndex = i;
            int left = leftChild(i);
            int right = rightChild(i);
            
            if(left < heap.size() && heap[left] < heap[minIndex])
                minIndex = left;

            if(right < heap.size() && heap[right] < heap[minIndex])
                minIndex = right;

            if(i != minIndex){
                std::swap(heap[i], heap[minIndex]);
                siftDown(minIndex);
            }
        }

        void copy(const MinHeap &other){
            heap = other.heap;
        }

        void freeMemory(){

        }

    public:
        MinHeap(){
            heap = std::vector<int>();
        }

        MinHeap(const MinHeap &other){
            copy(other);
        }

        void insert(int val){
            heap.push_back(val);
            siftUp(heap.size() - 1);
        }

        int extractMin() {
            if(isEmpty())
                throw std::underflow_error("Heap is empty!");

            int root = heap[0];
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();

            if(!isEmpty())
                siftDown(0);

            return root;
        }

        int peek() const {
            if(isEmpty())
                throw std::underflow_error("Heap is empty!");
            return heap[0];
        }

        bool isEmpty() const {
            return heap.empty();
        }

        MinHeap& operator=(const MinHeap &other){
            if(this != &other){
                freeMemory();
                copy(other);
            }
            return *this;
        }

        ~MinHeap(){
            freeMemory();
        }
};

int main(){
    return 0;
}