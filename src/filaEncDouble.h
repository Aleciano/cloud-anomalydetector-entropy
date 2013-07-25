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
*	
*/
typedef struct nofiladouble{
	double elemento; 	/* Elemento guardado na estrutura*/
	struct nofiladouble *prox; /* Ponteiro para o pr�ximo valor na pr�xima posi��o */
	struct nofiladouble *baixo; /* Ponteiro para o valor de baixo na mesma posi��o */
} nofiladoubleenc;


typedef struct cabecaDouble{
		nofiladoubleenc *frente; /* Elemento da primeira posi��o da fila e do topo,
				 			*equivalente a [0][0] */
		nofiladoubleenc *fim; /* Elemento da �ltima posi��o*/
		int colunas;
		int linhas;
        int tam;      
        } TFilaEncDouble;

//Fun��o que cria uma fila  vazia      
void criarFilaDouble(TFilaEncDouble *fila, int colunas, int linhas);

//Verifica se a fila est� vazia ou n�o
int filaVaziaDouble(TFilaEncDouble *fila);

//Verifica se a fila esta cheia ou n�o
int filaCheiaDouble(TFilaEncDouble *fila);

//Coloca elementos na fila(fim dela).
//O fim da fila s� � atualizado e esta �ltima coluna estiver
//totalmente preenchida com todas as linhas.
int enfileirarDouble(TFilaEncDouble *fila, double dado, int linha);

//Retirar os elementos da frente da fila(andar)
// SEM USO AGORA
//int desenfileirarDouble(TFilaSeqCircDouble *fila, double *dado, int linha);

//Imprime os elementos da fila na ordem correta.
int imprimirFilaDouble(TFilaEncDouble *fila);

/* Responde com o elemento que est� na frente da fila e na linha informada. */
int consultarPrimeiroDouble(TFilaEncDouble *fila, int linha, double *dado);

// D� a m�dia dos valores da referida linha da fila
double ultimoElementoDouble(TFilaEncDouble *fila, int linha);

//Retorna a m�dia dos dados na linha informada.
double mediaDouble(TFilaEncDouble *fila, int linha);

int ultimoElementoDouble(TFilaEncDouble *fila, int linha, double *dado);

nofiladoubleenc * alocaDouble();

//Limpa toda a matriz de elementos.
int desalocaTudo(TFilaEncDouble *fila);
