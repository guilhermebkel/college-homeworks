//---------------------------------------------------------------------
// Arquivo      : matop.c
// Conteudo     : programa de avaliacao do TAD MAT 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-18 - arquivo criado
//              : 2021-10-21 - estrutura de diretorios
//              : 2021-10-25 - opcoes de linha de comando 
//              : 2021-11-14 - adequacao para versao 1.1 memlog 
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h" 
#include "msgassert.h" 

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis globais para opcoes
static int opescolhida;
char lognome[100], matrix1filePath[100], matrix2filePath[100], matrixOutputFilePath[100];
int regmem;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"matop\n");
  fprintf(stderr,"\t-s \t(somar matrizes) \n");
  fprintf(stderr,"\t-m \t(multiplicar matrizes) \n");
  fprintf(stderr,"\t-t \t(transpor matriz)\n");
  fprintf(stderr,"\t-l \t(registrar acessos a memoria)\n");
  fprintf(stderr,"\t-p <arq>\t(arquivo de registro de acesso)\n");
  fprintf(stderr,"\t-o <arq>\t(caminho do arquivo da matriz resultante)\n");
  fprintf(stderr,"\t-1 <arq>\t(caminho do arquivo de definição da primeira matriz)\n");
  fprintf(stderr,"\t-2 <arq>\t(caminho do arquivo de definição da segunda matriz)\n");
}


void parse_args(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opescolhida = -1;
     matrix1filePath[0] = 0;
     matrix2filePath[0] = 0;
     matrixOutputFilePath[0] = 0;
     regmem = 0;
     lognome[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "smtp:o:1:2:lh")) != EOF)
      switch(c) {
        case 'm':
		      avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	        opescolhida = OPMULTIPLICAR;
          break;
        case 's':
          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
          opescolhida = OPSOMAR;
          break;
        case 't':
          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
          opescolhida = OPTRANSPOR;
          break;
        case 'p': 
          strcpy(lognome,optarg);
          break;
        case 'o':
          strcpy(matrixOutputFilePath,optarg);
          break;
        case '1': 
          strcpy(matrix1filePath,optarg);
          break;
        case '2': 
          strcpy(matrix2filePath,optarg);
		      break;
        case 'l': 
          regmem = 1;
		      break;
        case 'h':
        default:
          uso();
          exit(1);
      }

      // verificacao da consistencia das opcoes
      erroAssert(opescolhida>0,"matop - necessario escolher operacao");
      erroAssert(strlen(lognome)>0,"matop - nome de arquivo de registro de acesso tem que ser definido");
      erroAssert(strlen(matrixOutputFilePath)>0,"matop - o caminho do arquivo de saída da matriz resultante tem que ser definido");
      erroAssert(strlen(matrix1filePath)>0,"matop - o caminho do arquivo de entrada da matriz 1 tem que ser definido");
      
      if (opescolhida != OPTRANSPOR) {
        erroAssert(strlen(matrix2filePath)>0,"matop - o caminho do arquivo de entrada da matriz 2 tem que ser definido");
      }
}


int main(int argc, char ** argv)
// Descricao: programa principal para execucao de operacoes de matrizes 
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  mat_tipo a, b, c;

  // avaliar linha de comando
  parse_args(argc,argv);

  // iniciar registro de acesso
  iniciaMemLog(lognome);

  // ativar ou nao o registro de acesso
  if (regmem){ 
    ativaMemLog();
  }
  else{
    desativaMemLog();
  }

  // execucao dependente da operacao escolhida
  switch (opescolhida){
    case OPSOMAR:
      // cria matrizes a e b aleatorias, que sao somadas para a matriz c
      // matriz c é impressa e todas as matrizes sao destruidas
      defineFaseMemLog(0);
      leMatriz(&a, matrix1filePath, 0);
      leMatriz(&b, matrix2filePath, 1);
      criaMatriz(&c, a.tamx, a.tamy, 2);
      inicializaMatrizNula(&c);

      defineFaseMemLog(1);
      acessaMatriz(&a);
      acessaMatriz(&b);
      acessaMatriz(&c);
      somaMatrizes(&a,&b,&c);
      defineFaseMemLog(2);

      acessaMatriz(&c);
      if (regmem) imprimeMatriz(&c);
      salvaMatriz(&c, matrixOutputFilePath);
      destroiMatriz(&a);
      destroiMatriz(&b);
      destroiMatriz(&c);

      break;
    case OPMULTIPLICAR:
      // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
      // matriz c é impressa e todas as matrizes sao destruidas
      defineFaseMemLog(0);
      leMatriz(&a, matrix1filePath, 0);
      leMatriz(&b, matrix2filePath, 1);
      criaMatriz(&c, a.tamx, a.tamy, 2);
      inicializaMatrizNula(&c);

      defineFaseMemLog(1);
      acessaMatriz(&a);
      acessaMatriz(&b);
      acessaMatriz(&c);
      multiplicaMatrizes(&a,&b,&c);

      defineFaseMemLog(2);
      acessaMatriz(&c);
      if (regmem) imprimeMatriz(&c);
      salvaMatriz(&c, matrixOutputFilePath);
      destroiMatriz(&a);
      destroiMatriz(&b);
      destroiMatriz(&c);

      break;
    case OPTRANSPOR:
      // cria matriz a aleatoria, que e transposta, impressa e destruida
      defineFaseMemLog(0);
      leMatriz(&a, matrix1filePath, 0);

      defineFaseMemLog(1);
      acessaMatriz(&a);
      transpoeMatriz(&a);

      defineFaseMemLog(2);
      acessaMatriz(&a);
      if (regmem) imprimeMatriz(&a);
      salvaMatriz(&a, matrixOutputFilePath);
      destroiMatriz(&a);
	    break;
    default:
      // nao deve ser executado, pois ha um erroAssert em parse_args
      uso();
    exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}

