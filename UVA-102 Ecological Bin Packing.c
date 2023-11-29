#include<stdio.h>
#define nbin 3

int alpha_seq(int a){
    switch(a){
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 2;
        default:
            return -1;
    }
}

int main(){
    int bin[nbin][nbin];
    int bottle_sort[nbin] = {0};
    int min_sort[nbin] = {0};
    while(scanf("%d%d%d%d%d%d%d%d%d",
        &bin[0][0],&bin[0][1],&bin[0][2],
        &bin[1][0],&bin[1][1],&bin[1][2],
        &bin[2][0],&bin[2][1],&bin[2][2]) != EOF){
//----------------------------------------------------
        int max_dia = 0;
        int cur_dia = 0;
        int sum = 0;
        for(int i=0;i<nbin;i++){
            for(int j=0;j<nbin;j++){
                sum += bin[i][j];
            }
        }
        for(int i=0;i<nbin;i++){
            cur_dia += bin[0][i];
            cur_dia += bin[1][(i+1)%nbin];
            cur_dia += bin[2][(i+2)%nbin];
            bottle_sort[0] = i+1;
            bottle_sort[1] = (i+1)%nbin+1;
            bottle_sort[2] = (i+2)%nbin+1;
            if(cur_dia > max_dia){
                max_dia = cur_dia;
                for(int j=0;j<nbin;j++){
                    min_sort[j] = bottle_sort[j];
                }
            }else if(max_dia == cur_dia){
                for(int j=0;j<nbin;j++){
                    if( alpha_seq(min_sort[j]) > alpha_seq(bottle_sort[j]) ){
                        for(int k=0;k<nbin;k++){
                            min_sort[k] = bottle_sort[k];
                        }
                        break;
                    }else if( alpha_seq(min_sort[j]) < alpha_seq(bottle_sort[j]) ){
                        break;
                    }
                }
            }
            for(int j=0;j<nbin;j++){
                bottle_sort[j] = 0;
            }
            cur_dia = 0;
        }
        for(int i=0;i<nbin;i++){
            cur_dia += bin[0][i];
            cur_dia += bin[1][(i+2)%nbin];
            cur_dia += bin[2][(i+1)%nbin];
            bottle_sort[0] = i+1;
            bottle_sort[1] = (i+2)%nbin+1;
            bottle_sort[2] = (i+1)%nbin+1;
            if(cur_dia > max_dia){
                max_dia = cur_dia;
                for(int j=0;j<nbin;j++){
                    min_sort[j] = bottle_sort[j];
                }
            }else if(max_dia == cur_dia){
                for(int j=0;j<nbin;j++){
                    if( alpha_seq(min_sort[j]) > alpha_seq(bottle_sort[j]) ){
                        for(int k=0;k<nbin;k++){
                            min_sort[k] = bottle_sort[k];
                        }
                        break;
                    }else if( alpha_seq(min_sort[j]) < alpha_seq(bottle_sort[j]) ){
                        break;
                    }
                }
            }
            for(int j=0;j<nbin;j++){
                bottle_sort[j] = 0;
            }
            cur_dia = 0;
        }
        for(int i=0;i<nbin;i++){
            switch(min_sort[i]){
                case 1:
                    printf("B");
                    break;
                case 2:
                    printf("G");
                    break;
                case 3:
                    printf("C");
                    break;
            }
        }
        printf(" %d\n",sum - max_dia);
    }

    return 0;
}