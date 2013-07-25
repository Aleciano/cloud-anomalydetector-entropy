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
*	
*/
typedef struct nofiladouble{
	double elemento; 	/* Elemento guardado na estrutura*/
	struct nofiladouble *prox; /* Ponteiro para o próximo valor na próxima posição */
	struct nofiladouble *baixo; /* Ponteiro para o valor de baixo na mesma posição */
} nofiladoubleenc;


typedef struct cabecaDouble{
		nofiladoubleenc *frente; /* Elemento da primeira posição da fila e do topo,
				 			*equivalente a [0][0] */
		nofiladoubleenc *fim; /* Elemento da última posição*/
		int colunas;
		int linhas;
        int tam;      
        } TFilaEncDouble;

//Função que cria uma fila  vazia      
void criarFilaDouble(TFilaEncDouble *fila, int colunas, int linhas);

//Verifica se a fila está vazia ou não
int filaVaziaDouble(TFilaEncDouble *fila);

//Verifica se a fila esta cheia ou não
int filaCheiaDouble(TFilaEncDouble *fila);

//Coloca elementos na fila(fim dela).
//O fim da fila só é atualizado e esta última coluna estiver
//totalmente preenchida com todas as linhas.
int enfileirarDouble(TFilaEncDouble *fila, double dado, int linha);

//Retirar os elementos da frente da fila(andar)
// SEM USO AGORA
//int desenfileirarDouble(TFilaSeqCircDouble *fila, double *dado, int linha);

//Imprime os elementos da fila na ordem correta.
int imprimirFilaDouble(TFilaEncDouble *fila);

/* Responde com o elemento que está na frente da fila e na linha informada. */
int consultarPrimeiroDouble(TFilaEncDouble *fila, int linha, double *dado);

// Dá a média dos valores da referida linha da fila
double ultimoElementoDouble(TFilaEncDouble *fila, int linha);

//Retorna a média dos dados na linha informada.
double mediaDouble(TFilaEncDouble *fila, int linha);

int ultimoElementoDouble(TFilaEncDouble *fila, int linha, double *dado);

nofiladoubleenc * alocaDouble();

//Limpa toda a matriz de elementos.
int desalocaTudo(TFilaEncDouble *fila);
