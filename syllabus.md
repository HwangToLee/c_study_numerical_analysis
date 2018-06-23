# C Study: for Numerical Analysis

## 0. Info

- Last Update: 2018.06.23
- Editor: 이성윤
- E-mail Contact: gomqual@gmail.com
- Source Location: https://github.com/GomPC/c_study_numerical_analysis



## 1. Objectives

### 1.1. 대규모 프로그램의 C를 이용한 구현

- 입문 교재(예시: 윤성우의 열혈 C 프로그래밍)에서 접하는 프로그램은 대개 500줄 이내로, 실전에서 접하는 문제보다 훨씬 작고 단순한 프로그램
- 당연히 프로그램을 많이 작성하다 보면 실력이 자연스럽게 늘겠지만, 가이드라인이 있다면 훨씬 빠르게 실력을 향상시킬 수 있음
- 그러나 중급 단계에서 참조하면 좋은 내용의 교재가 잘 없으며, 동기부여가 잘 안되는 경우도 있음
- 유명한 상용 프로그램(MATLAB)의 기능을 모방하며 언어와 문제해결력을 키워보자

###1.2. 수치해석기법을 이용한 수식 풀이 및 응용

- 수치해석기법은 과학 및 공학 분야의 데이터 분석에 많이 쓰이며, 컴퓨터를 사용하는 가장 근본적인 이유임
- 수학식의 해를 유도하여 푸는 것이 아니라(analytical), 숫자를 대입하고 계산하여 푸는 방법(numerical)을 통칭함
- 그러나 수학과 코딩을 모두 이해해야 하여 진입장벽이 높은 편이어서 어려워하는 사람이 많음
- 수치해석에서 비교적 간단한 기법을 직접 구현해보며 장벽을 깨고 큰 그림을 그려보자
- 추후 낮은 수준의 프로그램(예시: 라이브러리, 엔진)을 작성할 때 큰 도움이 됨

###1.3. 코딩 습관

- 프로그램을 잘 작성하려면 반드시 코딩 습관이 필요함
- 스터디 기간동안 매일 일정량의 목표를 세우고 달성하며 습관을 들여보자
- git과 editor 등 개발자 도구를 익히고 프로그램을 작성하며 comment 작성의 노하우를 깨닫자



## 2. Pre-requisites

### 2.1. C 언어 문법 기본

- 적어도 문법은 모두 익혀서 올 것
- 입문 교재 '윤성우의 열혈 C 프로그래밍'에 있는 내용을 기준으로 함

### 2.2. Git 사용법

- 개발자에게 Git는 숨쉬기와 같은 행동이므로, 사용법을 익힐 것
- CUI 대신 SourceTree를 사용해도 좋음
- 한 번도 사용해보지 않았으면 https://opentutorials.org/course/1492 강의를 참조할 것

### 2.3. C 언어 개발환경 선정 및 기능 숙지

- 각자 편한 개발환경을 준비하고 사용법을 익혀둘 것
- 선호가 없으면 Win-Visual Studio, Mac-Xcode가 편하므로 추천, 가벼운 프로그램은 CodeBlock 추천



## 3. Subjects

- 각 주제는 심도 있게 다루기보다, 근본적이고 간단하며 많이 쓰이는 대표적인 방식을 제한적으로 다룰 예정
- 가급적 실제 문제에 대한 적용 위주로 설명 및 연습

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
- Integration (Simpson)
- Differentiation

#### 3.3.2. Linear Algebra

- System Solver (Gaussian Elimination, LU Factorization, Gauss-Seidel)
- Condition Number (Norm)
- Curve Fitting (Least Square)

#### 3.3.3. Differential Equation

- ODE Solver (Euler-Cauchy Method, Runge-Kutta Method)
- System of ODE
- PDE Solver

### 3.4. Signal Processing

#### 3.4.1. Signal and System

- Impulse Response
- Convolution

#### 3.4.2. Digital Filter

- FIR / IIR Filter
- Bilinear Transform

#### 3.4.3. Fourier Transform

- Frequency Domain
- FFT



## 4. Schedule

### 4.1. Phase 1: Interactive Shell 만들기

#### 4.1.1. Interactive Shell 만들기

- python, MATLAB 등 실시간으로 수식을 입력하고 함수를 실행하는 CUI
- 값 저장, 수식 해석, 함수 연결 등 구현

### 4.2. Phase 2: 여러 종류의 Solver 만들기

#### 4.2.1. f(x)=0 풀기

- 단일 변수 방정식의 근사값 계산

#### 4.2.2. Ax=b 풀기

- 다변수 연립방정식의 근사값 계산
- 행렬 연산으로 변환

#### 4.2.3. y''+ay'+by=c 풀기

- 선형 미분방정식의 근사값 계산
- 시간에 대한 함수 위주

### 4.3. Phase 3: Simulation 만들기

#### 4.3.1. Wave 시뮬레이션

- 1차원 선의 파동 전달
- 2차원 평면의 파동 전달

#### 4.3.2. Solar 시뮬레이션

- 태양계의 만유인력을 통한 공전

### 4.4. Phase 4: System 만들기

#### 4.4.1. Key tone 인식기

- 전화 버튼 소리 인식

#### 4.4.2. FFT Image Filter 

- 이미지 필터 적용

