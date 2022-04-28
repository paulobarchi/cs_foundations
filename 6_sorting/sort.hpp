//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 5 - Sort (Ordenação)		//
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 28/05/2017                            //
//==================================================//

#include <vector>
#include <algorithm>

// ## SelectionSort ##
void selectionSort(std::vector<int>& A, int n)
{
	int smaller;
	for (int i = 0; i <= n; ++i)
	{
		smaller = i;
		for (int j = i + 1; j <= n; ++j)
		{
			if (A[j] < A[smaller])
				smaller = j;
		}
		std::swap(A[i], A[smaller]);
	}
}

// ## InsertionSort ##
void insertionSort(std::vector<int>& A, int n)
{
	int i;
	for (int j = 1; j <= n; ++j)
	{
		int v = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > v)
		{
			A[i + 1] = A[i];
			--i;
		}
		A[i + 1] = v;
	}
}

// ## ShellSort ##
void shellSort(std::vector<int>& A, int n)
{
	int h = 1;
	int j, x;

	while (h <= n) {
		h *= 3;
		++h;
	}

	while (h > 1)
	{
		h /= 3;

		for (int i = h; i <= n; ++i)
		{
			x = A[i];
			j = i;

			while (j >= h && A[j - h] > x)
			{
				A[j] = A[j - h];
				j -= h;
			}

			A[j] = x;
		}
	}
}

// ## HeapSort ##
// HeapSort - FixDownHeap
void fixDownHeap(std::vector<int>& A, int n, int pos)
{
	int v = A[pos];
	int j = 2 * pos;

	while (j <= n) 
	{
		if (j < n && A[j] < A[j + 1])
			++j;
		if (v >= A[j]) // v's position found
			break;
		A[j / 2] = A[j];
		j *= 2;
	}
	A[j / 2] = v;
}

// HeapSort - heapify
void heapify(std::vector<int>& A, int n)
{
	for (int k = n / 2; k > 0; --k)
		fixDownHeap(A, n, k);
}

// heapSort
void heapSort(std::vector<int>& A, int n)
{
	heapify(A, n);

	for (int i = n; i > 0; --i)
	{
		std::swap(A[0], A[i]);		
		fixDownHeap(A, i - 1, 0);
	}
}

// ## MergeSort ##
// MergeSort - merge prototype
void merge(std::vector<int>& A, int l, int p, int r);

// mergeSort
void mSort(std::vector<int>& A, int l, int r)
{
	if (l < r)
	{
		int p = l + (r  - l) / 2;
		mSort(A, l, p);
		mSort(A, p + 1, r);
		merge(A, l, p, r);
	}
}
// MergeSort - merge
void merge(std::vector<int>& A, int l, int p, int r)
{
	int i, j, k;
	int n1 = p - l + 1;		// last index for L
	int n2 = r - p;			// last index for R

	// auxiliar vectors
	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (i = 0; i < n1; ++i)
		L[i] = A[l + i];
	for (j = 0; j < n2; ++j)
		R[j] = A[p + 1 + j];

	i = 0;
	j = 0;
	k = l;

	// main loop - merge auxiliar vectors back into vector A
	while (i < n1 && j < n2)
	{		
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}
		++k;
	}

	// remain elements of vector L, if there are any
	while (i < n1)
	{
		A[k] = L[i];
		++i;
		++k;
	}

	// remain elements of vector R, if there are any
	while (j < n2)
	{
		A[k] = R[j];
		++j;
		++k;
	}
}

void mergeSort(std::vector<int>& A, int n)
{
	mSort(A, 0, n);
}

// ## QuickSort ##
// QuickSort - partition
void partition(std::vector<int>& A, int l, int r, int &i, int &j)
{
	i = l;
	j = r;

	int x = A[(i + j) / 2];

	do
	{
		while (x > A[i]) i++;
		while (x < A[j]) j--;
		if (i <= j) {
			std::swap(A[i], A[j]);
			i++;
			j--;
		}
	} while (i <= j);

}

// quickSort
void qSort(std::vector<int>& A, int l, int r)
{
	int i, j;
	partition(A, l, r, i, j);
	if (l < j) qSort(A, l, j);
	if (i < r) qSort(A, i, r);	
}

void quickSort(std::vector<int>& A, int n)
{
	qSort(A, 0, n);
}

// std
void stdSort(std::vector<int>& A, int n)
{
	std::sort(A.begin(), A.end());
}

void stdStableSort(std::vector<int>& A, int n)
{
	std::stable_sort(A.begin(), A.end());
}

void stdSortHeap(std::vector<int>& A, int n)
{
	std::make_heap(A.begin(), A.end());
	std::sort_heap(A.begin(), A.end());
}