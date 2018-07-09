

# C Language Review

## 0. Info

- Last Update: 2018.07.03
- Editor: 이성윤
- E-mail Contact: gomqual@gmail.com
- Source Location: https://github.com/GomPC/c_study_numerical



## 1. 고놈의 포인터

### 1.1. 함수로 인자 전달하기

- Call by Value Example

```c
#include <stdio.h>
int main(void)
{
    int a = 1, b = 2;
    swap(a, b); // call by value
    printf("%d, %d\n", a, b);
    
    return 0;
}

void swap(int m, int n)
{
    int tmp;
    tmp = m;
    m = n;
    n = tmp;
}
```

- Call by Reference Example

```c
#include <stdio.h>
int main(void)
{
    int a = 1, b = 2;
    swap(&a, &b); // call by reference
    printf("%d, %d\n", a, b);
    
    return 0;
}

void swap(int *m, int *n)
{
    int tmp;
    tmp = *m;
    *m = *n;
    *n = tmp;
}
```

- 함수의 입력 인자와 호출 인자는 형식이 동일해야 함
- int 변수를 입력하여 호출할 경우, 호출된 함수는 새로운 변수를 생성하고 int를 복사함
- int 포인터 변수를 입력하여 호출할 경우, 호출된 함수는 새로운 포인터 변수를 생성하고 int*를 복사함
- 변수는 그 자체로 의미를 갖는 값으로, 새로운 변수가 생성되면 이전 변수와 관계가 사라짐
- 포인터 변수는 포인터를 찾아갈 때 의미를 갖는 값으로, 새로운 포인터 변수가 생성되어도 동일한 변수를 가리키면 같은 값을 조작할 수 있음

### 1.2. 배열 접근하기

- 배열과 포인터는 내부적으로 완전히 동일하게 취급

```c
#include <stdio.h>
int main(void)
{
    int i, arr[100], *parr;
    parr = arr;
    for(i = 0; i < 100; i++)
    {
        arr[i] = i;
    }
    printf("%d=%d=%d=%d\n", arr[77], *(arr+77), *(77+arr), *(&arr[76]+1));
    printf("%d=%d=%d=%d\n", parr[77], *(parr+77), *(77+parr), *(&parr[76]+1));
    return 0;
}
```

- 함수의 인자에서도 배열은 포인터와 동일하게 취급(int arr[], int *arr)

### 1.3. 버블 정렬

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE (100)
void swap(int *m, int *n);
int main(void)
{
    int i, arr[ARR_SIZE], arrSort[ARR_SIZE];
    // generate random number
    srand((unsigned int)time(NULL));
    for(i=0; i<ARR_SIZE;i++)
    {
        arrSort[i] = arr[i] = rand();
    }
    // bubble sort (ascending)
    int count;
    do{
        count = 0;
        for(i=1; i<ARR_SIZE; i++)
        {
            if(arrSort[i-1]>arrSort[i])
            {
                swap(&arrSort[i-1], &arrSort[i]);
                count++;
            }
        }
    } while(count);
    // result
    printf("RAW\tSORT\n");
    for(i=0; i<ARR_SIZE; i++)
    {
        printf("%d\t%d\n", arr[i], arrSort[i]);
    }
    return 0;
}
void swap(int *m, int *n)
{
    int tmp;
    tmp = *m;
    *m = *n;
    *n = tmp;
}
```

- swap을 이용해서 bubble sort를 구현해보자
- 배열에서 처음부터 끝까지 바로 앞과 뒤의 값을 비교하여 역순일 경우 swap하는 과정을 반복
- 배열을 한바퀴 도는 동안 swap을 한 번도 실행하지 않으면 순차로 정렬된 것이므로 종료

### 1.4. 삽입 정렬

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE (100)
int main(void)
{
    int i, arr[ARR_SIZE], arrSort[ARR_SIZE];
    // generate random number
    srand((unsigned int)time(NULL));
    for(i=0; i<ARR_SIZE;i++)
    {
        arrSort[i] = arr[i] = rand();
    }
    // insertion sort (ascending)
    int pivot, pivotIdx;
    for(pivotIdx=1; pivotIdx<ARR_SIZE; pivotIdx++)
    {
        pivot = arrSort[pivotIdx];
        for(i=pivotIdx-1;i>=0;i--)
        {
            if(arrSort[i]>pivot)
                arrSort[i+1] = arrSort[i];
            else
                break;
        }
        arrSort[i+1] = pivot;
    }
    // result
    printf("RAW\tSORT\n");
    for(i=0; i<ARR_SIZE; i++)
    {
        printf("%d\t%d\n", arr[i], arrSort[i]);
    }
    return 0;
}
```

