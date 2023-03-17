#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <strings.h>
#include "operacoes.h"

int main(){
    lista *Usuarios;
    char input[2];
    int n;
    Usuarios = cria_lista();

    setlocale(LC_ALL, "Portuguese"); //permitir acentos, tils e cedilhas
do {

	    printf("Caro usuário, suas opções são: \n");
	    printf(" 1) cadastrar um usuário \n");
	    printf(" 2) listar usuários cadastrados e suas informações \n");
	    printf(" 3) pedir para ser parceiro de um usuário \n");
	    printf(" 4) avaliar lista de pedidos de parceria \n");
	    printf(" 5) enviar mensagem para um parceiro \n");
	    printf(" 6) ver mensagens recebidas \n");
	    printf(" 7) sugerir novas parcerias \n");
	    printf(" 8) reinicializar sistema \n");
	    printf(" Outra coisa) sair do programa\n");
	    printf("--------------------------------------------------------\n");

        printf("O que deseja fazer? \n");
    	printf("Resposta: ");
	    scanf("%s",input);
	    n = atoi(input);
	    switch(n){
	    case 1:
	        cadastrar(Usuarios);
          break;

	    case 2:
	        exibir_lista(Usuarios);
          break;

      case 3:
          enviarPedido(Usuarios);
          break;

      case 4:
          avaliarPedido(Usuarios);
          break;

      case 5:
          enviarMensagem(Usuarios);
          break;

      case 6:
          verMensagem(Usuarios);
          break;

      case 7:
          sugerirParceria(Usuarios);
          break;

      case 8:
          Usuarios = reinicializar(Usuarios);
          break;

      default:
        reinicializar(Usuarios);
        destroi_lista(Usuarios);//libera toda a memoria antes de sair do loop e encerrar o programa
        n = 0;
        break;

	    }
    }while(n!=0);

    return 0;
}
