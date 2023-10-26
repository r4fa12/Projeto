typedef struct{
    char descricao[100];
    double valor;
    float tarifa;
    int existe;
}extrato;

typedef struct{
    char nome[100];
    char cpf[16];
    char conta[20];
    double vinicial;
    char senha[100];
    int existe;
    int pos;
    extrato extrato[100];
}Cliente;

void Menu();

void Novo_Cliente();

void Apagar_Clientes();

void Listar_Clientes();

void Debito();

void Deposito();

void Extrato();

void Transferencias();

void limpar();

int lerarquivo();

int criararquivo();

int criararquivoext();