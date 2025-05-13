/*
********************************
*       TensorPhobia (C)       *
*       ISI ARIANA 2025        *
* MAIL: tensorphobia@gmail.com *
********************************
*/

/*
   Opération       |  Coût   |                        Description (FR)
-------------------+---------+------------------------------------------------------------
  pushfront   °    |  O(1)   | Insère un nœud au début de la liste
-------------------+---------+------------------------------------------------------------
  pushback    °    |  O(1)   | Insère un nœud à la fin de la liste
-------------------+---------+------------------------------------------------------------
  insert      °    |  O(N)   | Insère un nœud à un index spécifique
-------------------+---------+------------------------------------------------------------
  popfront    °    |  O(1)   | Supprime et retourne le premier nœud
-------------------+---------+------------------------------------------------------------
  popback     °    |  O(N)   | Supprime et retourne le dernier nœud
-------------------+---------+------------------------------------------------------------
  pop         °    |  O(N)   | Supprime et retourne un nœud à un index donné
-------------------+---------+------------------------------------------------------------
  peekfront   °    |  O(1)   | Retourne la valeur du premier nœud
-------------------+---------+------------------------------------------------------------
  peekback    °    |  O(1)   | Retourne la valeur du dernier nœud
-------------------+---------+------------------------------------------------------------
  peek        °    |  O(N)   | Retourne la valeur à un index donné
-------------------+---------+------------------------------------------------------------
  print       °    |  O(N)   | Affiche la liste de la tête à la queue
-------------------+---------+------------------------------------------------------------
  printInverted °  |  O(N)   | Affiche la liste en sens inverse (récursif)
-------------------+---------+------------------------------------------------------------
  len         °    |  O(1)   | Retourne la taille de la liste
-------------------+---------+------------------------------------------------------------
  inverse     °    |  O(N)   | Inverse la direction de la liste
-------------------+---------+------------------------------------------------------------
  sort        °    |  O(N²)  | Trie la liste avec un tri à bulles
-------------------+---------+------------------------------------------------------------
  copy        °    |  O(N)   | Crée une copie profonde de la liste
-------------------+---------+------------------------------------------------------------
  constructeur °   |  O(N)   | Construit une liste de taille donnée
-------------------+---------+------------------------------------------------------------
  deconstruct      |  O(N)   | Libère tous les nœuds (non implémenté explicitement ici)
-------------------+---------+------------------------------------------------------------
  search      °    |  O(N)   | Cherche une valeur et retourne son index
-------------------+---------+------------------------------------------------------------
  slice            |  O(N)   | Coupe la liste en deux à un index donné
-------------------+---------+------------------------------------------------------------
  appendBack       |  O(1)   | Ajoute une autre liste à la fin
-------------------+---------+------------------------------------------------------------
  appendFront      |  O(1)   | Ajoute une autre liste au début
-------------------+---------+------------------------------------------------------------
  append           |  O(N)   | Insère une autre liste à un index donné
-------------------+---------+------------------------------------------------------------
  setfront    °    |  O(1)   | Modifie la valeur du premier nœud
-------------------+---------+------------------------------------------------------------
  setback     °    |  O(1)   | Modifie la valeur du dernier nœud
-------------------+---------+------------------------------------------------------------
  set         °    |  O(N)   | Modifie la valeur à un index donné
-------------------+---------+------------------------------------------------------------
  init        °    |  O(N)   | Initialise les valeurs de la liste (lecture utilisateur)
-------------------+---------+------------------------------------------------------------
*/



#include <assert.h>
#include <stddef.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node_t node_t;
#define SEARCH_NOT_FOUND 4294967295



struct node_t{
    int val;
    node_t *nxt;
};

node_t * node_constructor(){
    return malloc(sizeof(node_t));
};

void node_init(node_t * node , int val){
    node->val = val;
};

void node_concat(node_t * node1 , node_t * node2){
    node1->nxt = node2;
};

void node_swap_values(node_t * node1 , node_t * node2){
    int tmp = node1->val;
    node1->val = node2->val;
    node2->val =  tmp;
};

bool node_cmp_ASC(node_t* node1 , node_t* node2){
    return node1->val > node2->val;
}

bool node_cmp_DEC(node_t* node1 , node_t* node2){
    return node1->val < node2->val;
}

typedef struct{
    unsigned len;
    node_t *head,*tail;
} linkedList;

linkedList linkedList_constructor(int n){
    linkedList l = {0,NULL,NULL};
    if(n < 1){
        return l;
    }else if (n == 1) {
        l.head = l.tail = node_constructor();
        l.len = n;
        return l;
    }
    l.head = node_constructor();
    node_t *cur , *prc;
    prc = l.head;
    for (int i = 1; i < n; i++) {
        cur = node_constructor();
        prc->nxt = cur;
        prc = cur;
    }
    l.tail = cur;
    l.tail->nxt = NULL;
    l.len = n;
    return l;
};

void linkedList_init(linkedList l){
    node_t * cur = l.head;
    for (int i = 0; i < l.len; i++) {
        int x;
        puts("scan list node :");
        scanf("%d",&x);
        node_init(cur, x);
        cur = cur->nxt;
    }
};

void linkedList_print(linkedList l){
    node_t * cur = l.head;
    for (int i = 0; i < l.len; i++) {
        printf("%d -> ",cur->val);
        cur = cur->nxt;
    }
    puts("");
}

linkedList linkedList_copy(linkedList l1){
    linkedList l2 = linkedList_constructor(l1.len);
    node_t *cur_l1,*cur_l2;
    cur_l1 = l1.head;
    cur_l2 = l2.head;
    do{
        cur_l2->val = cur_l1->val;
        cur_l1 = cur_l1->nxt;
        cur_l2 = cur_l2->nxt;
    }while(cur_l1->nxt != NULL);
    cur_l2->val = cur_l1->val;
    return l2;
    
}

