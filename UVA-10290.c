//UVA 10290
#include<stdio.h>

//count
//整除奇數m, count++
//不整除偶數n: A, a=A/n(整除), A == n*a + sum(n) ? count++ : X
//n == 2 or n != 2
//sum(n) = 0+1+2+...+(n-1)

// ( num - sum(n) ) % digits of sum(n) == 0
// e.g. sum(n) = 1 + 2 -> 0+1+2 -> 3 digits
// -> num - (0+1+2) / 3 digits 餘0 -> 有解

//  設num = 33
//  num = 3*10 + 3
//  = 10 + 10 + 10 +
//     0 +  1 +  2
//  OR
//  num = 2+16 + 1
//  = 16 + 16 +
//     0 +  1

//  設num = 42
//  num = 4*9
//  = 9 + 9 + 9 + 9 +
//    0 + 1 + 2 + 3

void generate_prime(int store[],int num){
    static int i = 3;
    store[0] = 2;
    static int len = 1;
    for(i;i<=num;i++){
        for(int j=0;j<len;j++){
            if(i%store[j] == 0){
                break;
            }else if(j == len-1){
                store[len] = i;
                len++;
            }
        }
    }
}

void factoring(int count[],int factor[],int num){
    int index = 0;
    int i = factor[index];
    while(num != 1){
        while(num%i == 0){
            num /= i;
            count[index]++;
        }
        index++;
        i = factor[index];
    }
}

int main(){
    long long int input;
    while(scanf("%lld",&input) != EOF){
        int count = 1;
        long long int i = 1;
        long long int j = 2;
        while(input - i > 0){
            if((input - i)%j == 0){
                count++;
            }
            i += j;
            j++;
        }
        printf("%d\n",count);
    }
    
    return 0;
}