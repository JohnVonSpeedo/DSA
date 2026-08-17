#include <bits/stdc++.h>

void merge(std::vector<int> &arr, int left, int mid, int right){
    int length1 = mid - left + 1;
    int length2 = right - mid; 

    std::vector<int> L(length1), R(length2);

    for(int i = 0; i < length1; i++)
        L[i] = arr[left + i];
    for(int i = 0; i < length2; i++)
        R[i] = arr[mid + 1 + i];

    int idx1 = 0;
    int idx2 = 0;
    int curr = left;

    while(idx1 < length1 && idx2 < length2){
        if(L[idx1] <= R[idx2]){
            arr[curr] = L[idx1];
            idx1++;
        }
        else{
            arr[curr] = R[idx2];
            idx2++;
        }
        curr++;
    }

    while(idx1 < length1){
        arr[curr] = L[idx1];
        idx1++;
        curr++;
    }

    while(idx2 < length2){
        arr[curr] = R[idx2];
        idx2++;
        curr++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right){
    if(left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main(){
    return 0;
}