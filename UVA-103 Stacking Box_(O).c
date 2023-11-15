#include<stdio.h>

void ordering(int boxseq[][10],int nbox,int dibox){
    for(int i=0;i<nbox;i++){
        for(int j=0;j<dibox;j++){
            for(int k=j+1;k<dibox;k++){
                if(boxseq[i][j] > boxseq[i][k]){
                    int temp = boxseq[i][j];
                    boxseq[i][j] = boxseq[i][k];
                    boxseq[i][k] = temp;
                }
            }
        }
    }
}

int fitting_test_recur(int boxseq[][10],int boxfit[],int nbox,int dibox,int curbox[],int start,int* maxcount){
    static int count = 2;
    int maxstr = 1;
    int curstr = 0;
    int findfitbox = 0;
    for(int i=0;i<nbox;i++){
        for(int j=0;j<dibox;j++){
            if(boxseq[start][j] >= boxseq[i][j]){
                break;
            }else if(j == dibox - 1){
                findfitbox = 1;
                count++;
                curbox[count-1] = i+1;
                curstr = fitting_test_recur(boxseq,boxfit,nbox,dibox,curbox,i,maxcount);
                if(curstr > maxstr){
                    maxstr = curstr;
                }
                curbox[count-1] = 0;
                count--;
            }
        }
    }
    if(findfitbox == 0){
        if(count > *maxcount){
            for(int i=0;i<nbox;i++){
                boxfit[i] = curbox[i];
                *maxcount = count;
            }
        }
        curbox[count-1] = 0;
        return count;
    }
    return maxstr;
}

int fitting_test_base(int boxseq[][10],int boxfit[],int nbox,int dibox){
    int maxstr = 1;
    int curstr = 0;
    int curbox[30] = {0};
    for(int i=0;i<nbox;i++){
        for(int t=0;t<nbox;t++){
            for(int j=0;j<dibox;j++){
                if(boxseq[i][j] >= boxseq[t][j]){
                    break;
                }else if(j == dibox-1){
                    curbox[0] = i+1;
                    curbox[1] = t+1;
                    curstr = fitting_test_recur(boxseq,boxfit,nbox,dibox,curbox,t,&maxstr);
                    maxstr = curstr > maxstr ? curstr : maxstr;
                }
            }
        }
        for(int j=0;j<nbox;j++){
            curbox[j] = 0;
        }
    }
    if(maxstr == 1){
        boxfit[0] = 1;
        return 1;
    }
    return maxstr;
}

int main(){
    int nbox;
    int dibox;
    while(scanf("%d%d",&nbox,&dibox) != EOF){
        int box_seq[30][10] = {0};
        int box_fit[30] = {0};
        for(int i=0;i<nbox;i++){
            for(int j=0;j<dibox;j++){
                scanf("%d",&box_seq[i][j]);
            }
        }
        ordering(box_seq,nbox,dibox);
        int maxstring = fitting_test_base(box_seq,box_fit,nbox,dibox);
        printf("%d\n",maxstring);
        if(maxstring == 1){
            printf("%d",box_fit[0]);
            printf("\n");
        }else{
            printf("%d",box_fit[0]);
            for(int i=1;i<nbox;i++){
                if(box_fit[i] != 0){
                    printf(" %d",box_fit[i]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}