/*
Arquivo com protótipos das funções

*/

//#define POSICOES 20 
//#define LINHAS 2

																			
/*																		*/
/* ESTA ESTRUTURA DE DADOS FOI ADAPTADA PARA O USO ATUAL.
*
* A organização desta estrutura é como uma matriz, contendo quantas linhas
* e quantas colunas forem desejadas.
*
* A inserção é coluna por coluna.
* Se implementada a alteração da quantidade de linhas e colunas depois de inicializada
* a matriz, será necessário resetá-la ou alterar a inserção para que faça o que for
desejado em termos de inserção nas novas linhas/colunas criadas.
*/
typedef struct nofilashortint{
	short int elemento; 	/* Elemento guardado na estrutura*/
	struct nofilashortint *prox; /* Ponteiro para o próximo valor na próxima posição */
	struct nofilashortint *baixo; /* Ponteiro para o valor de baixo na mesma posição */
} nofilashortintenc;


typedef struct cabecashortint{
		nofilashortintenc *frente; /* Elemento da primeira posição da fila e do topo,
				 			*equivalente a [0][0] */
		nofilashortintenc *fim; /* Elemento da última posição*/
		int colunas;
		int linhas;
        int tam;      
        } TFilaEncShortInt;

//Função que cria uma fila  vazia      
void criarFilaShortInt(TFilaEncShortInt *fila, int colunas, int linhas);

//Verifica se a fila está vazia ou não
int filaVaziaShortInt(TFilaEncShortInt *fila);

//Verifica se a fila esta cheia ou não
int filaCheiaShortInt(TFilaEncShortInt *fila);

//Coloca elementos na fila(fim dela).
//O fim da fila só é atualizado e esta última coluna estiver
//totalmente preenchida com todas as linhas.
int enfileirarShortInt(TFilaEncShortInt *fila, short int dado, int linha);

//Retirar os elementos da frente da fila(andar).
// SEM USO AGORA
//int desenfileirarShortInt(TFilaEncShortInt *fila, double *dado, int linha);

//Imprime os elementos da fila na ordem correta.
int imprimirFilaShortInt(TFilaEncShortInt *fila);

/* Responde com o elemento que está na frente da fila e na linha informada. */
int consultarPrimeiroShortInt(TFilaEncShortInt *fila, int linha, short int *dado);

// Dá a média dos valores da referida linha da fila
short int mediaShortInt(TFilaEncShortInt *fila, int linha);

/* Retorna 1 para uma operação de sucesso e 0 para alguma problema */
/* Se tudo OK, o parâmetro dado é alterado com o valor solicitado. */

short int ultimoElementoShortInt(TFilaEncShortInt *fila, int linha);

nofilashortintenc * alocaShortInt();

//Limpa toda a matriz de elementos.
int desalocaTudo(TFilaEncShortInt *fila);
