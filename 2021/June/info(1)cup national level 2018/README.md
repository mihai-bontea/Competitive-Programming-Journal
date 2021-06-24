# Cambridge

https://www.pbinfo.ro/probleme/3230/cambridge
https://www.info1cup.com/archive/2018/national/task5/

## Example

#### Input
```
4 3
1 10
14 18
2 7
10 12
3 4
2 4
1 3
```

#### Output
```
0
0
1
```
## Solution

Since the numbers D[i] are really large, a dynamically allocated segment tree is used.

![1](https://user-images.githubusercontent.com/79721547/123297289-1e5ccc80-d520-11eb-9a38-a7ef623a4328.png)

From the official solution, I removed the function call for **change** from **while(!query())** since it was redundant(we are only moving towards right, there is no need to 'remove'
a node over which we will not iterate again).
In addition, an improvement is noticed if one only propagates when **node->lazy** is different from 0.

![2](https://user-images.githubusercontent.com/79721547/123297413-39c7d780-d520-11eb-9f5e-0aca8ce05b43.png)

## Squeezing the last drop of efficiency

After inlining the functions:

![3](https://user-images.githubusercontent.com/79721547/123297468-44826c80-d520-11eb-9c79-d6c160e608e0.png)


