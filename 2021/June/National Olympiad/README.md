# Lexicographic

Translated from https://www.pbinfo.ro/probleme/3059/lexicografic

## Problem statement

A list **v** formed from positive integers, not necessarily distinct, is given. On this list, we can perform only one type of operation: swapping two consecutive elements. 

Given a number **K**, display the list which can be created using at most **K** swaps that is lexicographically minimal.

## Restrictions and remarks

* 1 <= N <= 250.000
* T <= 2500
* 1 <= K <= N(N - 1) / 2
* 1 <= V[i] <= N 

## Example

#### Input
```
3
5 2
4 2 3 1 1
4 3
2 1 3 4
6 4
5 3 5 3 4 6
```

#### Output
```
2 3 4 1 1
1 2 3 4
3 3 5 4 5 6
```

## Solution

* K = N(N - 1) / 2 - ideal situation, we can apply any type of sort.

* Otherwise, segment trees can be used to find the minimum in the interval [1, min(K + 1, N)] of numbers which were not moved yet. So in addition to a variable containing the position
of the minimum element, a variable containing the number of unmoved elements is kept. 

![1](https://user-images.githubusercontent.com/79721547/121079080-61116b80-c7e2-11eb-8bf5-c4763a48f103.png)

## Squeezing the last drop of efficiency

After inlining the functions:

![2](https://user-images.githubusercontent.com/79721547/121079165-7a1a1c80-c7e2-11eb-8520-16cc34ddc25c.png)

After adding input file parsing:

![3](https://user-images.githubusercontent.com/79721547/121079186-830aee00-c7e2-11eb-9589-8c86a9758827.png)