- insertion sort를 구현해보자
- 먼저 배열의 두 번째 값을 기준(pivot)으로 삼은 후, 그 값이 들어가야 할 자리를 앞에서 찾는 방식
- pivot보다 앞선 위치는 정렬된 상태로, pivot과 하나씩 비교하여 pivot을 끼워넣거나 뒤로 밀어냄
- pivot을 끼워넣은 후에는 정렬되지 않은 부분의 첫 번째가 새로운 pivot임
- 배열의 마지막까지 pivot으로 삼고 정렬 위치에 끼워넣으면 종료

## 2. 다이나믹하네

### 2.1. 데이터 수를 자유롭게

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i, n, *arr, *arrSort;
	printf("Data Size: ");
	scanf_s("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	arrSort = (int*)malloc(sizeof(int)*n);
	// generate random number
	srand((unsigned int)time(NULL));
	for (i = 0; i<n; i++)
	{
		arrSort[i] = arr[i] = rand();
	}
	// insertion sort (ascending)
	int pivot, pivotIdx;
	for (pivotIdx = 1; pivotIdx<n; pivotIdx++)
	{
		pivot = arrSort[pivotIdx];
		for (i = pivotIdx - 1; i >= 0; i--)
		{
			if (arrSort[i]>pivot)
				arrSort[i + 1] = arrSort[i];
			else
				break;
		}
		arrSort[i + 1] = pivot;
	}
	// result
	printf("INDEX\tRAW\tSORT\n");
	for (i = 0; i<n; i++)
	{
		printf("%d\t%d\t%d\n", i+1, arr[i], arrSort[i]);
	}
	free(arr);
	free(arrSort);
	return 0;
}
```

- 작동 후에 배열의 크기를 정할 경우 동적 할당으로 연결
- malloc() 쓸 때는 sizeof()를 이용하여 바이트 수를 계산하고, 대입할 때 캐스팅해주어야 함
- free()는 프로그램을 종료할 경우 안해도 자동으로 반환되지만, 종료하지 않는 종류의 프로그램일 경우 문제가 될 수 있으므로 직접 반환하는 습관이 필요함
- calloc()이나 realloc()도 있음

### 2.2. 시간 측정

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main(void)
{
	LARGE_INTEGER tic, toc, ticFreq;
    int i, n, *arr, *arrSort;
    QueryPerformanceFrequency(&ticFreq);
	printf("Data Size: ");
	scanf_s("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	arrSort = (int*)malloc(sizeof(int)*n);
	// generate random number
	srand((unsigned int)time(NULL));
	for (i = 0; i<n; i++)
	{
		arrSort[i] = arr[i] = rand();
	}
	// insertion sort (ascending)
	int pivot, pivotIdx;
    QueryPerformanceCounter(&tic);
	for (pivotIdx = 1; pivotIdx<n; pivotIdx++)
	{
		pivot = arrSort[pivotIdx];
		for (i = pivotIdx - 1; i >= 0; i--)
		{
			if (arrSort[i]>pivot)
				arrSort[i + 1] = arrSort[i];
			else
				break;
		}
		arrSort[i + 1] = pivot;
	}
    QueryPerformanceCounter(&toc);
	// result
    printf("Sorting Time: %.4f [sec]\n", (double)(toc.QuadPart - tic.QuadPart) / ticFreq.QuadPart);
	free(arr);
	free(arrSort);
	return 0;
}
```

