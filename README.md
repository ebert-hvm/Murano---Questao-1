
# Desafio Murano Group: Questão 1
C++ implementation of merge sort, quick sort and bubble sort, sorting algorithms and their time execution analysis. Development environment: Visual Studio Code

## Getting Started

### Prerequisites

- Python 2.7 or newer;
- Required libraries: matplotlib
- C++11 (or newer) compiler

### Installation

- Clone repository:
```
git clone https://github.com/ebert-hvm/Murano-Questao-1.git
```
- Compile "main.cpp":
```
g++ -std=c++11 main.cpp -o main
```
- Install Python dependencies:
```
pip install matplotlib
```

## Usage

- Run the C++ program:
```
./main
```
This will create the txt file with the algorithms calculations.
- Run "plot.py" script
```
python plot.py
```
This will create the "plot.png" file with the time execution plot.
## Observations
- The algorithm with less complexity is the merge sort with O(nlog(n)) complexity. The bubble sort has O(n^2) complexity as well as quick sort.

- Despite the higher complexity, quick sort has an average complexity of O(nlog(n)) which explains why its performance is so close to merge sort.

- It was not performed the calculation for N = 10^9 because of the high execution time for all three algorithms. However the time was measured for 8 values of N from 10 to 10^8.
- Again, the time execution for N greater than 10^6 was too high for the bubble sort so it was ignored.

