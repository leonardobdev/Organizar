#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int tamanho = 0;
int passos = 0;

void QuickSort(int *v, int tam)
{
    if (tam <= 1)
        return;
    else
    {
        int x = v[0];
        int a = 1;
        int b = tam - 1;
        do
        {
            while ((a < tam) && (v[a] <= x))
                a++;
            while (v[b] > x)
                b--;
            if (a < b)
            {
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
                passos++;
        } while (a <= b);
        v[0] = v[b];
        v[b] = x;
        QuickSort(v, b);
        QuickSort(&v[a], tam - a);
        passos++;
    }
}

void PercorreArvore(int *v, int raiz, int folha)
{
    int percorreu = 0, maxfolhas, temp;
    while ((raiz * 2 <= folha) && (!percorreu))
    {
        if (raiz * 2 == folha || v[raiz * 2] > v[raiz * 2 + 1])
            maxfolhas = raiz * 2;
        else
            maxfolhas = raiz * 2 + 1;
        if (v[raiz] < v[maxfolhas])
        {
            temp = v[raiz];
            v[raiz] = v[maxfolhas];
            v[maxfolhas] = temp;
            raiz = maxfolhas;
        }
        else
            percorreu = 1;
        passos++;
    }
}

void HeapSort(int *v, int tam)
{
    int i, temp;
    for (i = (tam / 2); i >= 0; i--)
        PercorreArvore(v, i, tam - 1);
    for (i = tam - 1; i >= 1; i--)
    {
        temp = v[0];
        v[0] = v[i];
        v[1] = temp;
        PercorreArvore(v, 0, i - 1);
    }
}

void MergeSort(int *v, int inicio, int fim)
{
    int i, j, k, meio, *t;
    if (inicio == fim)
        return;
    meio = (inicio + fim) / 2;
    MergeSort(v, inicio, meio);
    MergeSort(v, meio + 1, fim);
    i = inicio;
    j = meio + 1;
    k = 0;
    t = (int *)malloc(sizeof(int) * (fim - inicio + 1));
    while (i < meio + 1 || j < fim + 1)
    {
        if (i == meio + 1)
        {
            t[k] = v[j];
            j++;
        }
        else if (j == fim + 1)
        {
            t[k] = v[i];
            i++;
        }
        else if (v[i] < v[j])
        {
            t[k] = v[i];
            i++;
        }
        else
        {
            t[k] = v[j];
            j++;
        }
        k++;
            passos++;
    }
    for (i = inicio; i <= fim; i++)
        v[i] = t[i - inicio];
    passos++;
    free(t);
}

int main()
{

    FILE *arquivo;
    int *vetor, numero, i;

    arquivo = fopen("C:/aps/dtaleat1kdup1.txt", "r");

    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fscanf(arquivo, "%d", &numero) == 1)
    {
        tamanho++;
    }

    fseek(arquivo, 0, SEEK_SET);

    vetor = (int *)malloc(tamanho * sizeof(int));

    if (vetor == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para o vetor.\n");
        fclose(arquivo);
        return 1;
    }

    for (i = 0; i < tamanho; i++)
    {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
    
    printf("\nTotal de numeros: %d", tamanho);

    printf("\nPassos:");

    passos = 0;
    QuickSort(vetor, tamanho);
    printf("\nQuickSort: %d", passos);

    passos = 0;
    HeapSort(vetor, tamanho);
    printf("\nHeapSort: %d", passos);

    passos = 0;
    MergeSort(vetor, 0, tamanho - 1);
    printf("\nMergeSorts: %d", passos);

    printf("\n\n");

    free(vetor);

    return 0;
}
