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

void Apagar_Clientes() {
    char cpf2[15];
    char senha2[100];
    printf("Digite seu CPF: ");
    fgets(cpf2, sizeof(cpf2), stdin);
    int i;
    for (i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            int comp = strcmp(cpf2, registro[i].cpf);
            if (comp == 0) {
                break;
            };
        };
    }
    if (i < 999) {
        limpar();
        printf("Digite sua senha: ");
        fgets(senha2, sizeof(senha2), stdin);
        int comp2 = strcmp(senha2, registro[i].senha);
        if (comp2 == 0) {
            registro[i].existe = 0;
            printf("Sua conta foi apagada com sucesso!!\n");
        } else
            printf("Senha errada!\n");
    } else {
        printf("CPF nao encontrado!\n");
    }
};

void Listar_Clientes() {
    printf("--- LISTA DE CLIENTES ---\n");
    printf("\n");
    for (int i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            printf("\n");
            printf("Nome: %s\n", registro[i].nome);
            printf("Cpf: %s\n", registro[i].cpf);
            printf("Conta: %s\n", registro[i].conta);
            printf("Valor: %.2lf\n", registro[i].vinicial);
            printf("Senha: %s\n", registro[i].senha);
            printf("---------------------\n");
        }
    }
};

void Debito() {
    char descricao[100];
    double deb;
    char cpf2[15];
    char senha2[100];
    printf("Digite seu CPF: ");
    fgets(cpf2, sizeof(cpf2), stdin);
    int i;
    for (i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            int comp = strcmp(cpf2, registro[i].cpf);
            if (comp == 0) {
                break;
            };
        };
    }
    if (i < 999) {
        limpar();
        printf("Digite sua senha: ");
        fgets(senha2, sizeof(senha2), stdin);
        int comp2 = strcmp(senha2, registro[i].senha);
        if (comp2 == 0) {
            printf("Digite o valor que deseja debitar: ");
            scanf("%lf", &deb);
            char tipo1[5] = "Plus\0";
            int comp3 = strcmp(tipo1,registro[i].conta);
            if(comp3 == 0){
                float tarifap = 0.03;
                deb = deb + (deb * tarifap);
                if(deb > (registro[i].vinicial + 5000)){
                    printf("O valor que foi digitado e maior do que a quantidade atual de credito na conta mais o limite de saldo negativo(5000)! ");
                    printf("Por tanto o debito foi negado.\n");
                }
                else{
                    registro[i].vinicial = registro[i].vinicial - deb;
                    printf("Debito realizado com sucesso!");
                    printf("Seu valor atualizado: %.2lf\n", registro[i].vinicial);
                    sprintf(descricao,"Debito realizado.");
                    double valor = deb;
                    int pos = registro[i].pos;
                    registro[i].extrato[pos].existe = pos;
                    registro[i].pos = registro[i].pos + 1;
                    if(registro[i].extrato[pos].existe >= 99){
                        for(int x = 1; x < 100; x++){
                            registro[i].extrato[x].existe = registro[i].extrato[x].existe - 1;
                        }
                    }
                    registro[i].extrato[pos].valor = valor;
                    registro[i].extrato[pos].tarifa = (deb * tarifap);
                    strcpy(registro[i].extrato[pos].descricao,descricao);
                }
            }else {
                float tarifac = 0.05;
                deb = deb + (deb * 0.05);
                if (deb > (registro[i].vinicial + 1000)) {
                    printf("O valor que foi digitado e maior do que a quantidade atual de credito na conta mais o limite de saldo negativo(1000)! ");
                    printf("Por tanto o debito foi negado.\n");
                } else {
                    registro[i].vinicial = registro[i].vinicial - deb;
                    printf("Debito realizado com sucesso!");
                    printf("Seu valor atualizado: %.2lf\n", registro[i].vinicial);
                    sprintf(descricao,"Debito realizado.");
                    double valor = deb;
                    int pos = registro[i].pos;
                    registro[i].extrato[pos].existe = pos;
                    registro[i].pos = registro[i].pos + 1;
                    if(registro[i].extrato[pos].existe >= 99){
                        for(int x = 1; x < 100; x++){
                            registro[i].extrato[x].existe = registro[i].extrato[x].existe - 1;
                        }
                    }
                    registro[i].extrato[pos].valor = valor;
                    registro[i].extrato[pos].tarifa = (deb * tarifac);
                    strcpy(registro[i].extrato[pos].descricao,descricao);
                }
            }
        }
    }else{
        printf("CPF nao encontrado!\n");
    }
};

void Deposito() {
    char descricao[100];
    double dep;
    char cpf2[15];
    char senha2[100];
    printf("Digite seu CPF: ");
    fgets(cpf2, sizeof(cpf2), stdin);
    int i;
    for (i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            int comp = strcmp(cpf2, registro[i].cpf);
            if (comp == 0) {
                break;
            };
        };
    }
    if (i < 1000) {
        limpar();
        printf("Digite sua senha: ");
        fgets(senha2, sizeof(senha2), stdin);
        int comp2 = strcmp(senha2, registro[i].senha);
        if (comp2 == 0) {
            printf("Digite o valor que deseja depositar: ");
            scanf("%lf", &dep);
            registro[i].vinicial = registro[i].vinicial + dep;
            printf("Deposito realizado com sucesso!\n");
            printf("Seu valor atualizado: %.2lf\n", registro[i].vinicial);
            sprintf(descricao,"Deposito realizado.");
            double valor = dep;
            int pos = registro[i].pos;
            registro[i].extrato[pos].existe = pos;
            registro[i].pos = registro[i].pos + 1;
            if(registro[i].extrato[pos].existe >= 99){
                for(int x = 1; x < 100; x++){
                    registro[i].extrato[x].existe = registro[i].extrato[x].existe - 1;
                }
            }
            registro[i].extrato[pos].valor = valor;
            registro[i].extrato[pos].tarifa = 0;
            strcpy(registro[i].extrato[pos].descricao,descricao);
        }
    }else{
        printf("CPF nao encontrado!\n");
    }
}

