#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>

double f(int x, int n, int V[n]);
void gravarArquvio();
void gravarArquviobinario();
int botar_nome();
void sair();


FILE *pont_arq;
FILE *pont_bin;
char nome[50];
char nomebin[50];
int *V;
int n, m, i, x, a, b, c, d, e,pontos = 0, num, voltar = 2, total_gravado;

//CRIAR O ARQUIVO COM O NOME

int main()
{
    setlocale(LC_ALL, "portuguese");

    botar_nome();
    //PERGUNTAR USUARIO SE QUER VOLTAR
    pont_bin = fopen(nomebin, "rb");
        if(pont_bin != NULL){
            printf("Deseja voltar para um jogo antigo? Digite 1 para sim e 2 para não: ");
            scanf("%i", &voltar);
        }
    fclose(pont_arq);
    do
    {
        c=0;
        b=0;
        num=0;
        if(voltar == 2){
            printf("Digite o grau do polinômio: ");
            scanf("%i", &m);
            n=m+1;
            V = malloc(n * sizeof(int));
            srand(time(NULL));
            for(i=0;i<n;i++)
                V[i] = rand() % 10;

            gravarArquviobinario();

            gravarArquvio();
        }else if(voltar == 1)
        {
            //VOLTAR PARA O JOGO Q ESTAVA ANTES
            pont_bin = fopen(nomebin, "rb");
            if(pont_bin == NULL){
                printf("ERRO! SEU ARQUIVO NÃO FOI ENCONTRADO!");
                voltar = 2;

                return 0;
            }
            fread(&n, sizeof(int), 1, pont_bin);
            V = malloc(n * sizeof(int));
            int vetor_todo[n + 1];
            fread(&vetor_todo, sizeof(int), n + 1, pont_bin);
            fclose(pont_bin);
            for(i = 0; i < n; i++)
            {
                V[i] = vetor_todo[i];
            }
            voltar = 2;
        }

        do
        {
            d=0;
            //ENTRADA DO X
            printf("Escreva um valor de x para receber f(x): ");
            num++;
            scanf("%d", &x);
            //SAIDA DO F(x) PARA O USUARIO
            printf("\nf(x) = %f\n", f(x, n, V));
            //GRAVAR O F(x) E O X EM UM ARQUVIO
            pont_arq = fopen(nome, "a");
            fprintf(pont_arq,"X = %d\tf(x) = %f\n",x, f(x, n, V));
            fclose(pont_arq);
            printf("\nTente adivinhar os termos do polinômio: \n");
            for(i=0;i<n;i++)
            {
                printf("x^%d: ", i);
                scanf("%d", &a);
                if(a!=V[i])
                {
                    i=n;
                    d=1;
                }
            }
            if(d==0)
            {
                c=1;
                //ACERTOU O POLINOMIO E MOSTRAR POLINOMIO
                free(V);
                remove(nomebin);
                printf("\nParabéns, você acertou os termos do polinômio! O polinômio é:\n");
                for(i=(n-1); i>=0; i--)
                {
                    if(i==0)
                        printf("%d ", V[i]);
                    else
                        printf("%d*x^%d + ", V[i], i);
                }
            //SISTEMA DE PONTUAÇÂO
            pontos = pontos+ 5*(m+1)-num;
            printf("\nSua pontuação é: %i", pontos);
            c=1;
            b=0;
            }
            else
            {
                printf("\nErrado.\n");
                sair();
            }
        }while(c==0);
        while(b==0)
        {
            //SAIR DO JOGO
            sair();
        }
    }while(b==1);
}
//FUNÇÂO PARA ENTRAR O X COM O POLINOMIO E SAIR O F(X)
double f(int x, int n, int V[n])
{
    int i;
    double y;
    y=0;
    for(i=0;i<n;i++)
    {
        y = y + (V[i]*pow(x,i));
    }
    return y;
}
int botar_nome()
{
    //NOME
    printf("Digite seu nome: ");
    gets(nome);
    strcpy(nomebin, nome);
    strcat(nomebin, "bin.txt");
    strcat(nome,".txt");
    //CRIAR ARQUIVO
    pont_arq = fopen(nome, "a");
    fclose(pont_arq);
    return 0;
}
void gravarArquviobinario()
{
    pont_bin = fopen(nomebin, "wb");
    int vetor[n+1];
    for(i = 0; i < n +1; i++)
    {
        if(i == 0){
            vetor[i] = n;
        }else{
            vetor[i] = V[i - 1];
        }
    }
    total_gravado = fwrite(&vetor,sizeof(int), n + 1, pont_bin);
    fclose(pont_bin);
}
void gravarArquvio()
{
    pont_arq = fopen(nome, "a");
    for(i=(n-1); i>=0; i--)
    {
        if(i==0)
            fprintf(pont_arq,"%d \n", V[i]);
        else
            fprintf(pont_arq,"%d*x^%d + ", V[i], i);
    }
    fclose(pont_arq);
}
void sair()
{
    printf("\nDeseja continuar? Digite 1 para sim e 2 para não: ");
            scanf("%d", &b);
            if(b == 2){
                //DESLOGAR PARA ENTRAR EM OUTRO USUARIO
                printf("Deseja logar em outro usuario? Digite 1 para sim e 2 para não: ");
                scanf("%i", &e);
                if(e == 1){
                    fflush(stdin);
                    botar_nome();
                    c = 0;
                    b = 1;
                }else if(e == 2){
                    printf("TCHAU :)");
                    c=1;
                }else{
                    printf("Digite 1 ou 2.");
                    b = 0;
                }
            }
            if(b<1 || b>2)
            {
                printf("Digite 1 ou 2.");
                b=0;
            }
}