- QueryPerformanceFrequency()와 QueryPerformanceCounter()로 정밀한 시간 측정 가능 (#include <Windows.h> 필요)

### 2.3. 큰 사이즈 난수 만들기

- rand()는 0~RAND_MAX 값(32767) 사이를 반환하므로, 큰 사이즈의 난수를 생성하면 중첩이 일어날 확률을 줄일 수 있음

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

long genRandInt32(void) // 0 ~ 2,147,483,647
{
	long res = rand() << 16 | rand() << 1 | (rand() % 2);
	return res;
}

long long genRandInt64(void) // 0 ~ 9,223,372,036,854,775,807
{	
	long long res = ((long long)rand()) << 48;
	res |= ((long long)rand()) << 33;
	res |= ((long long)rand()) << 18;
	res |= ((long long)rand()) << 3;
	res |= ((long long)rand())%8;
	return res;
}

int main(void)
{
	LARGE_INTEGER tic, toc, ticFreq;
    long long i, n, *arr, *arrSort;
    QueryPerformanceFrequency(&ticFreq);
	printf("Data Size: ");
	scanf_s("%lld", &n);
	arr = (long long*)malloc(sizeof(long long)*n);
	arrSort = (long long*)malloc(sizeof(long long)*n);
	// generate random number
	srand((unsigned int)time(NULL));
	for (i = 0; i<n; i++)
	{
		arrSort[i] = arr[i] = genRandInt64();
	}
	// insertion sort (ascending)
	long long pivot, pivotIdx;
    QueryPerformanceCounter(&tic);
	for (pivotIdx = 1; pivotIdx<n; pivotIdx++)
	{
		pivot = arrSort[pivotIdx];
		for (i = pivotIdx - 1; i >= 0; i--)
		{
			if (arrSort[i]>pivot)
				arrSort[i + 1] = arrSort[i];
			else
				break;
		}
		arrSort[i + 1] = pivot;
	}
    QueryPerformanceCounter(&toc);
	// result
    printf("Sorting Time: %.4f [sec]\n", (double)(toc.QuadPart - tic.QuadPart) / ticFreq.QuadPart);
    printf("INDEX\tRAW\tSORT\n");
	for (i = 0; i<n; i++)
	{
		printf("%lld\t%lld\t%lld\n", i+1, arr[i], arrSort[i]);
	}
	free(arr);
	free(arrSort);
	return 0;
}
```

### 2.4. 정렬 시간 비교하기

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void swap(long long *m, long long *n);
long genRandInt32(void); // 0 ~ 2,147,483,647
long long genRandInt64(void); // 0 ~ 9,223,372,036,854,775,807
void bubbleSort(long long arr[], long long n);
void insertionSort(long long arr[], long long n);
int main(void)
{
	LARGE_INTEGER tic, toc, ticFreq;
	long long i, start, end, step, *arr, *arrSort;
	QueryPerformanceFrequency(&ticFreq);
    
    printf("***** Sorting Time Comparison *****\n");
    printf("Data Size Start: ");
	scanf_s("%lld", &start);
    printf("Data Size End: ");
	scanf_s("%lld", &end);
    printf("Data Size Step: ");
	scanf_s("%lld", &step);
    
	arr = (long long*)malloc(sizeof(long long)*end);
	arrSort = (long long*)malloc(sizeof(long long)*end);
	
	// generate random number
	srand((unsigned int)time(NULL));
	for (i = 0; i<end; i++)
	{
		arr[i] = genRandInt64();
	}

	printf("Size\tInsertion\tBubble\n");
	for (i = start; i < end; i += step)
	{
		long long j;
		printf("%lld\t", i);

		// copy
		for (j = 0; j < i; j++)
		{
			arrSort[j] = arr[j];
		}
		// insertion sort
		QueryPerformanceCounter(&tic);
		insertionSort(arrSort, i);
		QueryPerformanceCounter(&toc);
		printf("%.4f\t", (double)(toc.QuadPart - tic.QuadPart) / ticFreq.QuadPart);

		// copy
		for (j = 0; j < i; j++)
		{
			arrSort[j] = arr[j];
		}
		// bubble sort
		QueryPerformanceCounter(&tic);
		bubbleSort(arrSort, i);
		QueryPerformanceCounter(&toc);
		printf("%.4f\n", (double)(toc.QuadPart - tic.QuadPart) / ticFreq.QuadPart);
	}
    free(arr);
    free(arrSort);
	return 0;
}

void swap(long long *m, long long *n)
{
	long long tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

long genRandInt32(void)
{
	long res = rand() << 16 | rand() << 1 | (rand() % 2);
	return res;
}

long long genRandInt64(void)
{	
	long long res = ((long long)rand()) << 48;
	res |= ((long long)rand()) << 33;
	res |= ((long long)rand()) << 18;
	res |= ((long long)rand()) << 3;
	res |= ((long long)rand())%8;
	return res;
}

void bubbleSort(long long arr[], long long n)
{
	long long i, count;
	do {
		count = 0;
		for (i = 1; i < n; i++)
		{
			if (arr[i - 1] > arr[i])
			{
				swap(&arr[i - 1], &arr[i]);
				count++;
			}
		}
	} while (count);
}

void insertionSort(long long arr[], long long n)
{
	long long i, pivot, pivotIdx;
	for (pivotIdx = 1; pivotIdx<n; pivotIdx++)
	{
		pivot = arr[pivotIdx];
		for (i = pivotIdx - 1; i >= 0; i--)
		{
			if (arr[i]>pivot)
				arr[i + 1] = arr[i];
			else
				break;
		}
		arr[i + 1] = pivot;
	}
}
```

- 동일한 난수 배열을 생성한 후 두 가지 정렬 방법의 소요시간 측정 및 비교
- 각 정렬 방법을 함수로 분리
- ![](.\01_1.png)

## 3. 멀티 먹자

### 3.1. 소스 길다

- main()만 남기고 나머지는 분리하자
- swap 구현 파일

```c
// swap.c
void swap(long long *m, long long *n)
{
	long long tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}
```

- swap 헤더 파일
- 헤더 파일은 중첩 포함될 가능성이 있으므로 #ifndef, #define, #endif로 감싸줄 것
- 주로 파일 이름을 이용하여 #define 문구를 결정

```c
// swap.h
#ifndef __SWAP_H__
#define __SWAP_H__
void swap(long long *m, long long *n);
#endif
```

- sorting 구현 파일
- sorting 내에서 swap()을 사용하므로, 헤더 파일 포함 필요

```c
// sort.c
#include "swap.h"
void bubbleSort(long long arr[], long long n)
{
	long long i, count;
	do {
		count = 0;
		for (i = 1; i < n; i++)
		{
			if (arr[i - 1] > arr[i])
			{
				swap(&arr[i - 1], &arr[i]);
				count++;
			}
		}
	} while (count);
}
void insertionSort(long long arr[], long long n)
{
	long long i, pivot, pivotIdx;
	for (pivotIdx = 1; pivotIdx<n; pivotIdx++)
	{
		pivot = arr[pivotIdx];
		for (i = pivotIdx - 1; i >= 0; i--)
		{
			if (arr[i]>pivot)
				arr[i + 1] = arr[i];
			else
				break;
		}
		arr[i + 1] = pivot;
	}
}
```

- sorting 헤더 파일

```c
// sort.h
#ifndef __SORT_H__
#define __SORT_H__
void bubbleSort(long long arr[], long long n);
void insertionSort(long long arr[], long long n);
#endif
```

- genRand 구현 파일
- genRandInit() 추가
- 전역변수 genRandCK로 초기화가 되어 있지 않을 경우 genRandInit() 추가
- 한 번 초기화되었을 경우, 중복 실행하지 않음

```c
// genRand.c
#include <stdlib.h>
#include <time.h>
int genRandCK = 0;
void genRandInit(void)
{
	if (!genRandCK)
	{
		srand((unsigned int)time(NULL));
		genRandCK = 1;
	}
}
long genRandInt32(void)
{
	long res;
	if (!genRandCK) genRandInit();
	res = rand() << 16 | rand() << 1 | (rand() % 2);
	return res;
}
long long genRandInt64(void)
{
	long long res;
	if (!genRandCK) genRandInit();
	res = ((long long)rand()) << 48;
	res |= ((long long)rand()) << 33;
	res |= ((long long)rand()) << 18;
	res |= ((long long)rand()) << 3;
	res |= ((long long)rand()) % 8;
	return res;
}
```

- genRand 헤더 파일

```c
// genRand.h
#ifndef __GENRAND_H__
#define __GENRAND_H__
void genRandInit(void);
long genRandInt32(void); // 0 ~ 2,147,483,647
long long genRandInt64(void); // 0 ~ 9,223,372,036,854,775,807
#endif
```

- preciseTime 구현 파일
- 관련된 변수를 struct로 정리, 형식은 헤더에서 선언
- PreciseTimeInit()를 추가, PreciseTimeToc()에서 PreciseTime.initCK가 체크되지 않을 경우 자동 실행

```c
// preciseTime.c
#include "preciseTime.h"
PreciseTimeType PreciseTime = {
	0,	// int initCK;
	0,	// LARGE_INTEGER tic;
	0,	// LARGE_INTEGER toc;
	0	// LARGE_INTEGER ticFreq;
};
void PreciseTimeInit(void)
{
	if (!PreciseTime.initCK)
	{
		PreciseTime.initCK = 1;
		QueryPerformanceFrequency(&PreciseTime.ticFreq);
	}
}
LARGE_INTEGER PreciseTimeTic(void)
{
	QueryPerformanceCounter(&PreciseTime.tic);
	return PreciseTime.tic;
}
double PreciseTimeToc(void)
{
	QueryPerformanceCounter(&PreciseTime.toc);
	if (!PreciseTime.initCK)
	{
		PreciseTimeInit();
	}
	return (double)(PreciseTime.toc.QuadPart - PreciseTime.tic.QuadPart) / PreciseTime.ticFreq.QuadPart;
}
```

- preciseTime 헤더 파일
- struct는 typedef를 이용하여 선언

```c
// preciseTime.h
#ifndef __PRECISETIME_H__
#define __PRECISETIME_H__
#include <Windows.h>
typedef struct _PreciseTimeType_
{
	int initCK;
	LARGE_INTEGER tic;
	LARGE_INTEGER toc;
	LARGE_INTEGER ticFreq;
} PreciseTimeType;
void PreciseTimeInit(void);
LARGE_INTEGER PreciseTimeTic(void);
double PreciseTimeToc(void);
#endif
```

- main 파일
- 헤더를 포함하여 구현한 함수 사용
- swap()은 main.c에서 사용하지 않았으므로 헤더 포함 불필요

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "genRand.h"
#include "preciseTime.h"

int main(void)
{
	long long i, start, end, step, *arr, *arrSort;
	printf("***** Sorting Time Comparison *****\n");
	printf("Data Size Start: ");
	scanf_s("%lld", &start);
	printf("Data Size End: ");
	scanf_s("%lld", &end);
	printf("Data Size Step: ");
	scanf_s("%lld", &step);

	arr = (long long*)malloc(sizeof(long long)*end);
	arrSort = (long long*)malloc(sizeof(long long)*end);

	// generate random number
	srand((unsigned int)time(NULL));
	for (i = 0; i<end; i++)
	{
		arr[i] = genRandInt64();
	}

	printf("Size\tInsertion\tBubble\n");
	for (i = start; i <= end; i += step)
	{
		long long j;
		printf("%lld\t", i);

		// copy
		for (j = 0; j < i; j++)
		{
			arrSort[j] = arr[j];
		}
		// insertion sort
		PreciseTimeTic();
		insertionSort(arrSort, i);
		printf("%.4f\t", PreciseTimeToc());

		// copy
		for (j = 0; j < i; j++)
		{
			arrSort[j] = arr[j];
		}
		// bubble sort
		PreciseTimeTic();
		bubbleSort(arrSort, i);
		printf("%.4f\n", PreciseTimeToc());
	}
	free(arr);
	free(arrSort);
	return 0;
}
```

### 3.2. 소스 또쓸래


