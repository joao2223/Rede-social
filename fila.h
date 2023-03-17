
typedef struct elemFila{
	char apelido[20];
	struct elemFila *prox;
}elemFila;

typedef struct Fila{
    elemFila *inicio;
    elemFila *fim;
} Fila;


Fila* cria_fila();
elemFila* cria_elemFila(char apelido[]);
//elemFila* cria_elemFila2(Usuario *usPassado);
void entra(Fila *fi, elemFila *novo);
elemFila* sai(Fila *fi);
void destroi_fila(Fila *f);
int busca_fila(char apelidoID[], Fila *f);
