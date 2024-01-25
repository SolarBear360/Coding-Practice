#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    int frequency;
    struct node* l_node;
    struct node* r_node;
};

struct num_pair{
    int x;
    int y;
};

struct num_pair find_smallest(struct num_pair a,struct num_pair b){
    int check_a;
    int check_b;
    int sum_a = a.x + a.y;
    int sum_b = b.x + b.y;
    if(a.x < 0 || a.y < 0){
        check_a = 0;
    }else{
        check_a = 1;
    }
    if(b.x < 0 || b.y < 0){
        check_b = 0;
    }else{
        check_b = 1;
    }
    if(!check_a){
        return b;
    }
    else if(!check_b){
        return a;
    }
    return sum_a < sum_b ? a : b;
}

void insertion_sort(int arr[],int len){
    for(int i=0;i<len;i++){
        int hold = arr[i];
        int j;
        for(j=i;j>0;j--){
            if(hold < arr[j-1]){
                arr[j] = arr[j-1];
            }else{
                break;
            }
        }
        arr[j] = hold;
    }
}

int huffman_tree(struct node* treenode,int curlen){
    //1.建立一個母節點
    //2.將頻率最小的兩個子節點透過母節點連接，母節點頻率為兩子節點相加
    //3.新的nodearr為除去兩子節點再加上一母節點
    //4.遞迴直到終止條件
    static int LENGTH = 0;
    static int add_node = 0; //加在後面的
    static int used_node = 0;//後面已使用的
    if(curlen == 0){    //terminal
        while(LENGTH+add_node < 2*LENGTH-1){
            treenode[add_node].l_node = treenode+used_node;
            treenode[add_node].r_node = treenode+used_node+1;
            treenode[add_node].frequency = (treenode[add_node].l_node)->frequency + (treenode[add_node].r_node)->frequency;
            add_node++;
            used_node+=2;
        }
        add_node = 0;
        used_node = 0;
        return (2*LENGTH-2);
    }
    if(add_node == 0){  //beginning
        LENGTH = curlen;
        treenode[LENGTH].l_node = treenode;
        treenode[LENGTH].r_node = treenode+1;
        treenode[LENGTH].frequency = (treenode[LENGTH].l_node)->frequency + (treenode[LENGTH].r_node)->frequency;
        treenode[LENGTH].value = -1;
        add_node++;
        return huffman_tree(treenode+2,curlen-2);
    }
    else{
        // int two_leaf_fre = -1;
        // if(curlen > 1){
        //     two_leaf_fre = treenode[0].frequency + treenode[1].frequency;
        // }
        // int one_leaf_fre = treenode[0].frequency + treenode[curlen+used_node].frequency;
        // int two_node_fre = treenode[curlen+used_node].frequency + treenode[curlen+used_node+1].frequency;
        // int smallest = find_smallest(find_smallest(two_leaf_fre,one_leaf_fre),two_node_fre);
        struct num_pair two_leaf;
        struct num_pair one_leaf;
        struct num_pair two_node;
        two_leaf.x = treenode[0].frequency;
        if(curlen > 1){
            two_leaf.y = treenode[1].frequency;
        }else{
            two_leaf.y = -1;
        }
        one_leaf.x = treenode[0].frequency;
        one_leaf.y = treenode[curlen+used_node].frequency;
        two_node.x = treenode[curlen+used_node].frequency;
        two_node.y = treenode[curlen+used_node+1].frequency;
        struct num_pair small_pair = find_smallest(find_smallest(two_leaf,one_leaf),two_node);
        int small = small_pair.x + small_pair.y;
        int two_leaf_fre = two_leaf.x + two_leaf.y;
        int one_leaf_fre = one_leaf.x + one_leaf.y;
        int two_node_fre = two_node.x + two_node.y;
        if(small == two_leaf_fre){       //two_leaf_fre >= one_leaf_fre
            treenode[curlen+add_node].l_node = treenode;
            treenode[curlen+add_node].r_node = treenode+1;
            treenode[curlen+add_node].frequency = two_leaf_fre;
            treenode[curlen+add_node].value = -1;
            add_node++;
            return huffman_tree(treenode+2,curlen-2);
        }else if(small == one_leaf_fre){ //
            treenode[curlen+add_node].l_node = treenode;
            treenode[curlen+add_node].r_node = treenode+curlen+used_node;
            treenode[curlen+add_node].frequency = one_leaf_fre;
            treenode[curlen+add_node].value = -1;
            add_node++;
            used_node++;
            return huffman_tree(treenode+1,curlen-1);
        }else{                           //
            treenode[curlen+add_node].l_node = treenode+curlen+used_node;
            treenode[curlen+add_node].r_node = treenode+curlen+used_node+1;
            treenode[curlen+add_node].frequency = two_node_fre;
            treenode[curlen+add_node].value = -1;
            add_node++;
            used_node+=2;
            return huffman_tree(treenode,curlen);
        }
    }
}

struct node* get_tree(int frequenArr[],int numArr[],int len){
    //產生葉節點
    struct node* treenode = (struct node* )malloc(len*2*sizeof(struct node));
    for(int i=0;i<len*2;i++){
        if(i<len){
            treenode[i].value = numArr[i];
            treenode[i].frequency = frequenArr[i];
        }else{
            treenode[i].frequency = -1;
        }
        treenode[i].l_node = NULL;
        treenode[i].r_node = NULL;
    }
    int root = huffman_tree(treenode,len);
    for(int i=0;i<2*len;i++){
        printf("node:%d fre:%d\n",i,treenode[i].frequency);
        if(treenode[i].l_node != NULL){
            printf("LNODE\n");
        }else{
            printf("LNULL\n");
        }
        if(treenode[i].r_node != NULL){
            printf("RNODE\n");
        }else{
            printf("RNULL\n");
        }
    }
    printf("root:%d\n",root);
    return treenode+root;
}

void climb_tree(struct node* pointer){
    if(pointer == NULL){
        return;
    }
    printf("fre:%d\n",pointer->frequency);
    if(pointer->l_node == NULL && pointer->r_node == NULL){
        printf("value:%d\n",pointer->value);
    }
    climb_tree(pointer->l_node);
    climb_tree(pointer->r_node);
}

int main(){
    int n = 22;
    int counter[22] = {5,3,4,2,8,9,7,1,8,3,4,11,6,22,10,9,6,1,1,2,14,8};
    // while(scanf("%d",&n) != EOF){
    //     if(n<10){
    //         counter[n]++;
    //     }
    // }

    int num[22];
    for(int i=0;i<22;i++){
        num[i] = i;
    }

    for(int i=0;i<n;i++){
        int hold = num[i];
        int j;
        for(j=i;j>0;j--){
            if(counter[hold] < counter[num[j-1]]){
                num[j] = num[j-1];
            }else{
                break;
            }
        }
        num[j] = hold;
    }
    insertion_sort(counter,n);
    // for(int i=0;i<22;i++){
    //     printf("%2d ",num[i]);
    // }
    // printf("\n");
    // for(int i=0;i<22;i++){
    //     printf("%2d ",counter[i]);
    // }
    // printf("\n");
    struct node* root = get_tree(counter,num,n);
    climb_tree(root);

    free(root);
    return 0;
}