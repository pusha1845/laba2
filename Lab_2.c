#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int r[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };

    clock_t start, end; 

    FILE* file = fopen("result.csv", "w");

    fprintf(file, "Size;Time\n");

    for (int z = 0; z < sizeof(r) / sizeof(int); ++z) {
        int n = r[z];

        int** a = (int**)malloc(sizeof(int*) * n);
        for (int i = 0; i < n; ++i) {
            a[i] = (int*)malloc(sizeof(int) * n);
        }

        int** b = (int**)malloc(sizeof(int*) * n);
        for (int i = 0; i < n; ++i) {
            b[i] = (int*)malloc(sizeof(int) * n);
        }

        int** c = (int**)malloc(sizeof(int*) * n);
        for (int i = 0; i < n; ++i) {
            c[i] = (int*)malloc(sizeof(int) * n);
        }
        srand(time(NULL)); 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rand() % 100 + 1; 
                b[i][j] = rand() % 100 + 1; 
            }
        }

        int elem_c;
        start = clock();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                elem_c = 0;
                for (int x = 0; x < n; x++)
                {
                    elem_c = elem_c + a[i][x] * b[x][j];
                }
                c[i][j] = elem_c;
            }
        }
        end = clock();

        float time_spent = (float)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "%dx%d;%.3f\n", r[z], r[z], time_spent);
        printf("Size %dx%d: %.3f\n", r[z], r[z], time_spent);

        free(a);
        free(b);
        free(c);
    }

    fclose(file);

    return 0;
}