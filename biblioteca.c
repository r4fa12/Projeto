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
};

void Novo_Cliente() {
    char nome[100];
    char cpf[15];
    char conta[20];
    size_t len;
    size_t len2;
    double vinicial;
    char senha[100];
    char descricao[100];
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    printf("Digite seu CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    limpar();
    printf("Digite qual sera seu tipo de conta(Comum/comum ou Plus/plus):");
    fgets(conta, sizeof(conta), stdin);
    len2 = strlen(nome);
    if (nome[len2 - 1] == '\n') nome[--len2] = 0;
    len = strlen(conta);
    if (conta[len - 1] == '\n') conta[--len] = 0;
    printf("Digite qual o valor inicial da conta: ");
    scanf("%lf", &vinicial);
    limpar();
    printf("Crie sua senha: ");
    fgets(senha, sizeof(senha), stdin);
    printf("Sua conta foi criada com sucesso!!\n");
    for (int i = 0; i < 1000; i++) {
        if (registro[i].existe == 0) {
            sprintf(descricao,"CLiente criado com sucesso!");
            double valor1 = 1;
            float tarifa1 = 1;
            registro[i].pos = 1;
            int pos = registro[i].pos;
            registro[i].extrato[pos].existe = pos;
            registro[i].pos = registro[i].pos + 1;
            registro[i].extrato[pos].valor = valor1;
            registro[i].extrato[pos].tarifa = tarifa1;
            strcpy(registro[i].extrato[pos].descricao,descricao);
            strcpy(registro[i].nome, nome);
            strcpy(registro[i].senha, senha);
            strcpy(registro[i].conta, conta);
            strcpy(registro[i].cpf, cpf);
            registro[i].vinicial = vinicial;
            registro[i].existe = 1;
            break;
        };
    };
};