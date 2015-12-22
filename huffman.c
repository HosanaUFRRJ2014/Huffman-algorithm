#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"
#include "arvore.h"

#define true 1
#define false 0

#define ESQUERDA 0
#define DIREITA 1

struct {
	unsigned int bit : 1;
	
}Bit;

/*Implementação da estrutura de Huffman(código e árvore) e do algoritmo de Huffuman em si*/

//salvar nome original do arquivo também, pois pedem isso
typedef struct
{
	ARVORE *arvore;
	char codigo[TAM][TAM];

}HUFFMAN;

HUFFMAN *criarHuffman()
{
	HUFFMAN *huffman = (HUFFMAN *) malloc(sizeof(HUFFMAN));

	int i;

	if (huffman != NULL) 
	{
		for (i = 0; i < TAM; i++) 
		{
			huffman->codigo[i][0] = '\0';
		}

		huffman->arvore = NULL;
	}

	return huffman;

}

void apagarHuffman(HUFFMAN **huffman) 
{
	apagarArvore(&((*huffman)->arvore));
	free(*huffman);
	*huffman = NULL;
}



/*Algoritmo para montar a arvore de Huffman*/
void construirArvoreHuffman(HUFFMAN *huffman, char *mensagem)
{
	int i, frequencia[TAM];
	

	for (i = 0; i < TAM; i++)
	    frequencia[i] = 0;

    for (i = 0; mensagem[i] != '\0'; i++)
    {
    	frequencia[(int)mensagem[i]]++;
    	
    }

    HEAP *heap = criarHeap();

    for (i = 0; i < TAM; i++)
    {
    	if(frequencia[i] > 0)
    	{
    		NO *novo = (NO *) malloc(sizeof(NO));
            
    		novo->caractere = i;
    		novo->frequencia = frequencia[i];
    		novo->esquerda = NULL;
    		novo->direita = NULL;
    		enfileirar(heap, novo);
    	}
    }

    while(tamanhoHeap(heap) > 1)
    {
    	NO *novo = (NO *) malloc(sizeof(NO));
    	
    	novo->caractere = '#';
    	novo->esquerda = (NO *) malloc(sizeof(NO));
    	novo->direita = (NO *) malloc(sizeof(NO));
		novo->esquerda = desenfileirar(heap);
		novo->direita = desenfileirar(heap);
		novo->frequencia = novo->esquerda->frequencia + novo->direita->frequencia;
		enfileirar(heap, novo);
    }

    huffman->arvore = criarArvore();
    criarRaiz(huffman->arvore, desenfileirar(heap));
    apagarHeap(heap);



}

/*Para criar o código:*/
  /*codigo será o codigo que será criado, fim será o tamanho dele(crescerá de acordo com o numero de vezes
que a função recursiva será chamada)*/
void criarCodigoAux(HUFFMAN *huffman,NO *no, char *codigo, int fim)
{
	if(no != NULL)
	{
		if(no->esquerda == NULL && no->direita == NULL) //se é um nó folha
		{
			int i;

			for (i = 0; i <= fim; i++)
			{
				huffman->codigo[(int) no->caractere][i] = codigo[i];
			}

			huffman->codigo[(int) no->caractere][fim + 1] = '\0';
			
		}

		else
		{
			if(no->esquerda != NULL)
			{
				fim++;
				codigo[fim] = '0';
				criarCodigoAux(huffman,no->esquerda,codigo,fim);
				fim--;
			}

			if(no->direita != NULL)
			{
				fim++;
				codigo[fim] = '1';
				criarCodigoAux(huffman,no->direita,codigo,fim);
				fim--;
			}
		}
	}
	

}

//a tabela
void criarCodigo(HUFFMAN *huffman) 
{
	int tam = TAM, i;
	char *codigo = (char *) malloc(sizeof(char) * TAM);

	criarCodigoAux(huffman, huffman->arvore->raiz, codigo, -1);

}

