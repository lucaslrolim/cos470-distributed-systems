# Trabalho 3 Sistemas Distribuídos Anotações


## RMI

Implementação básica de RMI *(Remote Method Invocation)* de acordo com as especificações propostas no documento **T3.pdf**. Para o desenvolvimento foi utilizado Java 8, a IDE Netbeans e o ambiente Linux Ubuntu 16.

## Execução do programa

Para executar o programa, em primeiro lugar, deve-se acessar por meio do terminal o diretório no qual os arquivos foram extraídos e executar o servidor por meio do seguinte comando:


    java Server

Feito isso, a mensagem *"server started"* será exibida, comprovando que o comando funcionou e o servidor já está rodando. Após visualizar a referida mensagem, o usuário deve utilizar o comando Ctrl+Shift+T, abrindo uma nova aba no terminal, e executar o cliente por meio do seguinte comando:


    java Client function argument

*Todas as funções são aplicadas em um vetor de tamanho N = 10⁸, preenchido de forma aleatória, como consta na especificação do trabalho*

| Função                                                                                                                   | function | argument                                                                                          |
| ------------------------------------------------------------------------------------------------------------------------ | -------- | ------------------------------------------------------------------------------------------------- |
| Retorna um vetor em que todos os elementos são os elementos gerados no vetor N elevados a potência fornecida em argument | 0        | Indica a potência que o número será elevado                                                       |
| Retorna um vetor em que todos os elementos são os logaritmos na base argument dos elementos gerados no vetor N           | 1        | Indica a base do logaritmo a ser utilizada                                                        |
| Retorna um vetor em que todos os elementos são os elementos gerados no vetor N multiplicados por argument                | 2        | Indica o fator multiplicativo                                                                     |
| Retorna a soma de todos os elementos do vetor N gerado                                                                   | 3        | argument = 0 indica a soma dos elementos de forma normal

argument = 1 realiza a soma dos módulos |
| Retorna a norma do vetor N gerado                                                                                        | 4        | Indica a norma a ser utilizada                                                                    |
| Retorna as extremidades do intervalo de valores do vetor N                                                               | 5        | argument = 1 retorna o maior valor

argument = 0 retorna o menor valor                            |

----------
## Explicações sobre implementação RMI

Para a implementação desse trabalho utilizamos três arquivos java, uma interface e duas classes. A interface se dá no arquivo RMI, enquanto as classes estão nos arquivos Server e Client.

A interface RMI é utilizada para a declaração dos métodos abstratos, ao passo que o Servidor é utilizado para a definição e processamento desses métodos e o Cliente para fazer as chamadas de função.

O servidor cria objetos remotos e faz referências a esses objetos disponíveis. Em seguida, ele é válido para clientes invocarem seus métodos sobre os objetos. O cliente executa referências remotas aos objetos remotos no servidor e invoca métodos nesses objetos remotos.

Funções do servidor RMI são fornecidos pela classe RemoteObject e suas subclasses Remote Server, Activatable e UnicastRemoteObject.  Para criarmos o nosso Servidor estendemos da classe RemoteObject, criando assim um objeto remoto, e implementamos o tipo RMI.  Outro ponto importante é que todas as chamadas de função dentro do servidor precisam possuir um tratamento de exceção, o que é feito por meio do uso da classe RemoteException.

Por fim, para a implementação do software, utilizamos um servidor local e a porta 8083 *(escolhida ao acaso)*.

