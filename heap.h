#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

#define true 1
#define false 0

#ifndef HEAP_H
#define HEAP_H

#define TAM 256


typedef struct 
{
	NO *vetor[TAM];  //tam será o tamanho necessário para armazenar todos os caracteres do arquivo
	int fim;
}HEAP;


HEAP *criarHeap()
{
	HEAP *heap = (HEAP *) malloc(sizeof(HEAP));

	if(heap != NULL)
	{
		heap->fim = -1;
	}

	return heap;
}

int cheia(HEAP *heap)
{
	return (heap->fim == TAM - 1);
}

int vazia(HEAP *heap) 
{
	return (heap->fim == -1);
}

void swap(HEAP *heap, int i, int j) 
{
	NO *aux = heap->vetor[i];
	heap->vetor[i] = heap->vetor[j];
	heap->vetor[j] = aux;
}	

void fix_up(HEAP *heap) 
{
	int posicao = heap->fim;
	int pai = (posicao - 1) / 2;

	while (posicao > 0 && heap->vetor[posicao]->frequencia < heap->vetor[pai]->frequencia) 
	{
		swap(heap, posicao, pai);
		posicao = pai;
		pai = (pai - 1) / 2;
	}
}

void fix_down(HEAP *heap) 
{
	int pos = 0;

	while (pos < heap->fim/2) 
	{
		int esquerda = 2 * pos + 1;
		int direita = 2 * pos + 2;

		int menorfilho;

		if (direita <= heap->fim && heap->vetor[esquerda]->frequencia < heap->vetor[direita]->frequencia) 
		    menorfilho = esquerda;
		
		else 
		    menorfilho = direita;
		

		if (heap->vetor[pos]->frequencia <= heap->vetor[menorfilho]->frequencia) 
		    break;
		

		swap(heap, pos, menorfilho);
		pos = menorfilho;

	}

}

//inserir na heap
int enfileirar(HEAP *heap, NO *no) 
{
	if (!cheia(heap)) 
	{
		heap->fim++;
		heap->vetor[heap->fim] = no;
		fix_up(heap);
		return true;
	}

	return false;
}

//remover  da heap
NO *desenfileirar(HEAP *heap) 
{
	if (!vazia(heap)) 
	{
		NO *no = heap->vetor[0];
		heap->vetor[0] = heap->vetor[heap->fim];
        
		heap->fim--;
		fix_down(heap);
		return no;
	}

	return NULL;
}

void apagarHeap(HEAP *heap)
{
	if(!vazia(heap))
	{
		int pos = 0;

		while (pos <= heap->fim) 
	    {
	    	NO *no = heap->vetor[pos];

            free(no);

            pos++;

	    }

	}
}

int tamanhoHeap(HEAP *heap)
{
	return heap->fim + 1;
}


void imprimirHeap(HEAP *heap)
{
	int i = 0;
	
	for (i = 0; i < heap->fim; i++)
	{
		printf("caractere: %d    frequencia: %d\n",heap->vetor[i]->caractere, heap->vetor[i]->frequencia);
	}
}

#endif
