
typedef struct elemPilha{
    char remetenteApelido[20], mensagem[280];
    struct elemPilha *prox;
    int isLida;
}elemPilha;

typedef struct pilha{
    elemPilha *topo;
}pilha;

int isEmpty(pilha *p);
elemPilha* cria_elemPilha(char remetenteApelido[],char mensagem[]);
pilha* cria_pilha(int *erro);
void push(pilha *p, elemPilha *newE, int *erro);
elemPilha* pop(pilha *p, int *erro);
void destroi(pilha *p);
