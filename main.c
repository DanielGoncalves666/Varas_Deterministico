/*
Nome do Arquivo: main.c
Programador: Daniel Gonçalves
Data de Criação: 2018

Descrição: Esse módulo é o módulo principal do programa, responsável por chamar todas as funções necessárias para alocação de matrizes,
distribuição do campo de piso, distrbuição dos pedestres, movimentação e realização de testes em massa.
*/

#include<stdio.h>
#include<stdlib.h>
#include"prototipos.h"

int main(){

	for(int testes=0; testes<QTD_TESTES; testes++){	//laço de repetição para executação de todos os testes 
		
		ler_inicio();	//função para ler as entradas necessárias (lin, col, local_portas)
		alocar_tudo();	//função para alocar todas as matrizes
			
		semente = 0;	//inicializa a variavel usada para gerar os numeros pseudo-aleatorios
		for(int simu=0; simu<10; simu++){	//simu define a qtd de simulações a serem feitas, que por padrão é 100
//- - - - - - - - - - - - - - - - - - - - - - - - - Campo de Piso - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//	
			int passos = 0;//variável que indica a qtd de passos necessários para todos os pedestres saírem da sala
			
			srand(semente);//dá semente como memória para a função rand()
			inicializar_campo_piso();//função para inicializar a matriz campo_piso
			inicializar_mat_int(&fogo,0,0);//preenche toda a matriz fogo com zeros								//fogo
			inserir_port();//função para inserir as portas em sua respectiva camada da matriz campo_piso
			distribuir_piso();//função para distribuir os valores para cada celula do campo de piso, em cada camada
			piso_final();//une todas as camadas do campo_piso
			copiarPiso(&piso,&piso_original);//função que copia o conteudo de uma matriz de floats em outra					//fogo
//- - - - - - - - - - - - - - - - - - - - - - - - - Movimentação - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - //	
			inicializar_mat_int(&sala,0,0);//função para inicializar a sala com zeros
			
			pedestre_alocar();//função para distribuir os pedestres na sala
			inserir_fogo();////função responsável por inserir os focos de incêndio na sala							//fogo
			
			//imprimir_sala(&sala);printf("\n\n");
			//imprimir_piso(&piso);printf("\n\n");
			
			do{
				basic_moviment();//função para a movimentação dos pedestres
				movimentar_em_X();//função responsável por impedir a movimentação em X
				mover_msmlugar();//função para impedir que pedestres se movimentem para a mesma posição
				pedestre_sair_2();//função para retirar os pedestres que saírem da sala
				converter_posicao();//função para 'realizar a movimentação'
				inicializar_mat_int(&sala,0,0);//reinicializa a sala
				ped_sala_loc();//função para alocar novamente os pedestres na sala formatada

				fogo_espalhar();//função responsável por espalhar o fogo pela sala							//fogo
				inicializar_campo_piso();//função para inicializar a matriz campo_piso							//fogo
				inserir_port();//função para inserir as portas em sua respectiva camada da matriz campo_piso				//fogo
				distribuir_piso();//função para distribuir os valores para cada celula do campo de piso, em cada camada			//fogo
				piso_final();//une todas as camadas do campo_piso									//fogo

				passos++;//incrementa a variável passos ao fim de uma rodada

				//imprimir_sala_pedestres(&sala,&piso);printf("\n\n");getchar();
				//imprimir_piso(&piso);printf("\n\n");
				
			}while(cont() > 0);//rodará enquanto a qtd de pedestres for maior que 0
			
			semente++;//incrementa a variavel usado para gerar os numeros pseudo-aleatorios
			printf("%d ",passos);//imprime a quantidade de passos necessários para todos os pedestres saírem da sala
		}
		desaloca();//desaloca as matrizes
		printf("\t%d %d\n",local_port[0],local_port[1]);
	}
	return 0;
}
