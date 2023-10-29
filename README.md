# Projeto

Projeto Banco em C

Este banco foi criado com o intuito de realizar as operações descritas abaixo entre os clientes que cadastraram suas contas neste mesmo sistema.

O código desenvolvido apresenta um total de 7 operações/funções que são apresentadas no menu principal assim que o código começa a rodar, sendo essas operações/funções:

Novo Cliente: cadastra um novo cliente no banco, colocando informações com nome, cpf, senha, qual tipo de conta o cliente irá criar（comum ou plus) e o valor inicial da conta. Essas informações serão armazenadas em um arquivo de Extrato e em outro arquivo de informações gerais.

Apaga Cliente: apaga um cliente a partir do cpf e da senha em que cadastraram suas contas no banco.

Listar Clientes: lista todos os clientes já cadastrados no banco, exibindo suas informações como nome, cpf, tipo de conta e o valor presente na conta.

Debito: debita um valor da conta do cliente, sendo necessário informar o cpf, senha e o valor que será debitado. É válido ressaltar que o tipo de conta interfere nessa operação, pois caso o cliente possua uma conta do tipo comum será cobrada uma taxa de 5% a cada débito realizado. Caso o cliente possua uma conta do tipo plus será cobrada uma taxa de 3% a cada débito realizado.

Deposito: deposita um valor na conta do cliente a partir do cpf e informando qual valor será depositado.

Extrato: apresenta o histórico de todas as operações realizadas pela conta informada.

Transferencia: pede-se o cpf e a senha da conta que irá realizar a tranferência, e o cpf da conta que irá receber essa tranferência.

Lembrando que em todas as operações é verificado se as informações como cpf e senha estão corretas, já que há um arquivo geral com todas essas informações, portanto se o cpf ou senha informados não estiverem nesse arquivo a operação será cancelada e o usuário será encaminhado para o menu principal.

Integrantes do grupo:
Rafael Takahagi Mendes (RA: 24.123.050-7)
Pedro Henrique Ferreira Valim (RA: 24.123.048-1)
Gustavo Mendes Franco Lapin Atui (RA: 24.123.072-1)
