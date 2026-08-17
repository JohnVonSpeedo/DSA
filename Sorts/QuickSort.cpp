#include <bits/stdc++.h>

int partition(std::vector<int> &arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
        if(arr[j] < pivot){
            i++;
            std::swap(arr[i], arr[j]);
        }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int> &arr, int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){
    std::vector<int> nums = {5, 4, 8, 7, 3, 12, 6, 2};
    int length = nums.size();
    quickSort(nums, 0, length - 1);
    for (int i = 0; i < length; i++)
        std::cout << nums[i] << " ";
    return 0;
}