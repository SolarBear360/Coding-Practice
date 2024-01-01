#include<stdio.h>

int digits(int arr[],int num,int len){
    int i = 0;
    while(num > 0 && i<len){
        arr[i] = num%10;
        num/=10;
        i++;
    }
    return i;
}

int reverse_digit(int num){
    int result = 0;
    int arr[20] = {0};
    int len = 0;
    len = digits(arr,num,20);
    for(int i=len-1,base=1;i>=0;i--){
        result += arr[i]*base;
        base*=10;
    }
    return result;
}

int main(void)
{
    int N;
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        int count = 0;
        int num;
        scanf("%d",&num);
        int reverse = reverse_digit(num);
        while(reverse != num){
            count++;
            num = num + reverse;
            reverse = reverse_digit(num);
        }
        printf("%d %d\n",count,num);
    }
    return 0;
}