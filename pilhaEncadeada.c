#include "pilhaEncadeada.h"
#include <stdlib.h>
#include <strings.h>


int isEmpty(pilha *p){
    if(p->topo == NULL){
        return 1;
    }
    return 0;
}
elemPilha* cria_elemPilha(char remetenteApelido[], char mensagem[]){
    elemPilha *retval;

    retval = (elemPilha*)malloc(sizeof(elemPilha));
    if(retval == NULL){
        exit(1); //caso falte memoria, aborta
    }

    strcpy(retval->remetenteApelido,remetenteApelido); //inicializa os campos com os valores dados ou nulo
    strcpy(retval->mensagem,mensagem);
    retval->prox = NULL; //inicializa com nulo para poder acessar a memoria, mesmo caso vazia
    retval->isLida = 0; //marca a mensagem como nao lida

    return retval;
}

pilha* cria_pilha(int *erro){

    pilha *retval;

    retval = (pilha*)malloc(sizeof(pilha));
    if(retval == NULL){
        *erro = 1;
        exit(1); //se nao houver memoria, aborta
    }
    else{
        retval->topo = NULL; //inicializa com nulo para poder acessar a memoria, mesmo caso vazia
    }

    return retval;
}

void push(pilha *p, elemPilha *newE, int *erro){

        newE->prox = p->topo; //adiciona elemento no topo
        p->topo = newE;
}

elemPilha* pop(pilha *p, int *erro){
    elemPilha *step;

    if(p->topo != NULL){
        step = p->topo;
        p->topo = step->prox; //retorna o topo da pilha
    }
    else{
        *erro = 1;
        step = NULL; //se a pilha estiver vazia, retorna nulo
    }
    return step;

}

void destroi(pilha *p){
    elemPilha *ptr, *ptrNext;

    ptr = p->topo; //destroi recursivamente todas as camadas da pilha e depois a propria
    while(ptr != NULL){
        ptrNext = ptr->prox;
        free(ptr);
        ptr = ptrNext;
    }
    free(p);
}