void Extrato() {
    char cpf2[15];
    char senha2[100];
    printf("Digite seu CPF: ");
    fgets(cpf2, sizeof(cpf2), stdin);
    int i;
    for (i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            int comp = strcmp(cpf2, registro[i].cpf);
            if (comp == 0) {
                break;
            };
        };
    }
    if (i < 1000) {
        limpar();
        printf("Digite sua senha: ");
        fgets(senha2, sizeof(senha2), stdin);
        int comp2 = strcmp(senha2, registro[i].senha);
        if (comp2 == 0) {
            printf("\n\n");
            printf("Cliente: %s\n",registro[i].nome);
            printf("Cpf: ¨%s\n",registro[i].cpf);
            printf("Tipo de conta %s\n",registro[i].conta);
            printf("\n");
            printf("----- EXTRATO -----\n");
            printf("\n");
            FILE*extratoarq = fopen("extratoarq.txt","w");
            fprintf(extratoarq,"Cliente: %s\n",registro[i].nome);
            fprintf(extratoarq,"Cpf: ¨%s\n",registro[i].cpf);
            fprintf(extratoarq,"Tipo de conta %s\n",registro[i].conta);
            fprintf(extratoarq,"\n");
            fprintf(extratoarq,"----- EXTRATO -----\n");
            fprintf(extratoarq,"\n");
            for(int e = 0; e < 100 ; e++){
                if(registro[i].extrato[e].existe > 0){
                    printf("%s\n",registro[i].extrato[e].descricao);
                    printf("Valor: %.2lf\n",registro[i].extrato[e].valor);
                    printf("Tarifa: %.2lf\n",registro[i].extrato[e].tarifa);
                    printf("\n");
                    fprintf(extratoarq,"%s\n",registro[i].extrato[e].descricao);
                    fprintf(extratoarq,"Valor: %.2lf\n",registro[i].extrato[e].valor);
                    fprintf(extratoarq,"Tarifa: %.2lf\n",registro[i].extrato[e].tarifa);
                    fprintf(extratoarq,"\n");
                }
            }
            fclose(extratoarq);
        }
    }
};

void Transferencias() {
    double qtdf;
    char descricao[100];
    char descricao2[100];
    char nomep[20];
    char nomer[20];
    char cpf2[15];
    char senha2[100];
    char cpf3[15];
    printf("Digite seu CPF: ");
    fgets(cpf2, sizeof(cpf2), stdin);
    int i;
    for (i = 0; i < 1000; i++) {
        if (registro[i].existe == 1) {
            int comp = strcmp(cpf2, registro[i].cpf);
            if (comp == 0) {
                break;
            };
        };
    }
    if (i < 1000) {
        limpar();
        printf("Digite sua senha: ");
        fgets(senha2, sizeof(senha2), stdin);
        int comp2 = strcmp(senha2, registro[i].senha);
        if (comp2 == 0) {
            printf("Digite o CPF de quem recebera a trasferencia: ");
            fgets(cpf3, sizeof(cpf3), stdin);
            int j;
            for (j = 0; j < 1000; j++) {
                if (registro[j].existe == 1) {
                    int comp = strcmp(cpf3, registro[j].cpf);
                    if (comp == 0) {
                        break;
                    };
                };
            }
            if(j < 999){
                sprintf(nomep,registro[j].nome);
                sprintf(nomer,registro[i].nome);
                printf("Digite a quantidade que deseja transferir: ");
                scanf("%lf",&qtdf);
                registro[i].vinicial = registro[i].vinicial - qtdf;
                registro[j].vinicial = registro[j].vinicial + qtdf;
                printf("Seu valor atual: %2.lf\n",registro[i].vinicial);
                sprintf(descricao,"Transferencia realizada para %s",nomep);
                double valor = qtdf;
                int pos = registro[i].pos;
                registro[i].extrato[pos].existe = pos;
                registro[i].pos = registro[i].pos + 1;
                if(registro[i].extrato[pos].existe >= 99){
                    for(int x = 1; x < 100; x++){
                        registro[i].extrato[x].existe = registro[i].extrato[x].existe - 1;
                    }
                }
                registro[i].extrato[pos].valor = valor;
                registro[i].extrato[pos].tarifa = 0;
                strcpy(registro[i].extrato[pos].descricao,descricao);
                sprintf(descricao2,"Transferencia recebida de %s",nomer);
                int pos2 = registro[j].pos;
                registro[j].extrato[pos2].existe = pos;
                registro[j].pos = registro[j].pos + 1;
                if(registro[i].extrato[pos].existe >= 99){
                    for(int x = 1; x < 100; x++){
                        registro[i].extrato[x].existe = registro[i].extrato[x].existe - 1;
                    }
                }
                registro[j].extrato[pos2].valor = valor;
                registro[j].extrato[pos2].tarifa = 0;
                strcpy(registro[j].extrato[pos2].descricao,descricao2);
            }else{
                printf("CPF do recebidor não encontrado!\n");
            }
        }
    }else{
        printf("CPF nao encontrado!\n");
    }
};