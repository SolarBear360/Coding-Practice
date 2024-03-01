//uva 11234
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

struct NODE{
    char value;
    struct NODE* next;
    struct NODE* last;
};

char push(struct NODE** node,char val){
    if((*node)->value == '\0'){
        (*node)->value = val;
    }else{
        struct NODE* np = ( struct NODE* )malloc(sizeof(struct NODE));
        np->value = val;
        np->next = NULL;
        np->last = *node;
        (*node)->next = np;
        *node = (*node)->next;
    }
    return val;
}

char pop(struct NODE** node){
    char result;
    if((*node)->last == NULL){
        result = (*node)->value;
        (*node)->value = '\0';
    }else{
        result = (*node)->value;
        *node = (*node)->last;
        free((*node)->next);
        (*node)->next = NULL;
    }
    return result;
}

struct NODE* parsing_tree(struct NODE** stack,struct NODE** tree){
    char k = pop(stack);
    (*tree)->value = k;
    (*tree)->last = (struct NODE*)malloc(sizeof(struct NODE));
    (*tree)->next = (struct NODE*)malloc(sizeof(struct NODE));
    if(isupper(k)){
        (*tree)->last = parsing_tree(stack,&(*tree)->last);
        (*tree)->next = parsing_tree(stack,&(*tree)->next);
        return (*tree);
    }else{
        (*tree)->last = NULL;
        (*tree)->next = NULL;
        return (*tree);
    }
}

int tree_to_equation(struct NODE** ans_stack,struct NODE** parseTree,int depth){
    static int idep = 0;
    int a = 0;
    int b = 0;
    if(idep == depth){
        push(ans_stack,(*parseTree)->value);
        return 1;
    }else if(idep < depth){
        if((*parseTree)->next != NULL){
            idep++;
            a = tree_to_equation(ans_stack,&(*parseTree)->next,depth);
            idep--;
        }else{
            a = 0;
        }
        if((*parseTree)->last != NULL){
            idep++;
            b = tree_to_equation(ans_stack,&(*parseTree)->last,depth);
            idep--;
        }else{
            b = 0;
        }
    }
    return a || b;
}

void tree_to_free(struct NODE* tree){
    if(tree->last != NULL){
        tree_to_free(tree->last);
    }
    if(tree->next != NULL){
        tree_to_free(tree->next);
    }
    free(tree);
}


int main(){
    int T;
    scanf("%d",&T);
    for(int temp_count=0;temp_count<T;temp_count++){
        char record[200];
        int recordLen = 0;
        char tempk;
        scanf(" %c",&tempk);
        while(tempk != '\n'){
            record[recordLen] = tempk;
            recordLen++;
            scanf("%c",&tempk);
        }
        record[recordLen] = '\0';

        struct NODE* stored = ( struct NODE* )malloc(sizeof(struct NODE));
        stored->last = NULL;
        stored->value = '\0';
        for(int i=0;i<recordLen;i++){
            char k = push(&stored,record[i]);
        }

        struct NODE* tree = (struct NODE*)malloc(sizeof(struct NODE));
        parsing_tree(&stored,&tree);

        struct NODE* ans_stack = (struct NODE*)malloc(sizeof(struct NODE));
        ans_stack->last = NULL;
        ans_stack->value = '\0';

        int i = 0;
        int k;
        do{
            k = tree_to_equation(&ans_stack,&tree,i);
            i++;
        }while(k != 0);
        
        while(ans_stack->value != '\0'){
            char get = pop(&ans_stack);
            printf("%c",get);
        }

        tree_to_free(tree);
        free(ans_stack);
        free(stored);
    }

    return 0;
}

// struct QUEUE{
//     struct NODE* head;
//     struct NODE* tail;
// };

// void climb_tree(struct NODE* tree){
//     printf("%c",tree->value);
//     if(tree->last != NULL){
//         climb_tree(tree->last);
//     }
//     if(tree->next != NULL){
//         climb_tree(tree->next);
//     }
// }

// char enqueue(struct QUEUE* queue,char val){
//     if((*queue).head->value == '\0'){
//         (*queue).head->value = val;
//     }else{
//         struct NODE* np = ( struct NODE* )malloc(sizeof(struct NODE));
//         np->value = val;
//         np->next = NULL;
//         np->last = (*queue).head;
//         (*queue).head->next = np;
//         (*queue).head = (*queue).head->next;
//     }
//     return val;
// }

// char dequeue(struct QUEUE* queue){
//     char result;
//     if((*queue).head == (*queue).tail){
//         result = (*queue).head->value;
//         (*queue).head->value = '\0';
//     }else{
//         result = (*queue).tail->value;
//         (*queue).tail = (*queue).tail->next;
//         free((*queue).tail->last);
//         (*queue).tail->last = NULL;
//     }
//     return result;
// }
