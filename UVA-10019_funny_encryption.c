#include<stdio.h>
#include<string.h>

int check_bit(int m){
    int one_count = 0;
    int total_bit = sizeof(int)*8;
    for(int i=0;i<total_bit;i++){
        if(m & (1u << i)){
            one_count++;
        }
    }
    return one_count;
}

int main(void)
{
    int total_times;
    scanf("%d",&total_times);
    for(int i=0;i<total_times;i++){
        char N[5];
        int deciM;
        int hexaM;
        scanf("%s",&N);
        sscanf(N,"%d",&deciM);
        sscanf(N,"%x",&hexaM);
        printf("%d %d\n",check_bit(deciM),check_bit(hexaM));
    }
    return 0;
}