int codificar(HUFFMAN *huffman, char *mensagem, char *codigo, int tamanho, unsigned int *codigoFinal)
{
	int i, j, codigoFim;
	codigoFim = -1;

	for (i = 0; mensagem[i] != '\0'; i++)
	{
		char *aux = huffman->codigo[(int) mensagem[i]];
		//printf("%c",mensagem[i]);

		for (j = 0; aux[j] != '\0'; j++)
		{
			codigoFim++;
			codigo[codigoFim] = aux[j];
		}
	}

	i = 0;	
	int k = 0;
	while(i < codigoFim)
	{
		unsigned int aux = 0;
		for(j = i; j < i + 32; j++)
		{
			if(codigo[j] == '0')
			{
				Bit.bit = 0;
				
			}

			if(codigo[j] == '1')
			{
				Bit.bit = 1;
				
			}

			aux = aux << 1;  //desloca 1 bit à esquerda
			aux |= Bit.bit;            //faz o ou bit a bit

		}


		codigoFinal[k] =  aux;

		k++;
		
		i = i + 32;
	}	


	return k+1;


}

//como o arrasto de bits faz com que os binarios sejam convertidos para letras,
//pegar esssas "letras" dp buffer de arquivos
//transformar para decimal (apenas ler como int)
//transformar o decimal para binário(será feita a função para isso)
//armazenar os resultados em binarios, que será o novo código
void converterParaBinario(int *buffer,char *binarios)
{
	int i = 0,j = 0,k = 0;
	unsigned int aux;


	while(buffer[k] != 0)
	{
		aux = 0;
		for (i = 31; i >= 0 ; i--)
		{
			aux = buffer[k] >> i;

			if(aux & 1)
				binarios[j] = '1';
			else
				binarios[j] = '0';

			j++;
		}

		k++;
	}

}

int decodificar(HUFFMAN *huffman, char *codigo, char *mensagem)
{
	int i, decodificacaoFim;
    decodificacaoFim = -1;

    NO *novo = huffman->arvore->raiz;

    if(novo != NULL)
    {   
    	for (i = 0; codigo[i] != '\0'; i++) 
        {
    		if (codigo[i] == '0') 
    			novo = novo->esquerda;
    				
    
    		else if (codigo[i] == '1') 
    			novo = novo->direita;
    			
    
    		else
    			return 0;
    		
    
    		if (novo->esquerda == NULL && novo->direita == NULL) //se é nó folha
    		{
    			decodificacaoFim++;

    			if(novo->caractere == '$')
    				break;

    			mensagem[decodificacaoFim] = novo->caractere;
    			novo = huffman->arvore->raiz;
    		}
        }
    
        mensagem[decodificacaoFim + 1] = '\0';
    
    	return 1;
    }

    return 0;
}



