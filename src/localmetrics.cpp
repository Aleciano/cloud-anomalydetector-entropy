#include <stdio.h>
#include <ctype.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio_ext.h> //__fpurge(stdin)
#include "filaEncShortInt.h"
#include "filaEncDouble.h"
#include <math.h>
#include <time.h>
#define sleep_time 3

#define CPU 0
#define MEM 1

int vQtd(TFilaEncShortInt *fila);
int eiQtd(TFilaEncShortInt *fila);
double entropiaMonitorSample(TFilaEncShortInt *fila);
//char escolha_chr(char op1, char op2, char op3);

/* 
* O programa recebe como parâmetros, o número de "bins"(m) a ser
* utilizado e o "range" (r), respectivamente.
*/
int main(int argc, char **argv){
	system("clear");
	
	FILE *fp;
	
	short int j=0; 
	short int m, r, window, analysis_time, n_metrics;
	//char opcao_char;
	
	TFilaEncShortInt event;
	TFilaEncDouble metrics;
	
	TFilaEncShortInt *pev = &event; /* TAD que manipula um vetor dinâmico com informações
									* dos M-events criados. */
	TFilaEncDouble *pme = &metrics; /* TAD que manipula um vetor dinâmico com informações
									das métricas obtidas. */
	
	time_t beginTime,endTime; /* Manipulação do tempo. */
	struct tm * timeinfo;	/* Estrutura para obtenção de tempo local.*/
	
	glibtop_cpu cpu; /* TAD da libgtop com informações de CPU.*/
	glibtop_mem memory; /* TAD da libgtop com informações de Memória Principal.*/
	
	if (argc > 6) {
		window = atoi(argv[1]);
		analysis_time = atoi(argv[2]);	
		m = atoi(argv[3]);
		r = atoi(argv[4]);
		// nothing
		if(argv[5]) n_metrics = atoi(argv[5]);
		else n_metrics = 2;
		printf("\tUtilizando os seguintes parâmetros\nwindow: %d\nanalysis_time: %d min\nm: %d\nr: %d\nn_metrics: %d\nArquivo de log: %s\n",window,analysis_time,m,r,n_metrics,argv[6]);	
		/*opcao_char=escolha_chr('Y','N','\0'); // Ler opção do menu
							if(opcao_char=='N'){ return 1;
							}*/
	}
	else{
		printf("\n\tPrecisa dos seguintes parâmetros respectivamente: <tamanho da janela> <tempo de análise (min)> <m> <r> <métricas à utilizar> <local para salvar log>\n\n");
		return 1;
	}
	
	time(&beginTime);
	timeinfo = localtime(&beginTime);
	
	fp = fopen(argv[6], "w+");
	/* teste de abertura do arquivo */
	if(!fp) { printf("\t\terro ao abrir arquivo de log\n"); exit(1);}
	fprintf(fp,"#################################################\n#Log gerado em: %s\n#\n#\tParâmetros utilizados\n# Janela = %d\n# Tempo = %d min\n# m = %d\n# r = %d\n# Nº de métricas = %d\n#\n# Tempo\tEntropia\n",asctime(timeinfo),window,analysis_time,m,r,n_metrics);
	
	unsigned long cpu_buf[2]={0,0}; /* Valores de CPU (ou múltiplas) capturados em duas leituras */
	/* para testes */
	short int a,b; 
	
	/* fim de para testes */
	/* Atribuindo valores com base em argumentos passados na chamada ao programa*/
		
	criarFilaShortInt(pev,window,n_metrics);
	criarFilaDouble(pme,window,n_metrics);
	beginTime = time(NULL);
	endTime = beginTime;
	
	/* Laço de coleta das métricas e cálculo de entropia*/
	while((endTime-beginTime)/60<analysis_time){
	
	
	cpu_buf[0] = 0;
	cpu_buf[1] = 0;
	glibtop * sys_ref=glibtop_init(); 
	glibtop_get_cpu(&cpu);
		
	/* Início de coleta das métricas */
	printf("\nTempo %ld s\n",endTime-beginTime);
		
	/* Leitura da CPU das múltiplas CPUs (momento 1)*/	
	for(j=0; j<=sys_ref->ncpu; j++){
		cpu_buf[0] += ((unsigned long)cpu.xcpu_total[j] - (unsigned long)cpu.xcpu_idle[j]);	
			
	}
	sleep(sleep_time);
	printf("\n");
	glibtop_get_cpu(&cpu);
	glibtop_get_mem(&memory);
	
	/* Leitura da CPU das múltiplas CPUs (momento 2)*/	
	for(j=0; j<=sys_ref->ncpu; j++){
		cpu_buf[1] += ((unsigned long)cpu.xcpu_total[j] - (unsigned long)cpu.xcpu_idle[j]);	
			
	}
	/* O segundo parâmetro complicado é na verdade o valor médio das múltiplas CPUs
	* no intervalo de tempo (subtração das duas leituras)
	*/	
	if(!enfileirarDouble(pme, ((((double)(cpu_buf[1]-cpu_buf[0])/((sys_ref->ncpu)+1))/cpu.frequency)/sleep_time)*100, CPU)){
		printf("\t erro no enfileiramento de CPU\n\t\tSaindo.."); /* Valor percentual de CPU */
		return 1;
	}
	if(!enfileirarDouble(pme, ((double)memory.used/(1024*1024)), MEM)){
		printf("\t erro no enfileiramento de MEM\n\t\t"); /* Valor em MB de Memória Principal */
		return 1;
		}
	
	/* Fim de coleta de métricas */
	
	/* Início de inserção de valores "bin" */	
	//printf("\n\t\tagora\n");scanf("%hi",&a); scanf("%hi",&b);	
	enfileirarShortInt(pev, (short int)abs((ultimoElementoDouble(pme, CPU)/mediaDouble(pme, CPU))/(r/(double)m))/*a*/, CPU); // CPU
	enfileirarShortInt(pev, (short int)abs((ultimoElementoDouble(pme, MEM)/mediaDouble(pme, MEM))/(r/(double)m))/*b*/, MEM); //MEM
	
	/* Adiciona valores de entropia no arquivo de texto.*/	
	fprintf(fp,"%ld\t%f\n",endTime-beginTime,(double)entropiaMonitorSample(pev));
	
	/* Atualiza o tempo decorrido */
	endTime = time (NULL);
	
	fflush(fp); /* Gravar buffer no arquivo */
	printf("\tCPU\t\tMEM\n");
	if(!imprimirFilaDouble(pme)) printf("\n\tErro na impressão visse?");
	} //end-while
	
	fclose(fp);
	
	desalocaTudo(pme);
	desalocaTudo(pev);
	return 0;

	}