void linkedList_slice(linkedList *l, int split_at , linkedList * l1 , linkedList * l2){
    assert(split_at < l->len);
    //L1 includes split index
    l1->len = split_at + 1;
    l2->len = l->len - l1->len;
    // set L1
    l1->head = l->head;
    node_t* l1_cur = l1->head;
    /*
    1 -> 2 -> 3 -> 4
    0    1    2    3       
    
    */
    for (int i = 0; i < l1->len-1; i++) {
        l1_cur = l1_cur->nxt;
    }
    l1->tail = l1_cur;
    
    // set L2
    l2->head = l1_cur->nxt;
    
    l2->tail = l1->tail;
    // cut linkage of L1 tail
    l1->tail->nxt = NULL;
    // clean up L
    l->len = 0;
    l->head = l->tail = NULL;
    
}

node_t * pop_front(linkedList *l){
    if(l->len < 1) return NULL;
    if(l->len == 1){
        node_t * front = l->head;
        l->head = l->tail = NULL;
        l->len = 0;
        return  front; 
    }
    node_t * front = l->head;
    l->head = l->head->nxt;
    l->len-=1;
    return front;
}

node_t * pop_back(linkedList *l){
    if(l->len < 1) return NULL;
    if(l->len == 1){
        node_t * front = l->head;
        l->head = l->tail = NULL;
        l->len = 0;
        return  front; 
    }
    node_t * back = l->head;
    // note that we are garantied lenght > 1 (min 2) that mean we can explore x + 2 nodes
    /*while(back->nxt->nxt != NULL){
        back = back->nxt;
    }*/

    for (int i = 0; i < l->len - 2; i++) {
        back = back->nxt;
    }

    node_t *tmp =back->nxt;
    back->nxt = NULL;
    l->len -=1;
    return tmp;
}

void linkedList_concatinate(linkedList *l1 , linkedList *l2){
    l1->len += l2->len;
    l1->tail->nxt =  l2->head;
    l1->tail = l2->tail;

    l2->len= 0;
    l2->head = l2->tail = NULL;
}

node_t *linkedList_pop(linkedList *l,unsigned index){
    assert(index < l->len);
    if(index == 0){
        return pop_front(l);
    }
    if(index == l->len -1){
        return pop_back(l);
    }
    linkedList l1 , l2;
    // -1 because index is included
    linkedList_slice(l, index - 1, &l1, &l2);
    node_t *res = pop_front(&l2);
    printf("poped node :%d\n",res->val);
    linkedList_concatinate(&l1, &l2);
    *l = l1;
    return res;
}

void linkedList_inverse(linkedList *l){
    if(l->len > 1){
        // we granted presence of 2 elements
        node_t* prv = l->head;
        node_t* cur = prv->nxt;
        node_t* nxt = cur->nxt;
        node_t* tmp = prv;
        // reverse pointers
        while(nxt != NULL){ // for _ in 0 to len
            cur->nxt = prv;
            prv = cur;
            cur = nxt;
            nxt = nxt->nxt;
        }
        cur->nxt = prv;
        l->head = cur;
        tmp->nxt = NULL;
        l->tail = tmp;
    }
}

void linkedList_bubbleSort(linkedList *l,bool cmp(node_t *,node_t *)){
    if(l->len < 2) return;
    unsigned end = l->len;
    bool isNSorted;
    do {
        isNSorted = false;
        node_t *prv,*cur;
        prv = l->head;
        cur = l->head->nxt;
        while(cur != NULL){
            if(cmp(prv,cur)){
                node_swap_values(prv, cur);
                isNSorted = true;
            }
            prv = prv->nxt;
            cur = cur->nxt;
        }
        
    }while (isNSorted);
}

unsigned linkedList_search(linkedList l , int element){
    node_t *cur = l.head;
    for (int i = 0; i < l.len; i++) {
        if(cur->val == element){
            return i;
        }
        cur = cur->nxt;
    }
    return SEARCH_NOT_FOUND;
}

node_t *linkedList_front(linkedList l){
    return l.head;
}

node_t *linkedList_back(linkedList l){
    return l.tail;
}

node_t *linkedList_read(linkedList l , unsigned index){
    assert(index < l.len);
    if(index == 0) return linkedList_front(l);
    if(index == l.len -1) return linkedList_back(l);
    node_t *cur = l.head;
    for (int i = 0; i < index; i++) {
        cur = cur->nxt;
    }
    return cur;
}


void linkedList_pushfront(linkedList *l , node_t *node){
    node->nxt = l->head;
    l->len+=1;
    l->head = node;
}

void linkedList_pushback(linkedList *l , node_t *node){
    node->nxt = NULL;
    l->len+=1;
    l->tail->nxt = node;
}

void linkedList_insert(linkedList *l , node_t *node , unsigned index){
    assert(index < l->len);
    if(index == 0){
     linkedList_pushfront(l, node);
    }else if(index == l->len - 1){ 
        linkedList_pushback(l, node);
    }else{
        node_t *cur = l->head;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->nxt;
        }
        node->nxt = cur->nxt;
        cur->nxt = node;
        l->len +=1;
    }
}

void linkedList_append(linkedList *l1,linkedList l2){
    if(l2.len < 1) return;
    linkedList l3 = linkedList_copy(l2);
    linkedList_concatinate(l1, &l3);
}

void linkedList_print_inverted_helper(node_t* node){
    if(node != NULL){
        linkedList_print_inverted_helper(node->nxt);
        printf("<- %d ",node->val);
    }
}

void linkedList_print_inverted(linkedList l){
    linkedList_print_inverted_helper(l.head);
    puts("");
}

