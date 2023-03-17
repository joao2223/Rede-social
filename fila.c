#include "fila.h"
#include <stdlib.h>
#include <strings.h>

Fila* cria_fila(){
    Fila *f;

    f = (Fila*) malloc(sizeof(Fila)); //aloca fila
    if(f == NULL){
       exit(1); //se faltar memoria, aborta
    }
    f->fim = NULL; //inicializa com nulo, para permitir acessar a possicao quando a fila estiver vazial
    f->inicio = NULL;
    return f;
}

elemFila* cria_elemFila(char apelido[]){
  elemFila *retval;

  retval = (elemFila*)malloc(sizeof(elemFila));
  if(retval == NULL){
    exit(1); //se memoria, aborta
  }
  retval->prox = NULL; //inicializa com nulo, para poder acessar valor, caso vazio
  strcpy(retval->apelido,apelido);
  return retval;
}

void entra(Fila *f, elemFila *novo){

	if(f->inicio == NULL){ //se vazio, deve-se alocar o fim como sendo igual ao comeco
		f->inicio = novo;
		f->fim = novo;

	}else{
		f->fim->prox = novo;
		f->fim = novo; //coloca o novo no fim da fila
	}

}


elemFila* sai(Fila *f){
	elemFila *retval;

  if(f->inicio == NULL){
    return NULL;
	}
  else{
		retval = f->inicio;
		f->inicio = f->inicio->prox; //retorna o inicio da fila
		return retval;
	}
}

void destroi_fila(Fila *f){

    elemFila *ptr, *ptrNext;

    ptr = f->inicio;
    while(ptr != NULL){ //iterativamente move o inicio da fila para frente e libera a memoria do antigo inicio
        ptrNext = ptr->prox;
        free(ptr);
        ptr = ptrNext;
    }
    free(f); //libera a fila em si
}

int busca_fila(char apelidoID[], Fila *f){
    Fila *aux; //poderia usar o encadeamento da lista/fila para buscar, mas preferi conservar a logica de fila;
    elemFila *step;
    int retval;

    if(f->inicio == NULL){ //se a fila estiver vazi, nao ha o elemento requerido
        return 0;
    }

    aux = cria_fila();
    retval = 0; //pressupoe que nao vai encontrar
    step = sai(f);
    do{
        entra(aux,step); //monta a fila auxiliar, identica a original
        if(strcmp(step->apelido,apelidoID) == 0){ //encontrou o que procurava
            retval = 1;
        }
        step = sai(f);
    }while(step != NULL);

    step = sai(aux);
    do{
        entra(f,step); //devolve a lista original a posicao de memoria original
        step = sai(aux);
    }while(step != NULL);

    destroi_fila(aux); //destroi o auxiliar
    return retval;
}
