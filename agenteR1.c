/******************************************************************************

O objetivo do agente A é capturar todos os * da tela no menor tempo possivel.
1 - Escreva a função do agente seguindo o modelo reativo simples.
2 - Escreva a função do agente seguindo o modelo reativo baseado em objetivos.
3 - Escreva a função do agente seguindo o modelo reativo baseado em utilidade.

Depois compare o tempo que cada abordagem demorou para atingir o objetivo.

O agente capta com seus sensores o conteudo das 4 casas ao seu redor (esquerda, direita, cima, baixo)
O agente tem como acoes movimentar-se para esquerda (0), direita (1), cima (2), baixo (3)

Obs.: A função de agente implementada como exemplo representa um agente aleatório,
qualquer abordagem que você desenvolver, deve ser no mínimo melhor que o aleatório.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 52

int posAgenteX = 1;
int posAgenteY = 1;

int direction = 0; //variavel que indica a direção que o agente deverá movimentar-se

int auxPos;
int flag = 0;
int ambiente[SIZE][SIZE];

void delay(int tempo){
    int i;
	for(i=0; i<tempo; i++);
}

void construirAmbiente(){
    int i, j;
    for(i = 0; i<SIZE; i++){
        for(j = 0; j<SIZE; j++){
			if(i == 0 || i == SIZE-1){
				if(j == 0 || j == SIZE-1) ambiente[i][j] = 2;
				else ambiente[i][j] = 3;
			}
			else if(j == 0 || j == SIZE-1) ambiente[i][j] = 4;
			else ambiente[i][j] = rand()%2;
		}
	}
}

void atualizarAmbiente(int acao){
    ambiente[posAgenteX][posAgenteY] = 0;
    if (acao == 0 && ambiente[posAgenteX][posAgenteY-1] < 2) posAgenteY -= 1;
    else if (acao == 1 && ambiente[posAgenteX][posAgenteY+1] < 2) posAgenteY += 1;
    else if (acao == 2 && ambiente[posAgenteX-1][posAgenteY] < 2) posAgenteX -= 1;
    else if (acao == 3 && ambiente[posAgenteX+1][posAgenteY] < 2) posAgenteX += 1;
    ambiente[posAgenteX][posAgenteY] = 5;
}

void mostrarAmbiente(){
	system("cls");
	int count = 0;
	int i, j;
    for(i = 0; i<SIZE; i++){
        for(j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 0) printf(" ");
            else if (ambiente[i][j] == 1) { count++; printf("*");}
            else if (ambiente[i][j] == 2) printf("+");
            else if (ambiente[i][j] == 3) printf("-");
            else if (ambiente[i][j] == 4) printf("|");
            else if (ambiente[i][j] == 5) printf("A");
        }
        printf("\n");
    }
	printf("Faltam %d objetos.\n", count);
}

bool verificarSucesso(){
    int i, j;
    for(i = 0; i<SIZE; i++){
        for(j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 1) return false;
        }
    }
    return true;
}

int lerSensor(int lado){
    if (lado == 0) return ambiente[posAgenteX][posAgenteY-1];
    if (lado == 1) return ambiente[posAgenteX][posAgenteY+1];
    if (lado == 2) return ambiente[posAgenteX-1][posAgenteY];
    if (lado == 3) return ambiente[posAgenteX+1][posAgenteY];
    return 2;
}

int funcaoAgente(int esquerda, int direita, int cima, int baixo){
    delay(10000); //como o ambiente é muito pequeno, esse delay serve para que o tempo seja mensurável


	//aleatorio
	return rand()%4;
}

int funcaoAgente1(int esquerda, int direita, int cima, int baixo) {
    delay(10000);

    if(direction == 0) {
        if (posAgenteY!=SIZE-2) { //o agente se movimenta para a direita até perceber que chegou ao limite do ambiente
            return 1;
        }
        else {  direction = 1; //direção muda quando o agente mudar de linha
            return 3;
            }
    }
    else {
        if(posAgenteY!=1) { //o agente se movimenta para a esquerda até chegar ao limite do ambiente
            return 0;
        }
        else { direction = 0;
               return 3;
        }

    }

}

int funcaoAgente2(int esquerda, int direita, int cima, int baixo) {
    delay(10000);

    int i, count = 0;
    if(direction==0) {
    for (i=0; i<posAgenteY; i++) {              //o agente checa se há algum asterisco em alguma coordenada a esquerda
        if(ambiente[posAgenteX][i]==1) count++; //se houver, traça um caminho até ele
    }
    if((count>0)&&(posAgenteY!=1)) return 0;

    for (i=posAgenteY; i<SIZE-1; i++) {         //o agente checa se há algum asterisco em alguma coordenada a direita
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=SIZE-2)) return 1;

    if (count==0) {
     direction = 1;
     return 3;
    }

    }

    else {

    for (i=posAgenteY; i<SIZE-1; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=SIZE-2)) return 1;

    for (i=0; i<posAgenteY; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=1)) return 0;


    if (count==0) {
     direction = 0;
     return 3;
    }

    }
}

int funcaoAgente3(int esquerda, int direita, int cima, int baixo) {
    delay(10000);

int i, count =0;

    if (auxPos==SIZE-2) {
        for (i=0; i<posAgenteY; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=1)) return 0;

    for (i=posAgenteY; i<SIZE-1; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=SIZE-2)) return 1;

    if (count==0) {
     return 3;
    }

    }

//se houver algum asterisco ao redor que deixará o agente mais feliz, este asterisco é capturado
    if(ambiente[posAgenteX-1][posAgenteY] == 1) {
            if (flag==0) {
                flag++;
                auxPos = posAgenteX;
            }
            return 2;
    }
    if(ambiente[posAgenteX][posAgenteY-1] == 1)  {
            if (flag==0) {
                flag++;
                auxPos = posAgenteX;
            }
            return 0;
    }
    if(ambiente[posAgenteX][posAgenteY+1] == 1)  {
            if (flag==0) {
                flag++;
                auxPos = posAgenteX;
            }
            return 1;
    }
    if(ambiente[posAgenteX+1][posAgenteY] == 1)  {
            if (flag==0) {
                flag++;
                auxPos = posAgenteX;
            }
            return 3;
    }

    if(auxPos!=posAgenteX) return 2;
    flag = 0;

    //int i;
    count = 0;
    if(direction==0) {
    for (i=0; i<posAgenteY; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=1)) return 0;

    for (i=posAgenteY; i<SIZE-1; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=SIZE-2)) return 1;

    if (count==0) {
     direction = 1;
     return 3;
    }

    }

    else {

    for (i=posAgenteY; i<SIZE-1; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=SIZE-2)) return 1;

    for (i=0; i<posAgenteY; i++) {
        if(ambiente[posAgenteX][i]==1) count++;
    }
    if((count>0)&&(posAgenteY!=1)) return 0;


    if (count==0) {
     direction = 0;
     auxPos++;
     return 3;
    }

    }

}


int main()
{
    clock_t tempo[2];
	construirAmbiente();
	mostrarAmbiente();

    tempo[0] = clock();
	while(!verificarSucesso()){
        int acao = funcaoAgente3(lerSensor(0), lerSensor(1), lerSensor(2), lerSensor(3));
        atualizarAmbiente(acao);
        //mostrarAmbiente(); //mostra o que esta acontecendo, mas atrasa a execução
    }
	tempo[1] = clock();

	printf("Tempo gasto: %g ms.", ((tempo[1] - tempo[0]) / ((double)CLOCKS_PER_SEC)));
    return 0;
}
