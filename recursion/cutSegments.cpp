#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

int solve(int n, int x, int y, int z){
    // Base case
    if(n==0){
        return 0; // 0 Length rod can not have any segments
    }

    if(n<0){
        return INT_MIN; //If rod length is 0 than we can not cut it
    }
    // int a = 0;
    // if(n-x >= 0){
    //     a = solve(n-x, x, y, z) +1; // + 1 is of step with segment x
    // }

    // int b = 0;
    // if(n-y >= 0){
    //     b = solve(n-y, x, y, z) +1; // + 1 is of step with segment y
    // }

    // int c = 0;
    // if(n-z >= 0){
    //     c = solve(n-z, x, y, z) +1; // + 1 is of step with segment z
    // }
    int a = solve(n-x, x, y, z) + 1;
    int b = solve(n-y, x, y, z) + 1;
    int c = solve(n-z, x, y, z) + 1;

    

    int ans = max(a, max(b, c));
    return ans;
}

int main(){
    
    int n = 7;
    int x = 5;
    int y = 2;
    int z = 2;

    int ans = solve(n, x, y, z);

    if(ans < 0){
        ans =0;
    }

    cout << "Answer is : "<<ans<<endl;

    return 0;
}