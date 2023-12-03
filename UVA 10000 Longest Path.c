#include<stdio.h>

struct numPair{
    int x;
    int y;
};

struct numPair longest_path(int node[][100],int nodeNum,int start){
    static int count = 0;
    struct numPair longest_record;
    longest_record.x = 0;
    longest_record.y = 0;
    struct numPair result;
    result.x = count;
    result.y = start;
    for(int i=0;i<nodeNum;i++){
        if(node[start][i] == 0){
            return result;
        }
        count++;
        longest_record = longest_path(node,nodeNum,node[start][i]);
        if(longest_record.x == result.x){
            result = longest_record.y > result.y ? result : longest_record;
        }else if(longest_record.x > result.x){
            result = longest_record;
        }
        count--;
    }
    return result;
}

int main(){
    int nodeNum;
    int caseCount = 0;
    while(scanf("%d",&nodeNum)){
        if(nodeNum == 0){
            break;
        }
        caseCount++;
        int node[101][100];
        for(int i=0;i<=nodeNum;i++){
            for(int j=0;j<100;j++){
                node[i][j] = 0;
            }
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
        printf("Case %d: The longest path from %d has length %d, finishing at %d.\n",caseCount,start,answer.x,answer.y);
    }
    return 0;
}
