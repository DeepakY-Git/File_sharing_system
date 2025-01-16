#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

void printSubsequences(string str, string output, int i, vector<string>& v){
    //  Base Case
    if(i >= str.length()){
        // cout << output<<endl;
        v.push_back(output);
        return;

    }
    // exclude
    printSubsequences(str, output, i+1, v);

    // include
    output.push_back(str[i]);
    printSubsequences(str, output, i+1, v);
}

int main(){
    string str = "abc";

    string output = "";
    vector<string> v;
    int i = 0;

    printSubsequences(str, output, i, v);
    for(i = 0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    cout << " Total Number Of Subsequences are : "<<v.size()<<endl;

    return 0;
}