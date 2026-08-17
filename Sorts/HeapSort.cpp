#include <iostream>
#include <vector>

std::vector<int> heapify(std::vector<int>& arr, int length, int i){
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if(left_child < length && arr[left_child] > arr[largest])
        largest = left_child;
    
    if(right_child < length && arr[right_child] > arr[largest])
        largest = right_child;

    if(largest != i){
        std::swap(arr[i], arr[largest]);
        heapify(arr, length, largest);
    }
}

std::vector<int> heapSort(std::vector<int> &arr){
    int length = arr.size();
    for(int i = length / 2 - 1; i >= 0; i++)
        heapify(arr, length, i);

    for(int i = length - 1; i > 0; i--){
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main(){
    std::vector<int> nums = {5, 4, 8, 7, 3, 12, 6, 2};
    int length = nums.size();
    heapSort(nums);
    for (int i = 0; i < length; i++)
        std::cout << nums[i] << " ";
    return 0;
}