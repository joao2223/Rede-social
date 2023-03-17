#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void cadastrar(lista *l) { //1
	char nome[70], apelido[20];

  printf("--------------------------------------------------------\n");
  printf("Entre com seu nome: ");
  scanf(" %[^\n]s", nome); //escaneia string que pode conter espacos
  printf("Entre com seu apelido: ");
  scanf(" %[^\n]s", apelido);
  if(busca(apelido,l) != NULL){ //se busca nao encontra elemento, retorna nulo
    printf("Usuário já cadastrado no sistema!\n");
    return;
  }

  insere(l,cria_elemLista(apelido,nome)); //insere novo elemento Usuario na lista
  printf("Usuário cadastrado com sucesso!\n");
  printf("--------------------------------------------------------\n");
}

void exibir_lista(lista *l){ //2
  elemLista *stepUsuarios, *stepParceiros;

  printf("--------------------------------------------------------\n");
  if(l->inicio == NULL){ //checa se lista esta vazia
    printf("Ainda não há pessoas cadastradas!\n");
    printf("--------------------------------------------------------\n");
    return;
  }

  printf("Pessoas e seus parceiros:\n");
  stepUsuarios = l->inicio;
  while(stepUsuarios != NULL){
    if(stepUsuarios->user->parceiros->inicio == NULL){ //checa se lista de parceiros do usuario esta vazia
      printf("usuário %s; nome %s; não tem parceiros ainda...\n", stepUsuarios->user->apelido, stepUsuarios->user->nome);
    }
    else{
      printf("usuário: %s; nome: %s; possui parceiria com:", stepUsuarios->user->apelido, stepUsuarios->user->nome);
      stepParceiros = stepUsuarios->user->parceiros->inicio;
      while(stepParceiros != NULL){ //percorre lista de parceiros
        printf(" %s", stepParceiros->user->apelido);
        stepParceiros = stepParceiros->prox;
      }
        printf("\n");
    }

    stepUsuarios = stepUsuarios->prox;
  }
  printf("Listagem completa!\n");
  printf("--------------------------------------------------------\n");
}


  void enviarPedido(lista *l){ //3

    char apelidoRemetente[20],apelidoDestinatario[20];
    elemLista *remetente, *destinatario;

    printf("--------------------------------------------------------\n");
    printf("Entre com seu apelido:");
    scanf(" %[^\n]s", apelidoRemetente);

    remetente = busca(apelidoRemetente,l); //busca retorna nulo se nao encontra
    if(remetente == NULL){
      printf("Usuário não cadastrado!\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    printf("Entre com o apelido de quem você quer ser parceiro:");
    scanf(" %[^\n]s", apelidoDestinatario);

    if(strcmp(apelidoDestinatario,apelidoRemetente) == 0){ //checa se os apelidos sao iguais
      printf("Não pode ser parceiro de si mesmo\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    if(busca(apelidoDestinatario,remetente->user->parceiros) != NULL){ //checa se destinatario ja seria parceiro do remetente
        printf("Você já é parceiro dessa pessoa!\n");
        printf("--------------------------------------------------------\n");
        return;
    }

    destinatario = busca(apelidoDestinatario,l); //finalmente,checa se destinatario existe. Fomos fazendo checagem em ordem crescente de complexidade
    if(destinatario == NULL){
      printf("Usuário não cadastrado!\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    if(busca_fila(apelidoRemetente,destinatario->user->pedidosDeParceiria)){ //checa se remetente esta na fila de pedidos de parceira do destinatario
        printf("Você já tem um pedido pendente de parceiria a esse usuário!\n");
        printf("--------------------------------------------------------\n");
        return;
    }

    if(busca_fila(apelidoDestinatario,remetente->user->pedidosDeParceiria)){ //checa se o destinatario esta na fila de pedidos de perceirias do remetente
        printf("O usuário destinado já lhe enviou um pedido de parceiria!\n");
        printf("--------------------------------------------------------\n");
        return;
    }

    entra(destinatario->user->pedidosDeParceiria,cria_elemFila(apelidoRemetente));//finalmente, insere um pedido na fila do destinatario
    printf("Pedido encaminhado com sucesso!\n");
    printf("--------------------------------------------------------\n");
}

void avaliarPedido(lista *l){ //4
  char apelidoDestinatario[20], input[4];
  elemLista *destinatario;
  Fila *pedidos;
  elemFila *step;
  Usuario *novo;

  printf("--------------------------------------------------------\n");
  printf("Entre com seu apelido:");
  scanf(" %[^\n]s", apelidoDestinatario);

  destinatario = busca(apelidoDestinatario,l);

  if(destinatario == NULL){
    printf("Usuário não cadastrado!\n");
    printf("--------------------------------------------------------\n");
    return;
  }

  pedidos = destinatario->user->pedidosDeParceiria; //obtem fila de pedidos
  if(pedidos->inicio == NULL){ //checa se a mesma esta vazia
    printf("Ainda não há pedidos de parceiria.\n");
    printf("--------------------------------------------------------\n");
    return;
  }

  do{
  step = sai(pedidos);
  if(step != NULL){//itera por todos os pedidos ate acabarem
    while(1){//mantem o laco ate inserir-se uma resposta satisfatoria
      printf("%s deseja ser seu(ua) parceiro(a). Aceita?(sim/nao)",step->apelido);
      scanf("%s",input);
      if(strcmp(input,"sim") == 0 || strcmp(input,"nao") == 0){
        break;
      }
      printf("Insira uma resposta válida!\n");
    }
    if(strcmp(input,"sim") == 0){//caso a resposta seja nao, nao precisa fazer mais nada, pois o pedido ja saiu da fila
      novo = busca(step->apelido,l)->user;  //poupar uma busca e ficar menos feio
      insere(destinatario->user->parceiros,cria_elemLista2(novo));//insere o remetente na lista de pareceiros do destinatario
      insere(novo->parceiros,cria_elemLista2(destinatario->user));//e vice-versa
    }
  }

  }while(step != NULL);

  printf("Operação realizada com sucesso.\n");
  printf("--------------------------------------------------------\n");
}

void enviarMensagem(lista *l){ //5
    char msg[280], apelidoRemetente[20], apelidoDestinatario[20];
    elemLista *remetente, *destinatario;
    int err;

    printf("--------------------------------------------------------\n");
    printf("Entre com seu apelido:");
    scanf(" %[^\n]s", apelidoRemetente);

    remetente = busca(apelidoRemetente,l);//checa se quem quer mandar as mensagens existe no sistema
    if(remetente == NULL){
      printf("Usuário não cadastrado!\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    printf("Entre com o apelido de quem você quer mandar mensagem:");
    scanf(" %[^\n]s", apelidoDestinatario);

    if(strcmp(apelidoDestinatario,apelidoRemetente) == 0){ //checa se nao seria ele mesmo
      printf("Não se pode enviar mensagem a si mesmo\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    destinatario = busca(apelidoDestinatario,l); //checa se destinatario existe
    if(destinatario == NULL){
      printf("Usuário não cadastrado!\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    destinatario = busca(apelidoDestinatario,remetente->user->parceiros); //checa se destinatario estaria na lista de parceiros do remetente
    if(destinatario == NULL){                                             //poderia fazer o contrario
      printf("Usuário não é seu parceiro ainda!\n");
      printf("--------------------------------------------------------\n");
      return;
    }

    printf("Entre com a mensagem: ");
    scanf(" %[^\n]s", msg);
    push(destinatario->user->mensagens,cria_elemPilha(remetente->user->apelido,msg),&err);//empilha mensagem

    printf("\nMensagem enviada com sucesso!\n");
    printf("--------------------------------------------------------\n");
}

void verMensagem(lista *l){ //6
  pilha *msgs, *auxPilha;
  elemLista *destinatario;
  elemPilha *step;
  char apelidoDestinatario[20];
  int err;

  printf("--------------------------------------------------------\n");
  printf("Entre com seu apelido:");
  scanf(" %[^\n]s", apelidoDestinatario);

  destinatario = busca(apelidoDestinatario,l); //checa se quem quer ver as mensagens existe no sistema
  if(destinatario == NULL){
    printf("Usuário não cadastrado!\n");
    printf("--------------------------------------------------------\n");
    return;
  }
  msgs = destinatario->user->mensagens;

  if(msgs->topo == NULL){ //checa se a pilha de mensagens esta vazia
    printf("Não há mensagens ainda!\n");
    printf("--------------------------------------------------------\n");
    return;
  }
  auxPilha = cria_pilha(&err); //cria pilha auxiliar para manter a ordem

  step = pop(msgs,&err);
  printf("Suas mensagens são:\n");
  do{
    if(step->isLida == 0){ //se a mensagem for nova, coloca um indicador
        printf("*NOVA* ");
        step->isLida = 1; //e marca ela como lida
    }
    printf("%s %s\n",step->remetenteApelido,step->mensagem); //imprime a mensagem, sendo a mais nova impressa primeiro
    push(auxPilha,step,&err); //monta a pilha auxiliar
    step = pop(msgs,&err); //pega a proxima mensagem
  }while(step != NULL);

  step = pop(auxPilha, &err);
  do{//remonta a pilha original
    push(msgs,step,&err);
    step = pop(auxPilha, &err);
  }while(step != NULL);

  destroi(auxPilha); //destroi pilha original, ja vazia
  printf("Mensagens exibidas!\n");
  printf("--------------------------------------------------------\n");
}

void sugerirParceria(lista *l){
    elemLista *step1, *step2;
    int nComum, flagHaSugest = 0;

    printf("--------------------------------------------------------\n");
    if(l->inicio == NULL){
        printf("Não há usuários cadastrados no momento!\n");
        printf("--------------------------------------------------------\n");
        return;
    }

    printf("Sugestões de parceirias para cada usuário:\n");
    step1 = l->inicio;//inicia a comparacao comparando os dois primeiros elementos
    step2 = l->inicio->prox;
    while(step1 != NULL){//enquanto n acabar a lista
        printf("%s:\n", step1->user->apelido);//recomendacoes para esse usuario
        while(step2 != NULL){//compara com todos da lista
            if(busca(step2->user->apelido,step1->user->parceiros) == NULL){ //que nao ja sejam parceiros
                nComum = contaSimilaridades(step1->user->parceiros, step2->user->parceiros); //conta parceiros em comum entre ambos
                if(nComum > 0){ //se tiverem mais que um, ja sao uma recomendacao
                    printf("%s (%d parceiro(s) em comum)\n", step2->user->apelido, nComum); //imprime a recomendacao e o numero de amigos em comum
                    flagHaSugest = 1;
                }
            }
            step2 = step2->prox;//proximo a checar se seria uma recomendacao valida
            if(step2 == step1){ //evitar que comparem os mesmos - a partir do segundo laco isso seria uma possibilidade
                step2 = step2->prox; //mas ela acaba sendo impedida por esse if
            }
        }
        if(!flagHaSugest){//se nao houver recomendacoes, imprime uma mensagem apropriada
            printf("Não há sugestões para esse usuario\n");
        }
        flagHaSugest = 0;
        step2 = l->inicio;
        step1 = step1->prox; //procura recomendacoes para o proximo
    }

    printf("Operação realizada com sucesso!\n");
    printf("--------------------------------------------------------\n");
}

lista* reinicializar(lista *l){
    elemLista *step;


    printf("--------------------------------------------------------\n");
    step = l->inicio;
    while(step != NULL){ //itera pela lista, destruindo as estruturas de dados internas dos elementes e depois liberando os proprios
        destroi(step->user->mensagens);
        destroi_lista(step->user->parceiros); //lista
        destroi_fila(step->user->pedidosDeParceiria); //fila
        free(step->user);

        step = step->prox;
    }
    destroi_lista(l);//destroi a lista em si
    l = cria_lista();//cria uma nova

    printf("Operação realizada com sucesso!\n");
    printf("--------------------------------------------------------\n");
    return l;
}
