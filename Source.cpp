#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <stack>
#include <queue>


using namespace std;

int max_size = 5, i, j, start, num, mass_ex[30], D = 0, R = 1000, perif, center, elem = 0, counter_edge = 0, all_edge = 0, deg, stepen;
int* DIST = (int*)malloc(max_size * sizeof(int));
int* DIST2 = (int*)malloc(max_size * sizeof(int));
queue<int> ex;
int st_rebro;
int z[100];
int counter_rebro, schetchik, schetchik2;
void BSFD(int st, int** b, int num_of_elem, int* vis) {
	queue<int> Q;
	int t;
	Q.push(st);
	vis[st] = 0;

	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		for (int i = 0; i < num_of_elem; i++)
		{
			if (b[t][i] > 0 && vis[i] == 1000)
			{
				vis[i] = vis[t] + b[t][i];
				Q.push(i);
			}
		}
	}
}

void BSFD_rebro(int st_rebro, int** b, int num_edge, int num_height, int* vis) {
	queue<int> Q;
	int t;
	Q.push(st_rebro);
	vis[st_rebro] = 0;

	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		for (int i = 0; i < num_edge; i++)
		{
			if (b[t][i] > 0 && vis[t] == 1000)
			{
				for (int k = 0; k < num_height; k++)
				{
					if (b[k][i] > 0 && vis[k] == 1000)
					{
						vis[k] = vis[k] + b[k][i];
						Q.push(k);
					}
				}
			}
		}
	}
}

void max_elem(int* mass) {
	int max = 0, n;
	for (n = 0; n < max_size; n++) {
		if (mass[n] > max && mass[n] != 1000)
			max = mass[n];
	}
	ex.push(max);
}

int main() {

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int** a = new int* [max_size];
	for (i = 0; i < max_size; i++)
	{
		a[i] = new int[max_size];
	}

	for (i = 0; i < max_size; i++)
	{
		for (j = i + 1; j < max_size; j++)
		{
			num = rand() % 8;
			if (num <= 4)
			{
				a[i][j] = 0;
				a[j][i] = a[i][j];
			}
			else
			{
				a[i][j] = (rand() % 6) + 1;
				a[j][i] = a[i][j];
			}
		}
	}
	printf("\nНеориентированный граф:\n");
	for (i = 0; i < max_size; i++)
	{
		DIST[i] = 1000;
		for (j = 0; j < max_size; j++)
		{
			if (i == j)
				a[i][j] = 0;
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < max_size; i++) {
		BSFD(i, a, max_size, DIST);
		max_elem(DIST);
		printf("\nРасстояния из %d-й вершины: ", i + 1);
		for (j = 0; j < max_size; j++) {
			printf("%4d ", DIST[j]);
			DIST[j] = 1000;
		}
	}

	printf("\n\nЭксицентритеты вершин:\n");
	for (i = 0; i < max_size; i++) {
		if (!ex.empty()) {
			mass_ex[i] = ex.front();
			printf("%d-й = %d\n", i + 1, mass_ex[i]);
			ex.pop();
		}
	}

	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] > D)
			D = mass_ex[i];
		if (mass_ex[i] < R)
			R = mass_ex[i];
	}

	if (D > 0)
	{
		printf("Диаметр графа = %d\n", D);
	}
	if (R > 0)
	{
		printf("Радиус графа = %d", R);
	}

	printf("\nПерифирийные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == D)
			printf("%d ", i + 1);
	}
	printf("\nЦентральные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == R && R != 0)
			printf("%d ", i + 1);
	}

	//изолированные, концевые и доминирующие вершины
	printf("\n\nКонцевые вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
				elem++;
		}
		if (elem == 1)
			printf("%d ", i + 1);
		elem = 0;
	}

	printf("\nИзолированные вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
			{
				elem++;
			}
		}
		if (elem == 0)
			printf("%d ", i + 1);
		elem = 0;
	}

	printf("\nДоминирующие вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
			{
				elem++;
			}
		}
		if (elem == max_size - 1)
			printf("%d ", i + 1);
		elem = 0;
	}


	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Матрица инцидентности:" << endl;


	int q, w;
	counter_edge = 0;
	all_edge = 0;
	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < (max_size + q - max_size + 1); w++)
		{
			if (a[q][w] > 0 && a[q][w] != 1000)
			{
				all_edge++;
			}
		}
	}
	int** x = new int* [max_size];
	for (i = 0; i < max_size; i++)
	{
		x[i] = new int[all_edge];
	}

	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < all_edge; j++)
		{
			x[i][j] = 0;
		}
	}

	for (q = 0; q < max_size; q++)
	{
		for (w = q; w < max_size; w++)
		{
			if (a[q][w] > 0 && a[q][w] != 1000)
			{
				x[q][counter_edge] = a[q][w];
				x[w][counter_edge] = a[q][w];
				counter_edge++;
			}
		}
	}

	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < all_edge; w++)
		{
			printf("%2d", x[q][w]);
		}
		printf("\n");

	}

	for (i = 0; i < max_size; i++)
	{
		DIST2[i] = 1000;
	}

	for (i = 0; i < max_size; i++) {
		BSFD(i, a, max_size, DIST2);
		max_elem(DIST2);
		printf("\nРасстояния из %d-й вершины: ", i + 1);
		for (j = 0; j < max_size; j++) {
			printf("%4d ", DIST2[j]);
			DIST2[j] = 1000;
		}
	}

	printf("\n\nЭксицентритеты вершин:\n");
	for (i = 0; i < max_size; i++) {
		if (!ex.empty()) {
			mass_ex[i] = ex.front();
			printf("%d-й = %d\n", i + 1, mass_ex[i]);
			ex.pop();
		}
	}

	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] > D)
			D = mass_ex[i];
		if (mass_ex[i] < R)
			R = mass_ex[i];
	}
	if (D > 0)
	{
		printf("Диаметр графа = %d\n", D);
	}
	if (R > 0)
	{
		printf("Радиус графа = %d", R);
	}

	//printf("Диаметр графа = %d\nРадиус графа = %d", D, R);
	cout << endl << endl;
	printf("\nПерифирийные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == D)
			printf("%d ", i + 1);
	}
	printf("\nЦентральные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == R && R != 0)
			printf("%d ", i + 1);
	}

	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < all_edge; w++)
		{
			if (x[q][w] > 0)
			{
				stepen++;
			}

		}
		z[q] = stepen;
		printf("\n");
		cout << "Степень вершины" << " " << q << " " << "равна";
		printf("%2d", stepen);
		stepen = 0;
	}


	printf("\n\nКонцевые вершины:");
	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < all_edge; w++)
		{
			if (x[q][w] > 0)
				elem++;
		}
		if (elem == 1)
			printf("%d ", q + 1);
		elem = 0;
	}

	printf("\nИзолированные вершины:");
	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < all_edge; w++)
		{
			if (x[q][w] > 0)
			{
				elem++;
			}
		}
		if (elem == 0)
			printf("%d ", q + 1);
		elem = 0;
	}

	printf("\nДоминирующие вершины:");
	for (q = 0; q < max_size; q++)
	{
		for (w = 0; w < all_edge; w++)
		{
			if (x[q][w] > 0)
			{
				elem++;
			}
		}
		if (elem == max_size - 1)
			printf("%d ", q + 1);
		elem = 0;
	}
	_getch();
}