int main(int argc, char const *argv[])
{
	int i = 0,j = 0;
	HUFFMAN *huffman = criarHuffman();

	FILE *arqOrigem, *arqDestino;

    //para a compressão
    if(argv[1] != NULL && argv[2] != NULL )
	{
		printf("Comprimindo...\n");
		if((arqOrigem = fopen(argv[1],"r")) == NULL)
		{
			printf("Erro: O arquivo %s não pode ser aberto!\n",argv[1]);
			printf("Verifique se o arquivo não existe ou esta em um diretorio diferente do deste programa\n");
			exit(0);
		}

		if((arqDestino = fopen(argv[2],"wb")) == NULL)
		{
			printf("Erro: O arquivo de descompressao não pode ser aberto!\n");
			printf("Verifique se o arquivo não existe ou esta em um diretorio diferente do deste programa\n");
			exit(0);
		}

		//obter o tamanho do arquivo a ser lido em bytes
		fseek(arqOrigem, 0, SEEK_END);
		long tamanho = ftell(arqOrigem);
		rewind(arqOrigem);
		printf("\nTamanho do arquivo original: %ld bytes\n",tamanho);


	    //alocar espaço no buffer para a funcao fread
		char *vetor = (char *)malloc(sizeof(char) *(tamanho + 1)); //tamanho + 1 para o pseudo caractere
	    char *codigo = (char *) malloc(sizeof(char) * tamanho * 8); //código em bytes
        unsigned int *codigoFinal = (int *) malloc(sizeof(int) * tamanho); //armazenará o codigo pós compactação. Código em bites

        char *resultado = (char *) malloc(sizeof(char) * tamanho); //armazenará a mensagem pós descompactação

		if (vetor != NULL)
		{
			fread(vetor, sizeof(char), tamanho, arqOrigem);


		}

		else
			printf("Algo deu errado!!!\n");

		vetor[tamanho] = '$';  //colocando o pseudo caractere

		//inicio contagem de tempo
	    double comeco = (double) clock () / CLOCKS_PER_SEC;
		
		construirArvoreHuffman(huffman, vetor);
        
		criarCodigo(huffman);
        
		unsigned long long int tamCodFinal = codificar(huffman, vetor, codigo,sizeof(char) * tamanho * 8,codigoFinal);

		for (i = 0; i < 15; i++)
			fputc(argv[1][i],arqDestino);
	
        escrever_preOrdem(huffman->arvore,arqDestino);

		fwrite(codigoFinal,sizeof(int),tamCodFinal,arqDestino);

		fseek(arqDestino, 0, SEEK_END);
		long tamanho2 = ftell(arqDestino);
		rewind(arqDestino);

        //fim da contagem de tempo
		double fim = (double) clock () / CLOCKS_PER_SEC;

		printf("Tamanho do arquivo comprimido: %ld bytes\n",tamanho2);

		unsigned int taxaCompactacao = ((tamanho - tamanho2) * 100)/tamanho;

		printf("Taxa de compactacao: %d %%\n",taxaCompactacao);

		printf("Tempo gasto para a compactacao: %f segundos.\n", (fim-comeco));


	   
	}

    //para descomprimir
    else if(argv[1] != NULL && argv[2] == NULL)
    {
    	printf("Descomprimindo...\n");
    	
    	if((arqDestino = fopen(argv[1],"rb")) == NULL)
		{
			printf("Erro: O arquivo de descompressao não pode ser aberto!\n");
			printf("Verifique se o arquivo não existe ou esta em um diretorio diferente do deste programa\n");
			exit(0);
		}

    	//obter o tamanho do arquivo a ser lido em bytes
		fseek(arqDestino, 0, SEEK_END);
		long tamanho = ftell(arqDestino);
		rewind(arqDestino);

		char nomeArquivo[15]; //armazenará o nome do arquivo original gravado no comprimido
    	char *resultado = (char *) malloc(sizeof(int) * tamanho * 500); //armazenará a mensagem pós descompactação
        unsigned int *codigo = (int *) malloc(sizeof(int) * tamanho); //armazenará o codigo extraido do documento
        char *binarios = (char *) malloc(sizeof(int) * tamanho * 32); //armazenará o código que será usado

        //inicio contagem de tempo
	    double comeco = (double) clock () / CLOCKS_PER_SEC;
      
        huffman->arvore = criarArvore();

        printf("Nome do arquivo de destino da descompactacao\n");

        while(i < 15)
        {
        	nomeArquivo[i] = fgetc(arqDestino);
        	i++;
        }

        i = 0;

        while(nomeArquivo[i] != '.')
        {
        	i++;
        }
        
        nomeArquivo[i] = '2';
        nomeArquivo[i + 1] = '.';
        nomeArquivo[i + 2] = 't';
        nomeArquivo[i + 3] = 'x';
        nomeArquivo[i + 4] = 't';
        nomeArquivo[i + 5] = '\0';
        puts(nomeArquivo);

        ler_preOrdem(huffman->arvore,arqDestino);


		fread(codigo,sizeof(int),tamanho,arqDestino);

		converterParaBinario(codigo,binarios);


	    decodificar(huffman,binarios,resultado);

	    FILE *descomprimido = fopen(nomeArquivo,"w");


        i = 0;
	    while(resultado[i] != '\0')
	    {
	    	fputc(resultado[i],descomprimido);

	    	i++;

	    }

	    //fim da contagem de tempo
		double fim = (double) clock () / CLOCKS_PER_SEC;

		printf("Tempo gasto para a descompactacao: %f segundos.\n", (fim-comeco));
    }




	return 0;
}
