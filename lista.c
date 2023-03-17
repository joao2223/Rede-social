#include "lista.h"
#include <stdlib.h>
#include <strings.h>

lista* cria_lista(){
  lista *retval;

  retval = (lista*)malloc(sizeof(lista));
  if(retval == NULL){
    exit(1); //se nao houver memoria, aborta
  }

  retval->inicio = NULL; //inicializa com nulo para poder acessar a memoria, mesmo caso vazia
  return retval;
}

elemLista* busca (char apelido[], lista *l)
{
   elemLista *p;
   p = l->inicio;
   while (p != NULL && strcmp(p->user->apelido,apelido) != 0) //para de iterar caso chegue ao nulo ou ao elemento desejado
      p = p->prox;
   return p; //caso nao enconte, ira retornar nulo
}

elemLista* cria_elemLista(char apelido[], char nome[]){
  elemLista *retval;
  int err;

  retval = (elemLista*)malloc(sizeof(elemLista)); //aloca memoria inicial
  if(retval == NULL){
    exit(1); //se faltar memoria, aborta
  }
  retval->prox = NULL; //inicializa com nulo para poder acessar a memoria, mesmo caso vazia
  retval->user = (Usuario*)malloc(sizeof(Usuario)); //atribui os valores dados e inicializa as estrutras de dados internas
  retval->user->parceiros = cria_lista();
  strcpy(retval->user->nome,nome);
  strcpy(retval->user->apelido,apelido);
  retval->user->pedidosDeParceiria = cria_fila();
  retval->user->mensagens = cria_pilha(&err);

  return retval;
}

elemLista* cria_elemLista2(Usuario *user){ //cria um elo da lista partindo de um Usuario previamente criado
  elemLista *retval;

  retval = (elemLista*)malloc(sizeof(elemLista));
  if(retval == NULL){

  }
  retval->prox = NULL;
  retval->user = user;
  return retval;
}

void insere (lista *l, elemLista *nova)
{
   nova->prox = l->inicio; //insere novo elemento
   l->inicio = nova;
}

int contaSimilaridades(lista *l1, lista *l2){ //vai receber duas listas de amigos(usuarios), retorna numero de itens em comum
	int nComum = 0;
	elemLista *step1, *step2;

	step1 = l1->inicio;
	if(step1 == NULL){
        return -1; //indica que a lista que deseja achar uma similar eh vazia
	}
	step2 = l2->inicio;
	if(step2 == NULL){
        return 0; //n ha nenhum elemento em comum na 2 pois n ha elementos
	}

	while(step1 != NULL){ //compara todos os elementos da primeira com todos os da segunda
    	while(step2 != NULL){
            if (strcmp(step1->user->apelido, step2->user->apelido) == 0){ //ambos os apelidos iguais implica em um usuario em comum
                    nComum = nComum + 1;
                }
        	step2 = step2->prox;
    	}
		step1 = step1->prox;
		step2 = l2->inicio;
     }
    	return nComum;
}

void destroi_lista(lista *l){

    elemLista *ptr, *ptrNext;

    ptr = l->inicio;
    while(ptr != NULL){ //destroi iterativamente todos os elos da lista e depos a propria
        ptrNext = ptr->prox;
        free(ptr);
        ptr = ptrNext;
    }
    free(l);
    l = NULL;
}
