std::vector<int> heapify(std::vector<int>& arr, int length, int i){
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2* i + 2;

    if(left_child < length && arr[left_child] > arr[largest])
        largest = left_child;
    
    if(right_child < length && arr[right_child] > arr[largest])
        largest = right_child;

    if(largest != i){
        swap(arr[i], arr[largest])
        heapify(arr, length, largest);
    }
}

std::vector<int> heapSort(std::vector<int> &arr){
    int length = arr.size();
    for(int i = length / 2 - 1; i >= 0; i++)
        heapify(arr, legnth, i);

    for(int i = n - 1; i > 0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main(){
    return 0;
}