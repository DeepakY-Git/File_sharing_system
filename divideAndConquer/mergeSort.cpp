#include<iostream> 
#include<climits>
#include<vector>
using namespace std;
void merge(int* arr, int s, int e){
    int mid = (s+e)/2;

    int len1 = mid - s + 1;
    int len2 = e - mid;

    int* left = new int[len1];
    int* right = new int[len2];

    //copy values
    int k = s;
    for(int i = 0; i<len1; i++){
        left[i] =arr[k];
        k++;
    }

    k = mid + 1;
    for(int i = 0; i<len2; i++){
        right[i] = arr[k];
        k++;
    }

    //merge logic
    int leftIndex = 0; 
    int rightIndex = 0;
    int mainArrayIndex = s;

    while(leftIndex < len1 && rightIndex < len2){
        if(left[leftIndex] < right[rightIndex]){
            arr[mainArrayIndex++] = left[leftIndex++];
        }
        else{
            arr[mainArrayIndex++] = right[rightIndex++];
        }
    }
    //copy logic for left array
    while(leftIndex < len1){
        arr[mainArrayIndex++] = left[leftIndex++];
    }
    //copy for right array
    while(rightIndex < len2){
        arr[mainArrayIndex++] = right[rightIndex++];
    }
    //todp : delete left and right newly created
}
void mergeSort(int* arr, int s, int e){
    //  Base Case
    //s == e --> single element
    // s > e --> invalid array
    if(s>=e){
        return;
    }
    int mid = (s+e)/2;
    //left part sort by reccursion
    mergeSort(arr, s, mid);

    //right part sort by reccursion
    mergeSort(arr, mid+1, e);

    //merge 2 sorted arrays
    merge(arr, s, e);
    
}

int main(){
    int arr[] = {4,5,13,2,21,2,2,2};
    int n = 8;
    int s = 0;
    int e = n - 1;

    //calling mergeSort function
    mergeSort(arr, s, e);

    //printing array
    for(int i = 0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout<<endl;
    return 0;
}