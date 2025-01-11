#include<iostream> 
#include<vector>
using namespace std;

// void printArray(vector<int>nums){
//     if(nums.size()==0){
//         return;
//     }
//     cout << nums[nums.size()-1] << " ";
//     nums.pop_back();
//     printArray(nums);

// }
void printArray(int arr[], int n, int i){
    if(i>=n){
        return;
    }
    cout << arr[i]<< " ";
    printArray(arr, n, i+1);

}

int main(){
    
    int arr[5] = {10, 20, 30, 40 ,50};
    int n =5;
    int i = 0;
    printArray(arr, n, i);


    return 0;
}