#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define ESQUERDA 0
#define DIREITA 1

#ifndef ARVORE_H
#define ARVORE_H

/*Implementação das funções de uma árvore binária*/

typedef struct no_ NO;
struct no_
{
    unsigned int ehFolha : 1; //para verificar se o nó é folha ou não
	unsigned int caractere : 7;
	int frequencia;
	
	NO *esquerda;
	NO *direita;
	
};

typedef struct
{
	NO *raiz;
	
}ARVORE;

ARVORE *criarArvore()
{
	ARVORE *arvore = (ARVORE *) malloc(sizeof(ARVORE));

	if (arvore != NULL)
	{
		arvore->raiz = NULL;

	}


	return arvore;
}

/*Arvore e NO, para não anular toda  arvore*/


int criarRaiz(ARVORE *arvore, NO *raiz)
{
	arvore->raiz = (NO *) malloc(sizeof(NO));



	if(arvore->raiz != NULL)
	{
		arvore->raiz->ehFolha = false;
		arvore->raiz->esquerda = NULL;
		arvore->raiz->direita = NULL;
		arvore->raiz = raiz;

		return true;

	}

	return false;
	 

}


/*para criar a estrutura de Huffman para salvar em arquivo*/

/*Função que cria um filho a direita ou a esquerda do nó pai*/
NO *inserirFilho(NO *pai, NO *filho, int posicao)
{
	if(filho != NULL)
	{
		filho->esquerda = NULL;
		filho->direita = NULL;
		

		if(posicao == ESQUERDA)
			pai->esquerda = filho;

		else
			pai->direita = filho;


		return filho;

	}

	return NULL;
}

void apagarArvore_aux(NO *raiz)
{
	if (raiz != NULL)
	{
		apagarArvore_aux(raiz->direita);
		apagarArvore_aux(raiz->esquerda);
		free(raiz);

	}

}

void apagarArvore(ARVORE **arvore)
{
	apagarArvore_aux((*arvore)->raiz);

	free(*arvore);

}


void escrever_preOrdem_aux(NO *raiz,FILE *arquivo)
{
	if(raiz != NULL)
	{
		raiz->ehFolha = false;

		if(raiz->esquerda == NULL && raiz->direita == NULL) //se for folha
			raiz->ehFolha = true;

	    fwrite(raiz,sizeof(NO),1,arquivo);

		escrever_preOrdem_aux(raiz->esquerda, arquivo);
		escrever_preOrdem_aux(raiz->direita, arquivo);
	}


}

void escrever_preOrdem(ARVORE *arvore,FILE *arquivo)
{  
	escrever_preOrdem_aux(arvore->raiz, arquivo);

}

//percurso em pre-ordem para ler a arvore no arquivo
void ler_preOrdem_aux(NO *pai,NO *filho,int posicao,FILE *arquivo)
{

    filho = (NO *) malloc(sizeof(NO));

    fread(filho,sizeof(NO),1,arquivo);
    inserirFilho(pai,filho,posicao);
	

    
    if(filho->ehFolha == false)
    {
		ler_preOrdem_aux(filho,filho->esquerda,ESQUERDA,arquivo);
		ler_preOrdem_aux(filho,filho->direita,DIREITA,arquivo);
	}


}

void ler_preOrdem(ARVORE *arvore,FILE *arquivo)
{   
	NO *raiz = (NO *) malloc(sizeof(NO));
	fread(raiz,sizeof(NO),1,arquivo);
	criarRaiz(arvore,raiz);
	ler_preOrdem_aux(arvore->raiz,arvore->raiz->esquerda,ESQUERDA ,arquivo);
	ler_preOrdem_aux(arvore->raiz,arvore->raiz->direita,DIREITA ,arquivo);

}

#endif
