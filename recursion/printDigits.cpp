#include <iostream>
#include <climits>
#include <vector>
using namespace std;

void printDigits(int n){
    if(n==0){
        return;
    }
    
    int newValueOfN = n/10;

    printDigits(newValueOfN);
    int digit = n % 10;
    cout << digit << " ";

}

int main() {
    int n;
    cin >> n;
    cout << "The value of n is : "<<n<<endl;

    printDigits(n);
    // vector<int> ans;

    // int i; 

    // while(n>0){
    //     i = n%10;
    //     ans.push_back(i);
    //     n = n/10;
    // }

    // for(i = 0; i<ans.size(); i++){
    //     cout <<ans[i]<<" ";
    // }
    // cout << endl;
    

    return 0;
}
