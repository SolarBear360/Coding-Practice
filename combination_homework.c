#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int find_index(int num[],int n,int value){
    for(int i=0;i<n;i++){
        if(num[i] = value){
            return i;
        }
    }
    return -1;
}

int seq_detect(int num[],int record[],int even_point,int value,int n){
    if(value%2==0){
        for(int i=0;i<even_point;i++){
            if(find_index(num,n,record[i]) > find_index(num,n,value)){
                break;
            }else if(i == even_point-1){
                return 0;
            }
        }
        return 1;
    }else{
        for(int i=even_point;i<=even_point;i++){
            if(find_index(num,n,record[i]) > find_index(num,n,value)){
                break;
            }else if(i == even_point-1){
                return 0;
            }
        }
        return 1;
    }
}

void n_combination(int num[],int record[],int mark[],int m,int n,int even_count){
    static int c = 0;
    if(c>=n){
        printf("%d",record[0]);
        for(int i=1;i<n;i++){
            printf(",%d",record[i]);
        }
        printf("\n");
        return;
    }else if(c >= even_count){
        for(int i=0;i<m;i++){
            if(num[i]%2==1 && mark[i] != 1 && !seq_detect(num,record,even_count,num[i],n)){
                record[c] = num[i];
                mark[i] = 1;
                c++;
                n_combination(num,record,mark,m,n,even_count);
                mark[i] = 0;
                c--;
            }
        }
    }else{
        for(int i=0;i<m;i++){
            if(num[i]%2==0 && mark[i] != 1 && !seq_detect(num,record,even_count,num[i],n)){
                record[c] = num[i];
                mark[i] = 1;
                c++;
                n_combination(num,record,mark,m,n,even_count);
                mark[i] = 0;
                c--;
            }
        }
    }
}

int main()
{
    int m,n;
    while(scanf("%d%d",&m,&n) != EOF){
        int even_count = n/2+n%2;
        int num[10];
        int record[10] = {0};
        int mark[10] = {0};
        for(int i=0;i<m;i++){
            scanf("%d",&num[i]);
        }
        while(even_count <= n){
            n_combination(num,record,mark,m,n,even_count);
            even_count++;
        }
    }
   return 0;
} 