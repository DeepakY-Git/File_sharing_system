#include <iostream>
#include <climits>
#include <vector>
using namespace std;


bool checkKey(string& str, int i, int & n, char& key) {
    if (i >= n) {
        return false; // Base case.
    }
    
    if(str[i]==key){
        return true;
    }
    return checkKey(str, i+1, n, key); // Recursive call.
}


int main() {
    string str = "RaghavRajaram";
    int n = str.length();
    
    char key = 'r';
    
    int i = 0;
    bool ans = checkKey(str, i, n, key);
    
    cout<<"Answer is : "<<ans<<endl;

    return 0;
}
