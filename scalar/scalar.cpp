// scalar.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<iomanip>
#include "iostream"
#include "ctime"
#include <chrono>
#include <omp.h>

double scalar(double a[], double b[], int n) {
	double result = 0.0;
	//#pragma omp parallel reduction (+: result)
	//{
	//	# pragma omp for
		for (int i = 0; i < n; i++) {
			result += a[i] * b[i];
		}
	//}
	return result;
}

double *matrVect(int n, double **matrix, double b[]) {
	double *result = new double[n];
	for (int i = 0; i < n; i++) {
		result[i] = scalar(matrix[i], b, n);
		//std::cout << result[i] << " ";
	}
	return result;
}

double **matrixMatrix(double **A, double **B, int n) {
	double **result = new double*[n];
	for (int i = 0; i < n; i++) {
		result[i] = new double[n];
		for (int j = 0; j < n; j++) {
			result[i][j] = 0.0;
			for (int k = 0; k < n; k++) {
				result[i][j] += A[i][k] * B[k][j];
			}
			//std::cout << result[i][j] << " ";
		}
		//std::cout << std::endl;
	}
	return result;
}

double *randomArray(int n) {
	double *array = new double[n];
	for (int i = 0; i < n; i++) {
		array[i] = (double)rand() / 100;
		//std::cout << array[i] << " ";
	}
	//std::cout << std::endl;
	return array;
}

double **randomMatr(int n) {
	double **matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (double)rand() / 100;
			//std::cout << matrix[i][j] << " ";
		}
		//std::cout << std::endl;
	}

	return matrix;
}

int main()
{
	int mode;
	std::cout << "Select mode: ";
	std::cin >> mode;
	switch (mode) {
	case 1: 
	{
		srand(time(NULL));
		int n = 0;
		std::cin >> n;
		double *a = randomArray(n);
		double *b = randomArray(n);
		auto t1 = std::chrono::high_resolution_clock::now();
		scalar(a, b, n);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		std::cout << duration;
		break;
	}
	case 2:
	{
		srand(time(NULL));
		int n = 0;
		std::cin >> n;
		double **matrix = randomMatr(n);
		double *b = randomArray(n);
		auto t1 = std::chrono::high_resolution_clock::now();
		*matrVect(n, matrix, b);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		std::cout << duration;
		break;
	}
	case 3: 
	{
		srand(time(NULL));
		int n = 0;
		std::cin >> n;
		double **A = randomMatr(n);
		double **B = randomMatr(n);
		auto t1 = std::chrono::high_resolution_clock::now();
		matrixMatrix(A, B, n);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		std::cout << duration;
		break;
	}
	}
    return 0;
}

