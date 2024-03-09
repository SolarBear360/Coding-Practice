#include<iostream>
#include<vector>
using namespace std;

string longestPalindrome(string s) {
    int ispalin = 0;
    int len = s.length();
    static vector<string> str_record;
    static int layer_c = 0;
    if(len == 1){
        return s;
    }
    int record_index = 0;
    while(record_index < str_record.size()){
        if(s == str_record[record_index]){
            return "";
        }
        record_index++;
    }
    for(int i=0;i<len/2;i++){
        char a = s[i];
        char b = s[len-1-i];
        if(a != b){
            break;
        }else if(i == len/2-1){
            ispalin = 1;
        }
    }
    str_record.push_back(s);
    if(ispalin == 1){
        return s;
    }else{
        layer_c++;
        string a = longestPalindrome(s.substr(0,len-1));
        layer_c--;
        layer_c++;
        string b = longestPalindrome(s.substr(1,len-1));
        layer_c--;
        if(layer_c == 0){
            str_record.clear();
            // cout << "clear\n";
        }
        if(a.length() >= b.length()){
            return a;
        }else{
            return b;
        }
    }
}

int main(){
    string k;
    while(cin >> k){
        cout << longestPalindrome(k) << "\n";
    }

    return 0;
}