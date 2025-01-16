#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

bool isSorted(int arr[], int n, int i, int j){
    if(j==n){
        return true;
    }
    
    if(arr[i]<arr[j]){
        return isSorted(arr, n, i+1, j+1);
    }
    else{
        return false;
    }
}

int main(){
    
    int arr[5] = {10, 20, 30, 40 ,50};
    int n =5;
    int i = 0;
    int j = i+1;
    int ans = isSorted(arr, n, i, j);
    if(ans){
        cout << "Array is sorted."<<endl;
    }
    else{
        cout << "Not sorted array."<<endl;
    }
    


    return 0;
}