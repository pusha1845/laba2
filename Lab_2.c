#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define N 500000

void shell(int* items, int count) {
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) {
	int i, j;
	int x, y;

	i = left; j = right;

	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int compare(const void* x1, const void* x2) {
	return (*(int*)x1 - *(int*)x2);
}

int main(void) {
	setlocale(LC_ALL, "Rus");
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end;

	int i = 0, j = 0, r;

	int* a = (int*)malloc(sizeof(int) * N);
	int* b = (int*)malloc(sizeof(int) * N);
	int* c = (int*)malloc(sizeof(int) * N);

	FILE* file = fopen("result2.csv", "w");

	srand(time(NULL));
	while (i < N) {
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
		c[i] = rand() % 100 + 1;
		i++;
	}
	fprintf(file, "Сортировка спиcка из %d элементов\n", N);
	printf("Сортировка спиcка из %d элементов\n", N);
	fprintf(file, ";Сортировка;Время, с\n");
	fprintf(file, "Случайный набор\n");
	printf("Случайный набор\n");
	start = clock();
	shell(a, N);
	end = clock();
	float spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Сортировка Шелла;%.3f\n", spent_time);
	printf("Сортировка Шелла;%.3f\n", spent_time);

	start = clock();
	qs(b, 0, N - 1);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qs);%.3f\n", spent_time);
	printf("Быстрая сортировка (qs);%.3f\n", spent_time);

	start = clock();
	qsort(c, N, sizeof(int), compare);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qsort);%.3f\n", spent_time);
	printf("Быстрая сортировка (qsort);%.3f\n", spent_time);

	i = 0;
	while (i < N) {
		a[i] = i + 1;
		b[i] = i + 1;
		c[i] = i + 1;
		i++;
	}
	fprintf(file, "Возрастающий набор\n");
	printf("Возрастающий набор\n");
	start = clock();
	shell(a, N);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Сортировка Шелла;%.3f\n", spent_time);
	printf("Сортировка Шелла;%.3f\n", spent_time);



	start = clock();
	qs(b, 0, N - 1);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qs);%.3f\n", spent_time);
	printf("Быстрая сортировка (qs);%.3f\n", spent_time);


	start = clock();
	qsort(c, N, sizeof(int), compare);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qsort);%.3f\n", spent_time);
	printf("Быстрая сортировка (qsort);%.3f\n", spent_time);


	i = 0;
	while (i < N) {
		a[i] = N - i;
		b[i] = N - i;
		c[i] = N - i;
		i++;
	}
	fprintf(file, "Убывающий набор\n");
	printf("Убывающий набор\n");
	start = clock();
	shell(a, N);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Сортировка Шелла;%.3f\n", spent_time);
	printf("Сортировка Шелла;%.3f\n", spent_time);

	start = clock();
	qs(b, 0, N - 1);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qs);%.3f\n", spent_time);
	printf("Быстрая сортировка (qs);%.3f\n", spent_time);

	start = clock();
	qsort(c, N, sizeof(int), compare);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qsort);%.3f\n", spent_time);
	printf("Быстрая сортировка (qsort);%.3f\n", spent_time);

	i = 0;
	while (i < N) {
		if (i < (N / 2)) {
			a[i] = i + 1;
			b[i] = i + 1;
			c[i] = i + 1;
		}
		else {
			a[i] = N - i;
			b[i] = N - i;
			c[i] = N - i;
		}
		//printf("%d ", b[i]);
		i++;
	}
	fprintf(file, "Возрастающий до половины набор\n");
	printf("Возрастающий до половины набор\n");
	start = clock();
	shell(a, N);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Сортировка Шелла;%.3f\n", spent_time);
	printf("Сортировка Шелла;%.3f\n", spent_time);

	//start = clock();
	//qs(b, 0, N - 1);
	//end = clock();
	//spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	//spent_time = .0;
	//fprintf(file, ";Быстрая сортировка (qs);%.3f\n", spent_time);
	fprintf(file, ";Быстрая сортировка (qs);-\n");
	printf("Быстрая сортировка (qs);-\n");

	start = clock();
	qsort(c, N, sizeof(int), compare);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(file, ";Быстрая сортировка (qsort);%.3f\n", spent_time);
	printf("Быстрая сортировка (qsort);%.3f\n", spent_time);


	free(a);
	free(b);
	free(c);
	fclose(file);
	return(0);
}