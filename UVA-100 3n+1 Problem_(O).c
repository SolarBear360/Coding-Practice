#include<stdio.h>

int main(){
    int i,j;
    while(scanf("%d%d",&i,&j) != EOF){
        int max_cycle = 0;
        int begin = i > j ? j : i;
        int end = i > j ? i : j;
        for(int k=begin;k<=end;k++){
            int current = k;
            int count = 0;
            while(current!=1){
                if(current%2 == 1){
                    current = current*3+1;
                }else{
                    current/=2;
                }
                count += 1;
            }
            count += 1;
            if(count > max_cycle){
                max_cycle = count;
            }
        }
        printf("%d %d %d\n",i,j,max_cycle);
    }
    return 0;
}