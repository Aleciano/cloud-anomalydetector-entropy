/*
Arquivo com prot�tipos das fun��es

*/

//#define POSICOES 20 
//#define LINHAS 2

																			
/*																		*/
/* ESTA ESTRUTURA DE DADOS FOI ADAPTADA PARA O USO ATUAL.
*
* A organiza��o desta estrutura � como uma matriz, contendo quantas linhas
* e quantas colunas forem desejadas.
*
* A inser��o � coluna por coluna.
* Se implementada a altera��o da quantidade de linhas e colunas depois de inicializada
* a matriz, ser� necess�rio reset�-la ou alterar a inser��o para que fa�a o que for
desejado em termos de inser��o nas novas linhas/colunas criadas.
*/
typedef struct nofilashortint{
	short int elemento; 	/* Elemento guardado na estrutura*/
	struct nofilashortint *prox; /* Ponteiro para o pr�ximo valor na pr�xima posi��o */
	struct nofilashortint *baixo; /* Ponteiro para o valor de baixo na mesma posi��o */
} nofilashortintenc;


typedef struct cabecashortint{
		nofilashortintenc *frente; /* Elemento da primeira posi��o da fila e do topo,
				 			*equivalente a [0][0] */
		nofilashortintenc *fim; /* Elemento da �ltima posi��o*/
		int colunas;
		int linhas;
        int tam;      
        } TFilaEncShortInt;

//Fun��o que cria uma fila  vazia      
void criarFilaShortInt(TFilaEncShortInt *fila, int colunas, int linhas);

//Verifica se a fila est� vazia ou n�o
int filaVaziaShortInt(TFilaEncShortInt *fila);

//Verifica se a fila esta cheia ou n�o
int filaCheiaShortInt(TFilaEncShortInt *fila);

//Coloca elementos na fila(fim dela).
//O fim da fila s� � atualizado e esta �ltima coluna estiver
//totalmente preenchida com todas as linhas.
int enfileirarShortInt(TFilaEncShortInt *fila, short int dado, int linha);

//Retirar os elementos da frente da fila(andar).
// SEM USO AGORA
//int desenfileirarShortInt(TFilaEncShortInt *fila, double *dado, int linha);

//Imprime os elementos da fila na ordem correta.
int imprimirFilaShortInt(TFilaEncShortInt *fila);

/* Responde com o elemento que est� na frente da fila e na linha informada. */
int consultarPrimeiroShortInt(TFilaEncShortInt *fila, int linha, short int *dado);

// D� a m�dia dos valores da referida linha da fila
short int mediaShortInt(TFilaEncShortInt *fila, int linha);

/* Retorna 1 para uma opera��o de sucesso e 0 para alguma problema */
/* Se tudo OK, o par�metro dado � alterado com o valor solicitado. */

short int ultimoElementoShortInt(TFilaEncShortInt *fila, int linha);

nofilashortintenc * alocaShortInt();

//Limpa toda a matriz de elementos.
int desalocaTudo(TFilaEncShortInt *fila);
