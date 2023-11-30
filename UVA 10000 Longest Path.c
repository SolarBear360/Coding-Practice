#include<stdio.h>

struct numPair{
    int x;
    int y;
};

struct numPair longest_path(int node[][100],int nodeNum,int start){
    static int count = 0;
    struct numPair longest_record;
    struct numPair max_record;
    longest_record.x = 0;
    longest_record.y = 0;
    max_record.x = 0;
    max_record.y = 0;
    int isterminal = 1;
    for(int i=0;i<nodeNum;i++){
        if(node[start][i] == 0 && isterminal){
            struct numPair result;
            result.x = count;
            result.y = start;
            return result;
        }else if(node[start][i] ==0 && !isterminal){

        }
        isterminal = 0;
        count++;
        longest_record = longest_path(node,nodeNum,node[start][i]);
        count--;
        printf("%d %d\n",longest_record.x,longest_record.y);
    }

int main(){
    int nodeNum;
    while(scanf("%d",&nodeNum) != EOF){
        int node[101][100];
        for(int i=0;i<nodeNum;i++){
            for(int j=0;j<nodeNum;j++){
                node[i][j] = 0;
            }
        }
        if(nodeNum == 0){
            break;
        }
        int start;
        scanf("%d",&start);
        int p,q;
        while(scanf("%d%d",&p,&q) != EOF){
            if(p == 0 || q == 0){
                break;
            }
            for(int i=0;i<nodeNum;i++){
                if(node[p][i] != 0){
                    continue;
                }
                node[p][i] = q;
                break;
            }
        }
        struct numPair answer = longest_path(node,nodeNum,start);
        // printf("%d %d\n",answer.x,answer.y);
    }
    return 0;
}
