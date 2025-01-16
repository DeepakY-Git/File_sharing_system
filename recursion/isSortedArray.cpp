#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

bool isSorted(int arr[], int n, int i){
    if(i==n-1){
        return true;
    }
    
    if(arr[i]<=arr[i+1]){
        return isSorted(arr, n, i+1);
    }
    else{
        return false;
    }
}

int main(){
    
    int arr[5] = {10,20,30,40,50};
    int n =5;
    int i = 0;
    bool ans = isSorted(arr, n, i);
    if(ans){
        cout << "Array is sorted."<<endl;
    }
    else{
        cout << "Not sorted array."<<endl;
    }
    


    return 0;
}