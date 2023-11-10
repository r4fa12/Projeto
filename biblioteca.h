#define maxclientes 1000

typedef struct {
  char descricao[100];
  double valor;
  float tarifa;
  int existe;
} extrato;

typedef struct {
  char nome[100];
  char cpf[16];
  char conta[20];
  double vinicial;
  char senha[100];
  int existe;
  int pos;
  extrato extrato[100];
} Cliente;

void Menu();

void Novo_Cliente(Cliente Nome[]);

void Apagar_Clientes(Cliente Nome[]);

void Listar_Clientes(Cliente Nome[]);

void Debito(Cliente Nome[]);

void Deposito(Cliente Nome[]);

void Extrato(Cliente Nome[]);

void Transferencias(Cliente Nome[]);

void limpar();

int lerarquivo(Cliente Nome[], char nomearq[]);

int criararquivo(Cliente Nome[], char nomearq[]);
