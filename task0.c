#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define SIZE 50

struct matrix {
    int n;
    float elements[SIZE][SIZE];
};

typedef struct matrix* matrix;

int det_function(struct matrix a)
{
    for(int i=0; i<a.n; i++)
    {
        for (int j=i+1; j<=a.n; j++)
        {
            float x=a.elements[j][i]/a.elements[i][i];
            for(int t=0; t<=a.n; t++)
            {
                a.elements[j][t]=a.elements[j][t]-a.elements[i][t]*x;
            }
        }
    }
    float s=1;
    for (int p=0; p<=a.n; p++)
    {
        s=s*a.elements[p][p];
    }
    s=round(s);
    int b=(int)s;
    return b;
}

int InputArray(float a[], int n, const char *str)
{
    int i=0;
    for (i=0; i<=n; i++)
    {
        printf("¬ведите %s %d\n", str, i+1);
        scanf("%f",&a[i]);
    }
    return 0;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    int n;
    printf("¬ведите размер матрицы\n");
    scanf("%d",&n);
    n=n-1;
    struct matrix m;
    m.n=n;
    int i=0;
    for (; i<=n; i++)
    {
        InputArray(m.elements[i], n, "элемент");
    }
    int det=det_function(m);
    printf("%d", det);
}
