/*
Nome do Arquivo: fogo.c
Programador: Daniel Gonçalves
Data de criação: 2019

Descrição: arquivo onde estão implementadas as funções relacionadas à propagação de focos de incêndio
*/

#include<stdio.h>
#include<stdlib.h>
#include"prototipos.h"

void inserir_fogo(){//função responsável por inserir os focos de incêndio na sala

	for(int a=0; a<QTD_FOCOS; ){//quantidade de focos
		
		int i = (rand()%(lin-2))+1;//sorteia a linha para colocar o foco
		int h = (rand()%(col-2))+1;//sorteia a coluna para colocar o foco
		if(piso.mat[i][h] > ZONA_NEUTRA && fogo.mat[i][h] == 0 && sala.mat[i][h] == 0){//se a célula sorteado estiver fora da zona neutra e ela não tiver um foco de incêndio e nem um pedestre já alocado
			fogo.mat[i][h] = VALOR_FOGO;//atribui o valor do fogo na matriz
			a++;//seu aumento indica a introdução com sucesso de um novo foco
		}
	}
}

void fogo_espalhar(){//função responsável por espalhar o fogo pela sala
	inicializar_mat_int(&fogo_aux,0,0);//inicializa a matriz auxiliar
	
	for(int a=0; a<lin; a++){
		for(int b=0; b<col; b++){//percorre a matriz a procura de focos
			if(fogo.mat[a][b] == VALOR_FOGO){//verifica se existe um foco na célula em questão
				fogo_aux.mat[a][b] = fogo.mat[a][b];//a matriz aux recebe o foco de incendio na posição determinada
				for(int c=-1; c<2; c++){
					for(int d=-1; d<2; d++){//percorre a vizinhança
						if(piso.mat[a+c][b+d] == PAREDE || piso.mat[a+c][b+d] == VALOR_PORTA || sala.mat[a+c][b+d] > 0 || fogo.mat[a+c][b+d] == VALOR_FOGO)
							continue;//caso a célula da vizinhança for uma parede ou uma porta ou estiver ocupada por um pedestre ou se já existir um foco naquela posição
						
						int sem = rand()%100;//a variavel 'sem' recebe um numero aleatorio, entre 0 e 99
						
						if(sem < PROBABILIDADE)//quase sem for menor que o valor setado para a probabilidade
							fogo_aux.mat[a+c][b+d] = VALOR_FOGO;//um foco é iniciado
					}
				}
			}
		}
	}
	
	for(int a=0; a<lin; a++){
		for(int b=0; b<col; b++){
			fogo.mat[a][b] = fogo_aux.mat[a][b];//os valores da matriz_aux são passados para a matriz original	
		}
	}
}
