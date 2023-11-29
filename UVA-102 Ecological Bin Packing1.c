#include<stdio.h>
#define nbin 3

int alpha_seq(int n){
    switch(n){
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 2;
    }
    return -1;
}

int main(){
    int bin[nbin][nbin];
    int sorted_bin[nbin] = {0};
    int max_bin[nbin] = {0};
    int k = 0;
    while(scanf("%d%d%d",&bin[k][0],&bin[k][1],&bin[k][2]) != EOF){
        k += 1;
        if(k == nbin){
            int sum = 0;
            for(int i=0;i<nbin;i++){
                for(int j=0;j<nbin;j++){
                    sum += bin[i][j];
                }
            }
            int max = 0;
            int diagnal = 0;
            for(int i=0;i<nbin;i++){
                sorted_bin[i] = 1;
                for(int j=0;j<nbin;j++){
                    if(j == i){
                        continue;
                    }
                    sorted_bin[j] = 2;
                    for(int s=0;s<nbin;s++){
                        if(s == i || s == j){
                            continue;
                        }
                        diagnal += bin[0][i];
                        diagnal += bin[1][j];
                        diagnal += bin[2][s];
                        sorted_bin[s] = 3;
                        if(diagnal > max){
                            max = diagnal;
                            for(int t=0;t<nbin;t++){
                                max_bin[t] = sorted_bin[t];
                            }
                        }else if(diagnal == max){
                            for(int t=0;t<nbin;t++){
                                if(alpha_seq(sorted_bin[t]) > alpha_seq(max_bin[t])){
                                    break;
                                }else if(alpha_seq(sorted_bin[t]) < alpha_seq(max_bin[t])){
                                    for(int n=0;n<nbin;n++){
                                        max_bin[n] = sorted_bin[n];
                                    }
                                    break;
                                }
                            }
                        }
                        diagnal = 0;
                    }
                }
            }
            for(int i=1;i<=nbin;i++){
                for(int j=0;j<nbin;j++){
                    if(max_bin[j] == i){
                        switch(j){
                            case 0:
                                printf("B");
                                break;
                            case 1:
                                printf("G");
                                break;
                            case 2:
                                printf("C");
                                break;
                        }
                    }
                }
            }
            printf(" %d\n",sum - max);
            k = 0;
        }
    }
    return 0;
}