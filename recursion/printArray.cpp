#include<iostream> 
#include<vector>
using namespace std;

void printArray(vector<int>nums){
    if(nums.size()==0){
        return;
    }
    cout << nums[nums.size()-1] << " ";
    nums.pop_back();
    printArray(nums);

}

int main(){
    vector<int> nums({1,2,3,45,6,7});
    

    printArray(nums);
    
}