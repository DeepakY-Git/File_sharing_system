#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

int partition(int arr[], int s, int e){
    //step1 : choose pivotelement
    int pivotIndex = s;
    int pivotElement = arr[s];

    //step2 : find right poistion for pivot element and place it there
    int count = 0;
    for(int i = s+1; i<=e; i++){
        if(arr[i] <= pivotElement){
            count++;
        }
    }

    //jab loop se bhr aaye to pivot ki position ka index ready hai
    int rightIndex = s + count;
    swap(arr[pivotIndex], arr[rightIndex]);
    pivotIndex = rightIndex;

    //step 3: left me chhote number or right main bade number
    int i = s;
    int j = e;

    while(i < pivotIndex && j > pivotIndex){
        while(arr[i] <= pivotElement){
            i++;
        }
        while(arr[j] > pivotElement){
            j--;
        }

        // 2 case possible
        // A ---> you found the element to swap
        if( i < pivotIndex && j > pivotIndex){
            swap(arr[i], arr[j]);
        }

        // B ---> No need to Swap
    }
    return pivotIndex;
}
void quickSort(int arr[], int s, int e){
    //Base Case
    if(s>=e){
        return;
    }

    //Partition Logic
    int p = partition(arr, s, e);

    //recursive calls
    //left
    quickSort(arr, s, p-1);

    //right
    quickSort(arr, p+1, e);
}

int main(){
    int arr[] = {12,3,6,5,4,8,1,1,5,3,3,4,20,50,30};
    int n = 15;

    int s = 0;
    int e = n-1;
    quickSort(arr, s, e);

    for(int i = 0; i<n; i++){
        cout << arr[i] <<" ";
    }
    cout << endl;
    return 0;
}


