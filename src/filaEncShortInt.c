/*
Arquivo com a execução das funções
*/

#include<stdlib.h>
#include<stdio.h> //RODAR EM LINUX
#include "filaEncShortInt.h" 

void criarFilaShortInt(TFilaEncShortInt *fila, int colunas, int linhas){
    fila->frente=fila->fim=NULL;      
    fila->tam=0;
	fila->colunas=colunas;
	fila->linhas=linhas;
}

int filaVaziaShortInt(TFilaEncShortInt *fila){
    if(fila->tam==0)  
       return 1; //retorna 1 para fila VAZIA.
    return 0;
}

int filaCheiaShortInt(TFilaEncShortInt *fila){
    if(fila->tam==fila->colunas)
      return 1; //retorna 1 para fila CHEIA.
    return 0;
}

int enfileirarShortInt(TFilaEncShortInt *fila, short int dado, int linha){ 
	nofilashortintenc *aux;  
	int i,j;  
		
	/* If principal */
	if(filaVaziaShortInt(fila)){
		/* Alocando um novo nofiladoubleenc */
		nofilashortintenc * novo = alocaShortInt();
		if (!novo) return 0;
		novo->elemento = dado;
		novo->prox = NULL;
		novo->baixo = NULL;
		if(fila->frente==NULL) { /* "Vazia" e sem elementos na 1ª coluna..*/
			fila->frente = novo; /* Primeira inserção */
			//fila->fim = novo;
					
		}
		else{					/* "Vazia" e com elementos na 1ª coluna... */	
			aux=fila->frente; 
			while(aux->baixo!=NULL)
				aux = aux->baixo;
			aux->baixo = novo;
		}
		/* Código comum a ambas as inserções*/		
		if((linha+1)==fila->linhas){
				fila->fim = fila->frente;
				fila->tam++;	
		}
	} /* Fim do If principal */
	
	/* Else principal */
	else{	/* Se não vazia*/
		if(filaCheiaShortInt(fila) ){ /* Se não vazia e já completa! */ 
			if((fila->fim)->prox==NULL){
				aux = fila->frente;
			}
			else{
				aux = (fila->fim)->prox;
				}
			i = 0;
			while(i<linha){
				aux = aux->baixo; i++; }
			aux->elemento = dado;
			
			if((linha+1)==fila->linhas){
					if((fila->fim)->prox==NULL) fila->fim = fila->frente;
					else fila->fim = (fila->fim)->prox;		
			}
		}
		else{
			/* Alocando um novo nofiladoubleenc */
			nofilashortintenc * novo = alocaShortInt();
			if (!novo) return 0;
			novo->elemento = dado;
			novo->prox = NULL;
			novo->baixo = NULL;			
			if((fila->fim)->prox==NULL){ /* Coluna nova (matriz em preenchimento)*/
				(fila->fim)->prox=novo;		
				//fila->fim=novo;
			}
			else{				/* Coluna já com alguns itens (matriz em preenchimento).*/
				aux = (fila->fim)->prox; 
				i = j = 0;
				while(aux->baixo!=NULL){
					aux = aux->baixo;
					i++; 
				}
				aux->baixo = novo;
				/* Ligando o elemento da coluna anterior, mesma linha, ao novo.*/				
				aux=fila->fim;
				do{
					aux = aux->baixo;
				}while(j<i);
					
				aux->prox = novo; /* Será redundante algumas vezes...*/
			}
			/* Situação em que a coluna foi totalmente preenchida */
			if((linha+1)==fila->linhas){
				(fila->tam++);
				fila->fim=(fila->fim)->prox;
				
			}		
		}
	} /* Fim do Else principal */
	
	
    return 1; //SUCESSO NA INSERÇÃO!!  
}
/*
int desenfileirarShortInt(TFilaEncShortInt *fila, short int *dado, int linha){
    if(filaVaziaShortInt(fila))
		return 0; //Não se pode andar uma fila que está vazia!
	fila->tam--;
	*dado=fila->elementos[linha][fila->frente];
	fila->frente=(fila->frente+1) % POSICOES;
	return 1;
}
*/

/* IMPRIMIR EM ARQUIVO (falta concluir)*/

int imprimirFilaShortInt(TFilaEncShortInt *fila){
     nofilashortintenc * aux_topo, * aux_linhas;
     if(filaVaziaShortInt(fila)) return 0;
     int i = 0;
     aux_topo = aux_linhas = fila->frente;
     while(i<fila->tam){
		 if(aux_topo==fila->fim) printf(">");
		 printf("[ ");
		 do{
		 	printf(" %d | ",aux_linhas->elemento);
		 	aux_linhas=aux_linhas->baixo;
		 }while(aux_linhas!=NULL);
		 aux_topo = aux_linhas = aux_topo->prox;
		 printf(" ] \n"); 	
		 i++;
		
	}
	printf("\n");	
	return 1;
}


/*
int consultarPrimeiroShortInt(TFilaEncShortInt *fila, int linha, double *dado){
	int i=0;	
	nofiladoubleenc *aux;
	if(filaVaziaShortInt(fila) || (linha+1)>fila->linhas)
		return 0; 
	aux=fila->frente;	
	/* Avançando até a linha desejada *	
	while(i<linha){
		aux=aux->baixo;
		i++;	
	}	
	*dado=aux->elemento;
	return 1;
}

short int mediaShortInt(TFilaEncShortInt *fila, int linha){
	double soma=-1;	
	int i=0;	
	nofilashortintenc *aux;
	if(filaVaziaShortInt(fila) || (linha+1)>fila->linhas)
		return soma;	
	aux = fila->frente;
	soma = 0;
	/* Avançando até a linha desejada *
	while(i<linha){
		aux = aux->baixo;
		i++;
	}
	do{
		soma += aux->elemento;
		aux = aux->prox;
	}while(aux!=NULL);
	
	return soma/fila->tam;
}
*/

short int ultimoElementoShortInt(TFilaEncShortInt *fila, int linha){
	nofilashortintenc *aux;
	int i=0;
	if(filaVaziaShortInt(fila) || (linha+1)>(fila->linhas)){
		return 0; }
	aux=fila->fim;
	/* Avançando até a linha desejada */	
	while(i<linha){
		aux=aux->baixo;
		i++;	
	}	
	return aux->elemento;
	

}

nofilashortintenc * alocaShortInt(){
	return ( (nofilashortintenc*) malloc (sizeof(nofilashortintenc)));
}

int desalocaTudo(TFilaEncShortInt *fila){
	nofilashortintenc * aux_save, * aux_free;
	if(filaVaziaShortInt(fila)) return 0;
	int i = 0;
	
	while(i<fila->tam){
	 	aux_free = aux_save = fila->frente;
		fila->frente=(fila->frente)->prox;
	 	while(aux_free!=NULL){
	 		aux_save = aux_save->baixo;
			free(aux_free); printf(" * ");
			aux_free = aux_save;
			
		}
	 	i++;
	 } 
	printf("\n");
	return 1;
}
