#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

char nome[20];
int i,j;
char matriz[3][3];

void inicializacao(){
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            matriz[i][j] = 'a';
        }
    }
}

int coordenadaEhValida(int x, int y){
    if(x<=2 && y<= 2 && matriz[x][y] == 'a')
        return 1;
    else
        return 0;
}

int ganhouLinha(){
    for(i=0;i<3;i++){
        if(matriz[i][0] != 'a' && (matriz[i][0] == matriz[i][1]) && (matriz[i][1] == matriz[i][2]))
            return 1;
    }
    return 0;
}

int ganhouColuna(){
    for(j=0;j<3;j++){
        if(matriz[0][j] != 'a' && (matriz[0][j] == matriz[1][j]) && (matriz[1][j] == matriz[2][j]))
            return 1;
    }
    return 0;
}

int ganhouDiagP(){
    if(matriz[0][0] != 'a' && (matriz[0][0] == matriz[1][1]) && (matriz[1][1] == matriz[2][2]))
        return 1;
    else
        return 0;
}

int ganhouDiagS(){
    if(matriz[0][2] != 'a' && (matriz[0][2] == matriz[1][1]) && (matriz[1][1] == matriz[2][0]))
        return 1;
    else
        return 0;
}

void imprimir(){
    printf("      0  1  2\n");
    for(i=0;i<3;i++){
        printf("   %i", i);
        printf(" [");
        for(j=0;j<3;j++){
            if(matriz[i][j] == 'a'){
                printf("  ");
            }else{
                printf(" %c", matriz[i][j]);
            }
        }
        printf(" ]\n");
    }
}

int sorteio(){
    int primeiro;
    srand(time(NULL));
    primeiro = rand() % 2;
    return primeiro;
}

void jogar(){
    printf("Digite seu Nome: ");
    scanf("%s", nome);
    printf("%s - X\nComputador - O\n------------------\n", nome);
    int p = sorteio();
    int vez = p;
    int cont = 0;
    int x, y;
    int res = 0;
    if(p==0){
        //Jogador começa
        printf(" %s comeca\n------------------\n", nome);
        do{
            imprimir();
            if(vez == 0){
                printf("Vez de %s jogar...\n", nome);
                do{
                    printf("Em que posicao deseja jogar: ");
                    scanf("%i %i", &x,&y);
                }while(coordenadaEhValida(x, y) != 1);
                matriz[x][y] = 'X';
                vez = 1;
            }else if(vez == 1){
                printf("Vez do Computador jogar...\n");
                sleep(1);
                do{
                    srand(time(NULL));
                    x = rand() % 3;
                    y = rand() % 3;
                }while(coordenadaEhValida(x, y) != 1);
                matriz[x][y] = 'O';
                vez = 0;
            }
            res += ganhouLinha();
            res += ganhouColuna();
            res += ganhouDiagP();
            res += ganhouDiagS();
            cont++;
            if (cont == 9)
                break;
        }while(res < 1);
        imprimir();
    }
    else{
        //Computador começa
        printf(" Computador comeca\n------------------\n");
        do{
            //imprimir();
            if(vez == 1){
                printf("Vez do Computador jogar...\n");
                sleep(1);
                if(cont<=7){
                    do{
                        srand(time(NULL));
                        x = rand() % 3;
                        y = rand() % 3;
                    }while(coordenadaEhValida(x, y) != 1);
                }else if(cont == 8){
                    for(i=0;i<3;i++){
                        for(j=0;j<3;j++){
                            if(coordenadaEhValida(i, j)){
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
                matriz[x][y] = 'O';
                vez = 0;
            }else if(vez == 0){
                printf("Vez de %s jogar...\n", nome);
                do{
                    printf("Em que posicao deseja jogar: ");
                    scanf("%i %i", &x,&y);
                }while(coordenadaEhValida(x, y) != 1);
                matriz[x][y] = 'X';
                vez = 1;
            }
            res += ganhouLinha();
            res += ganhouColuna();
            res += ganhouDiagP();
            res += ganhouDiagS();
            cont++;
            imprimir();
            if (cont == 9)
                break;
        }while(res < 1);
    }
    if(res>=1){
        if(vez == 1)
            printf("Parabens %s, voce ganhou !!!\n", nome);
        else
            printf("Computador venceu!!\n");
    }else{
        printf("Deu Velha :(\n");
    }
}

int main()
{
    int resp;
    do{
        inicializacao();
        jogar();
        printf("Deseja jogar novamente?\n1 - Sim\n2 - Nao\n");
        scanf("%i", &resp);
    }while(resp != 2);
    printf("Obrigado por jogar, Volte sempre!\n");
    return 0;
}
