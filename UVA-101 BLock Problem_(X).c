#include<stdio.h>
#include<string.h>

void return_block(int block[],int posi[],int stak[],int block_num,int a,int n){
    for(int i=0;i<block_num;i++){
        if(posi[i] == posi[a] && stak[i] > stak[a]){
            block[i*n] = i;
            block[posi[i]*n + stak[i]] = -1;
            posi[i] = i;
            stak[i] = 0;
        }
    }
}

int main(){
    int block_num;
    while(scanf("%d",&block_num) != EOF){
        int block[25][25];
        int posi[25];
        int stak[25] = {0};
        for(int i=0;i<25;i++){
            posi[i] = -1;
            stak[i] = -1;
            for(int j=0;j<25;j++){
                block[i][j] = -1;
            }
        }
        for(int i=0;i<block_num;i++){
            block[i][0] = i;
            posi[i] = i;
            stak[i] = 0;
        }
        char act1[4];
        char act2[4];
        int a;
        int b;
        while(scanf("%s",&act1) != EOF){
            if(strcmp(act1,"quit") == 0){
                break;
            }else{
                scanf("%d%s%d",&a,&act2,&b);
            }
            if(posi[a] == posi[b] || a >= block_num || b >= block_num){
                continue;
            }
            if(strcmp(act1,"move") == 0 && strcmp(act2,"onto") == 0){
                // for(int i=0;i<block_num;i++){                           // return block on a or b
                //     if( (posi[i] == posi[a] && stak[i] > stak[a]) || (posi[i] == posi[b] && stak[i] > stak[b]) ){
                //         for(int j=0;j<block_num;j++){
                //             if(block[i][j] == -1){
                //                 block[i][j] = block[posi[i]][stak[i]];  // move block to another position
                //                 block[posi[i]][stak[i]] = -1;
                //                 posi[i] = i;                            // change the position and stack count of the block
                //                 stak[i] = j;
                //                 break;
                //             }
                //         }
                //     }
                // }
                return_block(block,posi,stak,block_num,a,25);
                return_block(block,posi,stak,block_num,b,25);
                block[posi[b]][stak[b]+1] = block[posi[a]][stak[a]];    // move a onto b
                block[posi[a]][stak[a]] = -1;
                posi[a] = posi[b];
                stak[a] = stak[b] + 1;                                  // change stak to top of b
            }else if(strcmp(act1,"move") == 0 && strcmp(act2,"over") == 0){
                // for(int i=0;i<block_num;i++){                           // return block on a
                //     if( posi[i] == posi[a] && stak[i] > stak[a] ){
                //         for(int j=0;j<block_num;j++){
                //             if(block[i][j] == -1){
                //                 block[i][j] = block[posi[i]][stak[i]];
                //                 block[posi[i]][stak[i]] = -1;
                //                 posi[i] = i;
                //                 stak[i] = j;
                //                 break;
                //             }
                //         }
                //     }
                // }
                return_block(block,posi,stak,block_num,a,25);
                for(int i=stak[b];i<block_num;i++){
                    if(block[posi[b]][i] == -1){                  // find empty stack on b
                        block[posi[b]][i] = block[posi[a]][stak[a]];
                        block[posi[a]][stak[a]] = -1;
                        posi[a] = posi[b];                              
                        stak[a] = i;
                        break;
                    }
                }
            }else if(strcmp(act1,"pile") == 0 && strcmp(act2,"onto") == 0){
                for(int i=0;i<block_num;i++){                           // return block on b
                    if( posi[i] == posi[b] && stak[i] > stak[b] ){
                        for(int j=0;j<block_num;j++){
                            if(block[i][j] == -1){
                                block[i][j] = block[posi[i]][stak[i]];
                                block[posi[i]][stak[i]] = -1;
                                posi[i] = i;
                                stak[i] = j;
                                break;
                            }
                        }
                    }
                }
                int a_pile = posi[a];
                for(int i=stak[a],j=1;i<block_num;i++,j++){
                    if(block[a_pile][i] == -1){                        // if find empty block
                        break;
                    }
                    else{
                        block[posi[b]][stak[b]+j] = block[a_pile][i];
                        posi[block[a_pile][i]] = posi[b];        // get current block position and change to b
                        stak[block[a_pile][i]] = stak[b]+j;      // get current block stack and change to top of b
                        block[a_pile][i] = -1;
                    }
                }
            }else if(strcmp(act1,"pile") == 0 && strcmp(act2,"over") == 0){
                int a_pile = posi[a];
                for(int i=stak[a],j=stak[b];i<block_num;){
                    if(block[a_pile][i] == -1){
                        break;
                    }
                    else{
                        if(block[posi[b]][j] == -1){
                            block[posi[b]][j] = block[a_pile][i];
                            posi[block[a_pile][i]] = posi[b];
                            stak[block[a_pile][i]] = j;
                            block[a_pile][i] = -1;
                            i++;
                        }
                        j++;
                    }
                }
            }
        }
        for(int i=0;i<block_num;i++){
            printf("%d:",i);
            for(int j=0;j<block_num;j++){
                if(block[i][j] != -1){
                    printf(" %d",block[i][j]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}