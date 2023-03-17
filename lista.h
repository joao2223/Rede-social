#include "fila.h"
#include "pilhaEncadeada.h"

typedef struct Usuario Usuario;

typedef struct elemLista {
   Usuario *user;
   struct elemLista *prox;
}elemLista;

typedef struct lista{
  elemLista *inicio;
}lista;

typedef struct Usuario{
  //struct Usuario **parceiros;
  lista *parceiros;
  char nome[70], apelido[20];
  Fila *pedidosDeParceiria; //fila de usuarios
  pilha *mensagens;
} Usuario;


lista* cria_lista();
elemLista* busca (char apelido[], lista *l);
elemLista* cria_elemLista(char apelido[], char nome[]);
elemLista* cria_elemLista2(Usuario *user);
void insere (lista *l, elemLista *nova);
void remover(elemLista *p);
void busca_e_remove (char apelido[], lista *l);
int contaSimilaridades(lista *l1, lista *l2);
void destroi_lista(lista *l);






