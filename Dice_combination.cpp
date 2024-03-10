// Your task is to count the number of ways to construct sum n by throwing a dice one or more times. Each throw produces an outcome between 1 and  6.
// For example, if n=3, there are 4 ways:

// 1+1+1
// 1+2
// 2+1
// 3

// Input
// The only input line has an integer n.

// Output
// Print the number of ways modulo 10^9+7.

// Constraints
// 1 <= n <= 10^6

#include<iostream>
#include<vector>
using namespace std;

long long int dice_combination(int num){
    long long int count = 0;
    static vector<int> record;
    static int layer_c = 0;
    static int modulo = 1e9 + 7;
    if(layer_c == 0){
        record.assign(num+1,0);
    }
    if(record[num] != 0 ){
        return record[num];
    }
    for(int i=6;i>=1;i--){
        if(num-i < 0){
            continue;
        }else if(num-i == 0){
            count ++;
        }else{
            layer_c++;
            count += dice_combination(num-i);
            layer_c--;
        }
    }
    record[num] = count%modulo;
    return count%modulo;
}

int main(){
    int k;
    cin >> k;
    cout << dice_combination(k);

    return 0;
}