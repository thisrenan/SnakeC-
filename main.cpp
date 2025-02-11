#include <iostream>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

    const int alturaQuadro = 25;
    const int larguraQuadro = 25;
    const int tempoJogo = 300;

    int direcao; //parado = 0; esquerda = 1; direita = 2; cima = 3; baixo = 4;
    bool gameOver = false;
    int quadro[alturaQuadro][larguraQuadro]; //0 = nada, 1 = parede, 2 = fruit, 3 = cobra
    int pontuacao = 0;
    int fruitX = rand() % alturaQuadro;
    int fruitY = rand() % larguraQuadro;
    int cobraX = alturaQuadro /2;
    int cobraY = larguraQuadro /2;
    int tamanhoCobra = 1;
    int tamanhoCobraAux;

void MontaQuadro()
{
    for (int i=0; i < alturaQuadro; i++)
    {
        for (int j=0; j < larguraQuadro; j++)
        {
            if ((i == 0) || (i == alturaQuadro-1) || (j == 0) || (j == alturaQuadro-1))
            {
                quadro[i][j] = 1;
            }
            else
            {
                quadro[i][j] = 0;
            }
        }
    }

    quadro[cobraX][cobraY] = 3;
    quadro[fruitX][fruitY] = 2;
}

void ExibeQuadro()
{
    system("cls");

    for (int i=0; i < alturaQuadro; i++)
    {
        for (int j=0; j < larguraQuadro; j++)
        {
            //cout<<quadro[i][j];

            if (quadro[i][j] == 0)
                cout<<" ";
            else if (quadro[i][j] == 1)
                cout<<"#";
            else if (quadro[i][j] == 2)
                cout<<"@";
            else
                cout<<"*";

        }
        cout<<endl;
    }
    cout<<"Score: "<<pontuacao;
}

void LerTeclado()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                direcao = 1;
            break;
            case 'd':
                direcao = 2;
            break;
            case 'w':
                direcao = 3;
            break;
            case 's':
                direcao = 4;
            break;
            case 'x':
                gameOver = true;
            break;
        }
    }
}

void VerificaColisao()
{
    if (quadro[cobraX][cobraY] == 1)
    {
        gameOver = true;
    }
    else if (quadro[cobraX][cobraY] >= 3)
    {
        gameOver = true;
    }
}

void VerificaPegouComida()
{
    if (quadro[cobraX][cobraY] == 2)
    {
        fruitX = rand() % alturaQuadro;
        fruitY = rand() % larguraQuadro;

        while (quadro[fruitX][fruitY] == 1 || quadro[fruitX][fruitY] >= 3)
        {
            fruitX = rand() % alturaQuadro;
            fruitY = rand() % larguraQuadro;
        }

        quadro[fruitX][fruitY] = 2;
        pontuacao = pontuacao + 10;
        tamanhoCobra = tamanhoCobra + 1;
    }
}

void LimpaCobra()
{
    for (int i=0; i < alturaQuadro; i++)
    {
        for (int j=0; j < larguraQuadro; j++)
        {
            if (i == cobraX && j == cobraY)
                continue;

            if (quadro[i][j] == 3)
                quadro[i][j] = 0;
            else if (quadro[i][j] == 4)
                quadro[i][j] = 3;
            else if (quadro[i][j] == 5)
                quadro[i][j] = 4;
            else if (quadro[i][j] == 6)
                quadro[i][j] = 5;
            else if (quadro[i][j] == 7)
                quadro[i][j] = 6;
            else if (quadro[i][j] == 8)
                quadro[i][j] = 7;
            else if (quadro[i][j] == 9)
                quadro[i][j] = 8;
            else if (quadro[i][j] == 10)
                quadro[i][j] = 9;
            else if (quadro[i][j] == 11)
                quadro[i][j] = 10;
            else if (quadro[i][j] == 12)
                quadro[i][j] = 11;
        }
    }
}

void CalculaPosicaoEFimJogo()
{
    Sleep(tempoJogo);

    switch (direcao)
    {
        case 1:
            cobraY--;
            VerificaPegouComida();
            VerificaColisao();
            quadro[cobraX][cobraY] = tamanhoCobra+2;
            break;
        case 2:
            cobraY++;
            VerificaPegouComida();
            VerificaColisao();
            quadro[cobraX][cobraY] = tamanhoCobra+2;
            break;
        case 3:
            cobraX--;
            VerificaPegouComida();
            VerificaColisao();
            quadro[cobraX][cobraY] = tamanhoCobra+2;
            break;
        case 4:
            cobraX++;
            VerificaPegouComida();
            VerificaColisao();
            quadro[cobraX][cobraY] = tamanhoCobra+2;
            break;
        default:
            break;
    }

    LimpaCobra();
}

void ExibeQuadroGameOver()
{
    system("cls");
    cout<<"Parabens, sua pontuacao foi de: "<<pontuacao;
}

int main()
{
    MontaQuadro();

    while (!gameOver)
    {
        ExibeQuadro();
        LerTeclado();
        CalculaPosicaoEFimJogo();
    }

    ExibeQuadroGameOver();

    return 0;
}
