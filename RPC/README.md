# RPC

Para a implementação do RPC foi utilizado o gerador de interfaces e pré compilador RPCGEN. Esse gerador de interfaces utiliza uma definição de interface para gerar arquivos modelo ser cliente, servidor e stubs.

## Instalação
    $ sudo apt-get install rpcbind
## Definição da interface
    #define N 100000000
    
    // Aqui temos o conjunto de estruturas que será utilizado para gerar os modelos e paara trocar informações pelo stub
    
    struct parameters{
            int vector[N];
            int functionParameter;
    };
    
    struct resultVector{
            int rVector[N];
    };
    
    // Conjunto de funções que poderá ser utilizada no modelo gerado por meio dessa interface
    program VEC_PROG{
            version VEC_VERS{
                    resultVector powVector(parameters) = 1;
                    resultVector shiftVector(parameters) = 2;
                    resultVector multiplyVector(parameters) = 3;
                    int sumVector(parameters) = 4;
                    int thresholdVector(parameters) = 5;
                    int edgeVector(parameters) = 6;
            } = 1;
    }=  0x23451111;
## Pré compilação e geração de modelos


    $ rpcgen -a -C vec.x
    $ make -f Makefile.vec

Os seguintes arquivos são gerados:

- Makefile.vec
- vec_client.o
- vec.h
- vec_server.o
- vec.x
- vec_client 
- vec_clnt.c 
- vec_server 
- vec_svc.c 
- vec_xdr.c 
- vec_client.c
- vec_clnt.o 
- vec_server.c
- vec_svc.o 
- vec_xdr.o
## Execução do programa

Abrir o terminal dentro da pasta do programa e executar o comando:


    $ sudo ./vec_server

E em seguida abrir outro terminal e executar o comando


    $ sudo ./vec_client localhost funcao argumentofuncao
| Função                                                                                                                           | function | argument                                                                                          |
| -------------------------------------------------------------------------------------------------------------------------------- | -------- | ------------------------------------------------------------------------------------------------- |
| Retorna um vetor em que todos os elementos são os elementos gerados no vetor N elevados a potência fornecida em argumento        | 0        | Indica a potência que o número será elevado                                                       |
| Retorna um vetor em que todos os elementos são os elementos gerados no vetor N deslocados positivamente pelo parâmetro fornecido | 1        | Indica o valor a dar ´shift´ positivo                                                             |
| Retorna um vetor em que todos os elementos são os elementos gerados no vetor N multiplicados por argument                        | 2        | Indica o fator multiplicativo                                                                     |
| Retorna a soma de todos os elementos do vetor N gerado                                                                           | 3        | argument = 0 indica a soma dos elementos de forma normal

argument = 1 realiza a soma dos módulos |
| Retorna o número de elementos no vetor gerado N que são maiores do que o parâmetro fornecido                                     | 4        | Indica o ´valor de corte´ que se deseja utilizar                                                  |
| Retorna as extremidades do intervalo de valores do vetor N                                                                       | 5        | argument = 1 retorna o maior valor

argument = 0 retorna o menor valor                            |

## Explicações sobre implementação RPC

O RPCGEN cuida de toda a complexidade de criação e configuração dos stubs, cabendo ao programador focar na estruturação do cliente e do servidor, com base nos métodos que ele mesmo definiu no modelo de interface inicial. Sendo assim, os nomes de função e os métodos usados no cliente e servidor devem ter exatamente os mesmos nomes que foram definidos no modelo de interface, pois todo código de Stubs gerado pelo RPCGEN leva isso em conta.

Visto isso, toda comunicação foi feita por meio de uma struct chamada Parameters e outra chamada rVector. A primeira struct é capaz de armazenar um array de N posições e o enviar do cliente para o servidor, a segunda, por sua vez, armazena a resposta do servidor e a retorna para o cliente.

Todos os métodos do servidor possuem a seguinte estrutura básica:


    retorno *
    nomefuncao_1_svc(parameters *argp, struct svc_req *rqstp)
    {
            static retorno  result;
            // codigo
            return &result;
    }

Em que o retorno pode ser do tipo rVector ou int.
