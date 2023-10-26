#include <stdio.h>
#include "biblioteca.h"
#include <stdlib.h>
#include <string.h>

Cliente registro[1000];

int criararquivo(){
    FILE*registroarq = fopen("arqclientes","wb");
  if(registroarq == NULL){
    return 1;
  }
    fwrite(&registro,sizeof(Cliente),1000,registroarq);
    fclose(registroarq);
    return 0;
}

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
};

void Menu() {
    int cod;
    cod = lerarquivo();
    if(cod == 1){
        printf("Nao foi possivel ler o arquivo!");
    }
    Cliente *cliente = malloc(sizeof(Cliente));
    int opcao;
    do {
        printf("MENU\n");
        printf(" 1.Novo Cliente\n 2.Apagar cliente\n 3.Listar clientes\n 4.Debito\n 5.Deposito\n ");
        printf("6.Extrato\n 7.Tranferencia\n 0.Sair\n");
        printf("Digite qual operacao deseja realizar: ");
        scanf("%d", &opcao);
        limpar();
        switch (opcao) {
            case 1:
                Novo_Cliente();
                break;
            case 2:
                Apagar_Clientes();
                break;
            case 3:
                Listar_Clientes();
                break;
            case 4:
                Debito();
                break;
            case 5:
                Deposito();
                break;
            case 6:
                Extrato();
                break;
            case 7:
                Transferencias();
                break;
        }
    }while (opcao != 0);
        criararquivo();
}