

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
    swap(&a, &b); // call by value
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
    srand(time(NULL));
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
    srand(time(NULL));
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

### 2.1. 정렬 시간 비교하기

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ARR_SIZE (100000)
void swap(INT64 *m, INT64 *n);
int genRandInt32(void); // 0 ~ 2,147,483,647
INT64 genRandInt64(void); // 0 ~ 9,223,372,036,854,775,807
void bubbleSort(INT64 arr[], INT64 n);
void insertionSort(INT64 arr[], INT64 n);
int main(void)
{
	LARGE_INTEGER tic, toc, ticFreq;
	INT64 i, mult, *arr, *arrSort;

	QueryPerformanceFrequency(&ticFreq);
	arr = (INT64*)calloc(sizeof(INT64), ARR_SIZE);
	arrSort = (INT64*)calloc(sizeof(INT64), ARR_SIZE);
	
	// generate random number
	srand(time(NULL));
	for (i = 0; i<ARR_SIZE; i++)
	{
		arr[i] = genRandInt64();
	}

	printf("***** Sorting Time Comparison *****\n");
	printf("Size\tInsertion\tBubble\n");

	mult = 10;
	for (i = 1000; i < ARR_SIZE; i += mult)
	{
		INT64 j;
		printf("%ld\t", i);

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

		if (i < 100) mult = 10;
		else if (i < 1000) mult = 100;
		else if (i < 10000) mult = 1000;
	}
    free(arr);
    free(arrSort);
	return 0;
}

void swap(INT64 *m, INT64 *n)
{
	INT64 tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

int genRandInt32(void)
{
	int res = rand() << 16 | rand() << 1 | (rand() % 2);
	return res;
}

INT64 genRandInt64(void)
{	
	INT64 res = ((INT64)rand()) << 48;
	res |= ((INT64)rand()) << 33;
	res |= ((INT64)rand()) << 18;
	res |= ((INT64)rand()) << 3;
	res |= ((INT64)rand())%8;
	return res;
}

void bubbleSort(INT64 arr[], INT64 n)
{
	// bubble sort (ascending)
	INT64 i, count;
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

void insertionSort(INT64 arr[], INT64 n)
{
	INT64 i, pivot, pivotIdx;
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
- rand()는 0에서 RAND_MAX 값(32767) 사이를 반환하므로, 큰 사이즈의 난수를 생성하면 중첩이 일어날 확률을 줄일 수 있음
- 각 정렬 방법을 함수로 분리
- 정밀한 시간 측정 방식 QueryPerformance-
- ![](.\01_1.png)

## 3. 멀티 먹자

### 3.1. 소스 길다



### 3.2. 소스 또쓸래







## 4. 구조체 