/*
* Função que calcula a entropia do determinado momento da janela
* de observação.
* A entropia é calculada mesmo que a janela só tenha o seu primeiro valor.
*/

double entropiaMonitorSample(TFilaEncShortInt *fila){

	double he = 0; /* Entropia */
	int ni = eiQtd(fila);
		
	int v = fila->tam;	
	v -= vQtd(fila); /* Tamanho do somatório considerando que v!=n quando há valores repetidos. */
	
	for(int i=0; i<v ; i++){
		he += ((double)ni/fila->tam)*log10((double)ni/fila->tam);
		
	}
		
	return fabs(he); //Absoluto
}

/*
* Quantidade de valores (ei) dentro do vetor.
*/


int vQtd(TFilaEncShortInt *fila){
	int v=0;
	int i,j,k;
	int proximo=0;
	short int achou; //boolean	
	short int dado;
	short int marcador[fila->tam];
	if(fila->tam < 2) { return 1;} //Situação em que o tamanho da fila não permite o cálculo do vQtd.	
	
	nofilashortintenc *aux=fila->frente;
	nofilashortintenc *aux_topo=fila->frente;
	nofilashortintenc *aux_pesquisa=fila->frente;
	nofilashortintenc *aux_pesquisa_topo=fila->frente;
	
	for(k=0;k<fila->tam;k++) { marcador[k] = -1 ; }
	
	for(i=0;i<fila->tam;i++){ //geral da fila
		achou=0;		
		for(k=0;k<fila->tam;k++){ //busca por coluna já marcada.
			if((i) == marcador[k]) achou = 1 ;
		}		
		if(!achou){ //livre, pode iniciar a procura.
			aux_pesquisa_topo = aux_pesquisa = aux->prox; //pesquisar da coluna de aux para frente.
			for(k=0;k<fila->tam-i-1;k++){ //laço de pesquisa individual de cada coluna do laço geral da fila.				
				j=0;
				dado = aux->elemento;	
				while(aux_pesquisa!=NULL && aux_pesquisa->elemento==dado){
		
					j++;
					aux = aux->baixo;
					dado = (aux) ? aux->elemento : -1 ; //-1 não indica nada em especial.
					aux_pesquisa = aux_pesquisa->baixo;
				}		
				if(j/fila->linhas){
					v++;
					marcador[proximo++] = i + k +1; //marca a coluna k como repetente.							
				}			
				aux = aux_topo; //volta ao topo da mesma coluna i
				aux_pesquisa_topo = aux_pesquisa_topo->prox;
				aux_pesquisa = aux_pesquisa_topo;	 		
			}	
		}
		//v+=(j/fila->linhas);
		aux_topo=(aux_topo)->prox;	
		aux=aux_topo;
			
	}
	 
	return v;			
}

int eiQtd(TFilaEncShortInt *fila){
	int ei=0,i,j;	
	short int dado;
	if(filaVaziaShortInt(fila)) return 0;	
	
	nofilashortintenc *aux=fila->frente;
	nofilashortintenc *aux_topo=fila->frente;
	
	

	for(i=0;i<fila->tam;i++){
		j=0;
		dado=ultimoElementoShortInt(fila, j);		
		while(aux!=NULL && aux->elemento==dado){
			
			j++;
			dado=ultimoElementoShortInt(fila, j);
			aux=aux->baixo;	
		}			
		ei+=(j/fila->linhas);
		aux_topo=(aux_topo)->prox;	
		aux=aux_topo;
	}
	return ei;			
}

char escolha_chr(char op1, char op2, char op3){
	char retorno;
	if(op3=='\0') op3='s';
	do{
	__fpurge(stdin);
	retorno=getchar();
	
	if(toupper(retorno)==op1 || toupper(retorno)==op2 || toupper(retorno)==op3)	
		return toupper(retorno);
	else
		printf("\nOpção inválida! Tente novamente.\n");
	}while(retorno!=op1 && retorno!=op2 && retorno!=op3);
}
