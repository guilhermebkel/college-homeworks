//---------------------------------------------------------------------
// Arquivo      : geracarga.c
// Conteudo     : gerador de carga para o simulador de poquer
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2022-05-31 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <getopt.h>
#include "msgassert.h"

const double DBL_EPS_COMP = 1 - DBL_EPSILON; 

#define MAXJOGADORES 12
#define MINJOGADORES 2

char naipes[5]="PECO";

double RandU() 
// Descricao: gera um numero aleatorio (distribuicao uniforme) entre 0 e 1
// Entrada: nenhuma
// Saida: numero aleatorio
{
    return DBL_EPSILON + ((double) rand()/RAND_MAX);
}

double RandN2(double mu, double sigma) 
// Descricao: gera um numero aleatorio 
//            (distribuicao normal, media mu e variancia sigma)
// Entrada: mu e sigma
// Saida: numero aleatorio
{
  return mu+(rand()%2?-1.0:1.0)*sigma*pow(-log(DBL_EPS_COMP*RandU()),0.5);
}

double RandN() 
// Descricao: gera um numero aleatorio 
//            (distribuicao normal, media 0 e variancia 1)
// Entrada: nenhuma
// Saida: numero aleatorio
{
    return RandN2(0, 1.0);
}

// estrutura de dados que contem os parametros
typedef struct prm{
  char nomesaida[1000];
  int rodadas;
  double jogadores, varjogadores;
} prmGeracao;

// estrutura de dados que contem os parametros do servidor
typedef struct jog{
  char nome[1000];
} Jogador;

void uso()
// Descricao: imprime as instrucoes de uso do programa
// Entrada:  N/A
// Saida: instrucoes
{
  fprintf(stderr,"geracarga\n");
  fprintf(stderr,"\t-o <arq>\t(arquivo de saida) \n");
  fprintf(stderr,"\t-r <num>\t(numero de rodadas)\n");
  fprintf(stderr,"\t-j <num>\t(jogadores por rodada)\n");
  fprintf(stderr,"\t-v <num>\t(variancia jogadores)\n");
  fprintf(stderr,"\t-h\t(opcoes de uso)\n");
}

void parse_args(int argc,char ** argv, prmGeracao * prm)
// Descricao: analisa a linha de comando a inicializa variaveis
// Entrada: argc e argv
// Saida: prm
{
     extern char * optarg;
     extern int optind;
     int c ;
     // valores padrao
     prm->nomesaida[0] = 0;
     prm->rodadas = 10;
     prm->jogadores = 4;
     prm->varjogadores = 1;
     // percorre a linha de comando buscando identificadores
     while ((c = getopt(argc, argv, "o:r:j:v:h")) != EOF)
       switch(c) {
         case 'o':
	          // arquivo de saida
	          strcpy(prm->nomesaida,optarg);
                  break;
         case 'r':
	          // numero de rodadas
	          prm->rodadas = atoi(optarg);
		  break;
         case 'j':
	          // numero medio de jogadores
	          prm->jogadores = atof(optarg);
		  break;
         case 'v':
	          // variancia de jogadores
	          prm->varjogadores = atof(optarg);
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
       // verifica apenas o nome do arquivo de saida
       erroAssert(prm->nomesaida[0],"Arquivo de saida nao definido.");
}

void gerapalavra(int tam, char * ret)
// Descricao: gera uma palavra aleatoria 
// Entrada: tam
// Saida: ret
{
  int i;
  for (i=0; i<tam; i++){
    ret[i] = (char)(rand()%26)+'a';
  }
  ret[tam] =0;
}




int main(int argc, char ** argv){
  int i,j,k,tampal,retclose;
  int carta, naipe, numjogadores, aposta, numcartas;
  prmGeracao prm;
  long cartabmp;
  char auxstr[1000];
  FILE * out;
  Jogador jvet[MAXJOGADORES];

  parse_args(argc,argv,&prm);

  out = fopen(prm.nomesaida,"wt");
  erroAssert(out!=NULL,"Erro no fopen");

  // inicializa o vetor de jogadores
  for (i=0; i<MAXJOGADORES; i++){
    // nome do jogador
    tampal = (int) RandN2(10.0,2.0);
    tampal=(tampal<3?3:tampal);
    gerapalavra(tampal,auxstr); 
    strcpy(jvet[i].nome,auxstr);
  }

  fprintf(out,"%d 1000\n",prm.rodadas);
  // gera carga de trabalho
  for (i=0; i<prm.rodadas; i++){
    // sorteia numero de jogadores
    numjogadores = (int) RandN2(prm.jogadores,prm.varjogadores);
    numjogadores = (numjogadores>=MINJOGADORES? numjogadores: MINJOGADORES);
    numjogadores = (numjogadores<=MAXJOGADORES? numjogadores: MAXJOGADORES);
    fprintf(out,"%d 50\n",numjogadores);
    // para cada jogador
    for (j=0; j<numjogadores; j++){
      aposta= (rand()%250)+50;
      fprintf(out,"%s %d",jvet[j].nome,aposta);
      // cartas do jogador 
      cartabmp=0;
      numcartas=0;
      while (numcartas<5){
	carta = rand()%52;
        if (carta & cartabmp){
	  // ja gerou a carta
	} else {
          cartabmp = cartabmp | (1<<carta);
	  fprintf(out," %d%c",carta%13,naipes[(int)(carta/13)]);
	  numcartas++;
	}
      }
      fprintf(out,"\n");
    }
  }
  retclose = fclose(out);
  erroAssert(retclose==0,"Erro no fclose");
  return 0;
}
