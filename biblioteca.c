#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

int criararquivo(Cliente Nome[],char nomearq[]) { // Função para criar o arquivo geral do banco
  FILE *registroarq = fopen(nomearq, "wb");
  if (registroarq == NULL) {
    return 1;
  }
  fwrite(&Nome, sizeof(Cliente), maxclientes, registroarq);
  fclose(registroarq);
  return 0;
}

void limpar() { // limpar os buffs
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void Menu() { // função do menu onde aparecem as operações do banco
  Cliente registro[maxclientes];
  int cod;
  cod = lerarquivo(registro, "arqclientes");
  if (cod == 1) { // comparação para saber se o arquivo foi lido com sucesso
    printf("Nao foi possivel ler o arquivo!");
  }
  int opcao;
  do {
    printf("MENU\n");
    printf(" 1.Novo Cliente\n 2.Apagar cliente\n 3.Listar clientes\n "
           "4.Debito\n 5.Deposito\n ");
    printf("6.Extrato\n 7.Tranferencia\n 0.Sair\n");
    printf("Digite qual operacao deseja realizar: ");
    scanf("%d", &opcao);
    limpar();
    switch (opcao) {
    case 1:
      Novo_Cliente(registro);
      break;
    case 2:
      Apagar_Clientes(registro);
      break;
    case 3:
      Listar_Clientes(registro);
      break;
    case 4:
      Debito(registro);
      break;
    case 5:
      Deposito(registro);
      break;
    case 6:
      Extrato(registro);
      break;
    case 7:
      Transferencias(registro);
      break;
    }
  } while (opcao != 0);
  criararquivo(registro,
               "arqclientes"); // criando o arquivo quando o programa é fechado
}

void Novo_Cliente(Cliente Nome[]) { // função de criar o cliente
  char nome[100];
  char cpf[15];
  char conta[20];
  size_t len;
  size_t len2;
  double vinicial;
  char senha[100];
  char descricao[100];
  char testeconta[10];
  char testeconta2[10];
  sprintf(testeconta, "Comum");
  sprintf(testeconta2, "Plus");
  printf("Digite o seu nome: ");
  fgets(nome, sizeof(nome), stdin);
  printf("Digite seu CPF: ");
  fgets(cpf, sizeof(cpf), stdin);
  limpar();
  int comp;
  int comp2;
  do { // comparação entre as contas existentes e as digitadas (somente sao
       // validas contas Comum e Plus)
    printf("Digite qual sera seu tipo de conta(Comum ou Plus):");
    fgets(conta, sizeof(conta), stdin);
    len = strlen(conta);
    if (conta[len - 1] == '\n')
      conta[--len] = 0;
    comp = strcmp(conta, testeconta);
    comp2 = strcmp(conta, testeconta2);
  } while (comp != 0 && comp2 != 0);
  len2 = strlen(nome);
  if (nome[len2 - 1] == '\n')
    nome[--len2] = 0; // para tirar o \n do final do nome
  printf("Digite qual o valor inicial da conta: ");
  scanf("%lf", &vinicial);
  limpar();
  printf("Crie sua senha: ");
  fgets(senha, sizeof(senha), stdin);
  printf("Sua conta foi criada com sucesso!!\n");
  for (int i = 0; i < maxclientes; i++) {
    if (Nome[i].existe == 0) { // para saber se é um cliente existente
      sprintf(descricao, "CLiente criado com sucesso!");
      double valor1 = 1;
      float tarifa1 = 1;
      Nome[i].pos = 1;
      int pos = Nome[i].pos;
      Nome[i].extrato[pos].existe = pos;
      Nome[i].pos = Nome[i].pos + 1;
      Nome[i].extrato[pos].valor = valor1;
      Nome[i].extrato[pos].tarifa = tarifa1;
      strcpy(Nome[i].extrato[pos].descricao, descricao);
      strcpy(Nome[i].nome, nome);
      strcpy(Nome[i].senha, senha);
      strcpy(Nome[i].conta, conta);
      strcpy(Nome[i].cpf, cpf);
      Nome[i].vinicial = vinicial;
      Nome[i].existe = 1;
      break;
    }
  }
}

void Apagar_Clientes(Cliente Nome[]) { // função de apagar um cliente existente
  char cpf2[15];
  char senha2[100];
  printf("Digite seu CPF: ");
  fgets(cpf2, sizeof(cpf2), stdin);
  int i;
  for (i = 0; i < maxclientes; i++) { // verifica se o cpf esta no banco de dados
                               // podendo apagar o cliente
    if (Nome[i].existe == 1) {
      int comp = strcmp(cpf2, Nome[i].cpf);
      if (comp == 0) {
        break;
      }
    }
  }
  if (i < 999) {
    limpar();
    printf("Digite sua senha: ");
    fgets(senha2, sizeof(senha2), stdin);
    int comp2 =
        strcmp(senha2, Nome[i].senha); // verifica se a senha esta no banco de
                                       // dados podendo apagar o cliente
    if (comp2 == 0) {
      Nome[i].existe = 0;
      printf("Sua conta foi apagada com sucesso!!\n");
    } else
      printf("Senha errada!\n");
  } else {
    printf("CPF nao encontrado!\n");
  }
}

void Listar_Clientes(Cliente Nome[]) { // função listar clientes
  printf("--- LISTA DE CLIENTES ---\n");
  printf("\n");
  for (int i = 0; i < maxclientes; i++) {
    if (Nome[i].existe == 1) {
      printf("\n");
      printf("Nome: %s\n", Nome[i].nome);
      printf("Cpf: %s\n", Nome[i].cpf);
      printf("Conta: %s\n", Nome[i].conta);
      printf("Valor: %.2lf\n", Nome[i].vinicial);
      printf("Senha: %s\n", Nome[i].senha);
      printf("---------------------\n");
    }
  }
}

void Debito(Cliente Nome[]) { // função de debito
  char descricao[100];
  double deb;
  char cpf2[15];
  char senha2[100];
  printf("Digite seu CPF: ");
  fgets(cpf2, sizeof(cpf2), stdin);
  int i;
  for (i = 0; i < maxclientes; i++) { // verifica se o cpf esta no banco de dados
    if (Nome[i].existe == 1) {
      int comp = strcmp(cpf2, Nome[i].cpf);
      if (comp == 0) {
        break;
      }
    }
  }
  if (i < 999) {
    limpar();
    printf("Digite sua senha: ");
    fgets(senha2, sizeof(senha2), stdin);
    int comp2 = strcmp(
        senha2,
        Nome[i].senha); // verifica se a senha esta de acordo com o cpf digitado
    if (comp2 == 0) {
      printf("Digite o valor que deseja debitar: ");
      scanf("%lf", &deb);
      char tipo1[5] = "Plus\0";
      int comp3 = strcmp(tipo1, Nome[i].conta);
      if (comp3 == 0) { // verifica o tipo de conta (Comum ou Plus)
        float tarifap = 0.03;
        deb = deb + (deb * tarifap); // aplica a tarifa
        if (deb > (Nome[i].vinicial + 5000)) {
          printf("O valor que foi digitado e maior do que a quantidade atual "
                 "de credito na conta mais o limite de saldo negativo(5000)! ");
          printf("Por tanto o debito foi negado.\n");
        } else {
          Nome[i].vinicial = Nome[i].vinicial - deb;
          printf("Debito realizado com sucesso!");
          printf("Seu valor atualizado: %.2lf\n", Nome[i].vinicial);
          sprintf(descricao, "Debito realizado.");
          double valor = deb;
          int pos = Nome[i].pos;
          Nome[i].extrato[pos].existe = pos;
          Nome[i].pos = Nome[i].pos + 1;
          if (Nome[i].extrato[pos].existe >= 99) {
            for (int x = 1; x < 100; x++) {
              Nome[i].extrato[x].existe = Nome[i].extrato[x].existe - 1;
            }
          }
          Nome[i].extrato[pos].valor = valor;
          Nome[i].extrato[pos].tarifa =
              (deb * tarifap); // adiciona no extrato do cliente as informações
          strcpy(Nome[i].extrato[pos].descricao, descricao);
        }
      } else {
        float tarifac = 0.05;
        deb = deb + (deb * 0.05); // aplica a tarifa 2
        if (deb > (Nome[i].vinicial + maxclientes)) {
          printf("O valor que foi digitado e maior do que a quantidade atual "
                 "de credito na conta mais o limite de saldo negativo(maxclientes)! ");
          printf("Por tanto o debito foi negado.\n");
        } else {
          Nome[i].vinicial = Nome[i].vinicial - deb;
          printf("Debito realizado com sucesso!");
          printf("Seu valor atualizado: %.2lf\n", Nome[i].vinicial);
          sprintf(descricao, "Debito realizado.");
          double valor = deb;
          int pos = Nome[i].pos;
          Nome[i].extrato[pos].existe = pos;
          Nome[i].pos = Nome[i].pos + 1;
          if (Nome[i].extrato[pos].existe >= 99) {
            for (int x = 1; x < 100; x++) {
              Nome[i].extrato[x].existe = Nome[i].extrato[x].existe - 1;
            }
          }
          Nome[i].extrato[pos].valor = valor;
          Nome[i].extrato[pos].tarifa =
              (deb * tarifac); // adiciona no extrato do cliente as informações
          strcpy(Nome[i].extrato[pos].descricao, descricao);
        }
      }
    }
  } else {
    printf("CPF nao encontrado!\n");
  }
}

void Deposito(Cliente Nome[]) { // função deposito
  char descricao[100];
  double dep;
  char cpf2[15];
  char senha2[100];
  printf("Digite seu CPF: ");
  fgets(cpf2, sizeof(cpf2), stdin);
  int i;
  for (i = 0; i < maxclientes; i++) { // verifica se o cpf é existente
    if (Nome[i].existe == 1) {
      int comp = strcmp(cpf2, Nome[i].cpf);
      if (comp == 0) {
        break;
      }
    }
  }
  if (i < maxclientes) {
    limpar();
    printf("Digite sua senha: ");
    fgets(senha2, sizeof(senha2),
          stdin); // verifica se a senha condiz com o cpf digitado
    int comp2 = strcmp(senha2, Nome[i].senha);
    if (comp2 == 0) {
      printf("Digite o valor que deseja depositar: ");
      scanf("%lf", &dep);
      Nome[i].vinicial = Nome[i].vinicial + dep;
      printf("Deposito realizado com sucesso!\n");
      printf("Seu valor atualizado: %.2lf\n", Nome[i].vinicial);
      sprintf(descricao, "Deposito realizado.");
      double valor = dep;
      int pos = Nome[i].pos;
      Nome[i].extrato[pos].existe = pos;
      Nome[i].pos = Nome[i].pos + 1;
      if (Nome[i].extrato[pos].existe >= 99) {
        for (int x = 1; x < 100; x++) {
          Nome[i].extrato[x].existe = Nome[i].extrato[x].existe - 1;
        }
      }
      Nome[i].extrato[pos].valor = valor;
      Nome[i].extrato[pos].tarifa = 0;
      strcpy(Nome[i].extrato[pos].descricao, descricao); // adiciona no extrato
    }
  } else {
    printf("CPF nao encontrado!\n");
  }
}

void Extrato(Cliente Nome[]) { // função extrato
  char cpf2[15];
  char senha2[100];
  printf("Digite seu CPF: ");
  fgets(cpf2, sizeof(cpf2), stdin);
  int i;
  for (i = 0; i < maxclientes; i++) { // verifica se o cpf existe
    if (Nome[i].existe == 1) {
      int comp = strcmp(cpf2, Nome[i].cpf);
      if (comp == 0) {
        break;
      }
    }
  }
  if (i < maxclientes) {
    limpar();
    printf("Digite sua senha: ");
    fgets(senha2, sizeof(senha2), stdin);
    int comp2 = strcmp(
        senha2, Nome[i].senha); // verifica se a senha condiz com o cpf digitado
    if (comp2 == 0) {
      printf("\n\n");
      printf("Cliente: %s\n", Nome[i].nome);
      printf("Cpf: ¨%s\n", Nome[i].cpf);
      printf("Tipo de conta %s\n", Nome[i].conta);
      printf("\n");
      printf("----- EXTRATO -----\n");
      printf("\n");
      FILE *extratoarq =
          fopen("extratoarq.txt", "w"); // cria um arquivo para o extrato
      fprintf(extratoarq, "Cliente: %s\n", Nome[i].nome);
      fprintf(extratoarq, "Cpf: ¨%s\n", Nome[i].cpf);
      fprintf(extratoarq, "Tipo de conta %s\n", Nome[i].conta);
      fprintf(extratoarq, "\n");
      fprintf(extratoarq, "----- EXTRATO -----\n");
      fprintf(extratoarq, "\n");
      for (int e = 0; e < 100; e++) {
        if (Nome[i].extrato[e].existe >
            0) { // verifica se o extrato existe e printa o mesmo
          printf("%s\n", Nome[i].extrato[e].descricao);
          printf("Valor: %.2lf\n", Nome[i].extrato[e].valor);
          printf("Tarifa: %.2lf\n", Nome[i].extrato[e].tarifa);
          printf("\n");
          fprintf(extratoarq, "%s\n", Nome[i].extrato[e].descricao);
          fprintf(extratoarq, "Valor: %.2lf\n", Nome[i].extrato[e].valor);
          fprintf(extratoarq, "Tarifa: %.2lf\n", Nome[i].extrato[e].tarifa);
          fprintf(extratoarq, "\n"); // le as informacoes do extrato
        }
      }
      fclose(extratoarq);
    }
  }
}

void Transferencias(Cliente Nome[]) { // função tranferencia entre contas
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
  for (i = 0; i < maxclientes; i++) { // verifica se o cpf existe
    if (Nome[i].existe == 1) {
      int comp = strcmp(cpf2, Nome[i].cpf);
      if (comp == 0) {
        break;
      }
    }
  }
  if (i < maxclientes) {
    limpar();
    printf("Digite sua senha: "); // verifica se a senha condiz com o cpf
    fgets(senha2, sizeof(senha2), stdin);
    int comp2 = strcmp(senha2, Nome[i].senha);
    if (comp2 == 0) {
      printf("Digite o CPF de quem recebera a trasferencia: ");
      fgets(cpf3, sizeof(cpf3), stdin);
      int j;
      for (j = 0; j < maxclientes;
           j++) { // verifica se o cpf de quem ira receber existe
        if (Nome[j].existe == 1) {
          int comp = strcmp(cpf3, Nome[j].cpf);
          if (comp == 0) {
            break;
          }
        }
      }
      if (j < 999) {
        sprintf(nomep, Nome[j].nome);
        sprintf(nomer, Nome[i].nome);
        printf("Digite a quantidade que deseja transferir: ");
        scanf("%lf", &qtdf);
        Nome[i].vinicial = Nome[i].vinicial - qtdf; // realiza a tranferencia
        Nome[j].vinicial = Nome[j].vinicial + qtdf;
        printf("Seu valor atual: %2.lf\n", Nome[i].vinicial);
        sprintf(descricao, "Transferencia realizada para %s", nomep);
        double valor = qtdf;
        int pos = Nome[i].pos;
        Nome[i].extrato[pos].existe = pos;
        Nome[i].pos = Nome[i].pos + 1;
        if (Nome[i].extrato[pos].existe >= 99) {
          for (int x = 1; x < 100; x++) {
            Nome[i].extrato[x].existe = Nome[i].extrato[x].existe - 1;
          }
        }
        Nome[i].extrato[pos].valor =
            valor; // leva as informacoes da tranferencia para o extrato
        Nome[i].extrato[pos].tarifa = 0;
        strcpy(Nome[i].extrato[pos].descricao, descricao);
        sprintf(descricao2, "Transferencia recebida de %s", nomer);
        int pos2 = Nome[j].pos;
        Nome[j].extrato[pos2].existe =
            pos; // leva as informacoes da tranferencia para o extrato de quem
                 // recebeu
        Nome[j].pos = Nome[j].pos + 1;
        if (Nome[i].extrato[pos].existe >= 99) {
          for (int x = 1; x < 100; x++) {
            Nome[i].extrato[x].existe = Nome[i].extrato[x].existe - 1;
          }
        }
        Nome[j].extrato[pos2].valor = valor;
        Nome[j].extrato[pos2].tarifa = 0;
        strcpy(Nome[j].extrato[pos2].descricao, descricao2);
      } else {
        printf("CPF do recebidor não encontrado!\n");
      }
    }
  } else {
    printf("CPF nao encontrado!\n");
  }
}

int lerarquivo(Cliente Nome[], char nomearq[]) { // função de ler o arquivo
  FILE *registroarq = fopen(
      nomearq, "rb"); // le o arquivo e escreve em binarios na arqclientes.txt
  if (registroarq == NULL) {
    return 1;
  }
  fread(&Nome, sizeof(Cliente), maxclientes, registroarq);
  fclose(registroarq); // fecha o arquivo
  return 0;
}
