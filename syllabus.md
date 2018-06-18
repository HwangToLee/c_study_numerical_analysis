# C Study: for Numerical Analysis

## 0. Info

- Last Update: 2018.06.18
- Editor: 이성윤
- E-mail Contact: gomqual@gmail.com
- Source Location: https://github.com/GomPC/c_study

## 1. Objectives

### 1.1. 입문 교재 예제보다 복잡한 프로그램의 C를 이용한 구현

- 입문 교재(예시: 윤성우의 열혈 C 프로그래밍)에서 접하는 프로그램은 대개 500줄 이내로, 실전에서 접하는 문제보다 훨씬 작고 단순한 프로그램
- 당연히 프로그램을 많이 작성하다 보면 실력이 자연스럽게 늘겠지만, 가이드라인이 있다면 훨씬 빠르게 실력을 향상시킬 수 있음
- 그러나 중급 단계에서 참조하면 좋은 내용의 교재가 잘 없으며, 동기부여가 잘 안되는 경우도 있음
- 유명한 상용 프로그램(MATLAB)의 기능을 모방하며 언어와 문제해결력을 키워보자

###1.2. 수치해석기법을 이용한 수식 풀이 및 응용

- 수치해석기법은 과학 및 공학 분야의 데이터 분석에 많이 쓰이며, 컴퓨터를 사용하는 가장 근본적인 이유임
- 수학식의 해를 유도하여 푸는 것이 아니라(analytical), 숫자를 대입하고 계산하여 푸는 방법(numerical)을 통칭함
- 그러나 수학과 코딩을 모두 이해해야 하여 진입장벽이 높은 편이어서 어려워하는 사람이 많음
- 수치해석에서 비교적 간단한 기법을 직접 구현해보며 장벽을 깨고 큰 그림을 그려보자
- 추후 낮은 수준의 프로그램(예시: 게임 엔진)을 작성할 때 큰 도움이 됨

###1.3. 코딩 습관

- 프로그램을 잘 작성하려면 반드시 코딩 습관이 필요함
- 스터디 기간동안 매일 일정량의 목표를 세우고 달성하며 습관을 들여보자
- 특히 그 기간동안 git과 editor 등 개발자 도구를 익히고 대규모 프로그램을 작성하며 comment 작성의 노하우를 깨닫자

## 2. Pre-requisites

### 2.1. C 언어 문법 기본

- 적어도 문법 자체는 모두 익혀서 올 것
- 입문 교재 '윤성우의 열혈 C 프로그래밍'에 있는 내용을 기준으로 함

### 2.2. Git 사용법

- 개발자에게 Git는 숨쉬기와 같은 행동이므로, 사용법을 익힐 것
- CUI 대신 SourceTree를 사용해도 좋음
- 한 번도 사용해보지 않았으면 https://opentutorials.org/course/1492 강의를 참조할 것

### 2.3. C 언어 개발환경 선정 및 기능 숙지

- 각자 편한 개발환경을 준비하고 사용법을 익혀둘 것
- 선호가 없으면 Win-Visual Studio, Mac-Xcode 추천

## 3. Subjects

### 3.1. C Language Review

- Pointer
- Structure
- Multi-file Programming
- Dynamic Allocation

### 3.2. Data Structure & Algorithm

- Linked List
- Stack / Queue
- Sort (Insertion, Merge, Heap, Quick)
- Search (Binary Tree, Hash Function)

### 3.3. Numerical Basic

#### 3.3.1. General

- Newton's Method
- Interpolation (Spline)
- Integration
- Differentiation

#### 3.3.2. Linear Algebra

- Gaussian Elimination
- LU Factorization
- Iteration Method (Gauss-Seidel)
- Condition Number
- Curve Fitting (Least Square)

#### 3.3.3. Differential Equation

- Euler-Cauchy Method
- Runge-Kutta Method
- System of ODE
- PDE Solving

### 3.4. Signal Processing

#### 3.4.1. Signal and System

#### 3.4.2. Linear Filter

#### 3.4.3. Discrete Filter

#### 3.4.4. Fourier Transform

## 4. Schedule

### 4.1. Week1

### 4.2. Week2

### 4.3. Week3