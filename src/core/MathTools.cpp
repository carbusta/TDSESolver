#include "MathTools.h"
#include "blas_externs.h"

namespace vtls {

	void addArraysImag(int len, std::complex<double>* arr1, double* arr2targ) {
		for (int i = 0; i < len; i++)
			arr2targ[i] += std::imag(arr1[i]);
	}

	void scaMulArray(int len, std::complex<double> scalar, std::complex<double> *__restrict arr) {
		/*for (int i = 0; i < len; i++)
			arr[i] *= scalar;*/
		cblas_zscal(len, &scalar, arr, 1);
	}

	void scaMulArray(int len, double scalar, double* __restrict arr) {
		cblas_dscal(len, scalar, arr, 1);
	}

	void scaMulArray(int len, double scalar, std::complex<double> *__restrict arr) {
		/*for (int i = 0; i < len; i++)
			arr[i] *= scalar;*/
		cblas_zdscal(len, scalar, arr, 1);
	}

	void copyArray(int len, double *__restrict arr1, double *__restrict arr2) {
		/*for (int i = 0; i < len; i++)
			arr2[i] = arr1[i];*/
		cblas_dcopy(len, arr1, 1, arr2, 1);
	}

	void copyArray(int len, std::complex<double> *__restrict arr1, std::complex<double> *__restrict arr2) {
		/*for (int i = 0; i < len; i++)
			arr2[i] = arr1[i];*/
		cblas_zcopy(len, arr1, 1, arr2, 1);
	}

	void copyArray(int len, double* __restrict arr1, std::complex<double>* __restrict arr2) {
		for (int i = 0; i < len; i++)
			arr2[i] = arr1[i];
	}

	template <typename T>
	void copyArrayRe(int len, T* __restrict arr1, double* __restrict arr2){
		for (int i = 0; i < len; i++)
			arr2[i] = std::real(arr1[i]);
	}

	int findValue(int len, double *__restrict arr, double val) {
		for (int i = 0; i < len; i++)
			if (arr[i] >= val)
				return i;
		if (val > arr[len - 1])
			return len - 1;
		else
			return -1;
	}

	//idxs should be initialized by user
	void insertSort_idxs(int len, double *__restrict arr, int *__restrict idxs) {

		int i = 1, j;
		double tempA, tempI;

		while (i < len) {

			j = i;

			while (j > 0 && arr[j - 1] > arr[j]) {

				tempA = arr[j];
				tempI = idxs[j];

				arr[j] = arr[j - 1];
				idxs[j] = idxs[j - 1];

				arr[j - 1] = tempA;
				idxs[j - 1] = tempI;

				j--;

			}

			i++;

		}
	}
}

namespace vtlsPrnt {
	void printGraph(int n, double *__restrict arr) {
		double minVal = *std::min_element(arr, arr + n);
		double maxVal = *std::max_element(arr, arr + n);
		int * nArr = (int*) sq_malloc(n * sizeof(int));
		int k = n / 50 + 1;
		for (int i = 0; i < n; i += k) nArr[i] = (int)(((arr[i] - minVal) / (maxVal - minVal)) * 100.0);
		//printArray(n, nArr);
		for (int i = 0; i < n; i += k) {
			for (int j = 0; j < nArr[i]; j++)
				std::cout << "#";
			std::cout << std::endl;
		}

		sq_free(nArr);
	}

	void printGraph(int n, std::complex<double>* __restrict arr0) {
		double* arr = (double*) sq_malloc(n * sizeof(double));
		for (int i = 0; i < n; i++)
			arr[i] = std::real(arr0[i]);
		double minVal = *std::min_element(arr, arr + n);
		double maxVal = *std::max_element(arr, arr + n);
		int* nArr = (int*) sq_malloc(n * sizeof(int));
		int k = n / 50 + 1;
		for (int i = 0; i < n; i += k) nArr[i] = (int)(((arr[i] - minVal) / (maxVal - minVal)) * 100.0);
		//printArray(n, nArr);
		for (int i = 0; i < n; i += k) {
			for (int j = 0; j < nArr[i]; j++)
				std::cout << "#";
			std::cout << std::endl;
		}

		sq_free(arr);
		sq_free(nArr);
	}
}