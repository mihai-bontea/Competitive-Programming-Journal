# Simple

Translated from https://www.pbinfo.ro/probleme/3225/simple

## Problem statement

**N** numbers are given along with **Q** operations of type:

* **0 a b val**: **val** is added to all elements in the **[a, b]** interval.

* **1 a b**: display the minimum even element and the maximum odd element in the **[a, b]** interval, or alternatively **-1** as a placeholder if one of them doesn't exist. 

## Restrictions and remarks

* **N**, **Q** <= 200.000
* The numbers given are between 1 and 2.000.000.000
* Memory: 256 MB / 8 MB
* Time limit: 1 second

## Example

#### Input
```
7
5 6 3 1 9 8 5
10
1 2 5
0 2 3 2
1 2 4
0 2 7 3
1 2 4
1 4 7
0 5 7 1
1 1 6
1 1 2
1 3 4
```

#### Output
```
6 9
8 5
4 11
4 11
4 13
-1 11
4 -1
```
## Solution

This problem is solved with segment trees, and since a whole interval can be updated at once, lazy propagation is used. Each node will hold **min_even** and **max_odd**, and their values
will be computed as follows: 

* current_node.min_even = min(left_node.min_even, right_node.min_even)
* current_node.max_odd = max(left_node.max_even, right_node.max_even)

However, after an operation of type **0(update)**, if an odd value is added, it will reverse the parity of all elements in the given interval. So it is necessary to also hold
**min_odd** and **max_even**, which will become **min_even** and **max_odd** after the odd value is added to them.

![1](https://user-images.githubusercontent.com/79721547/122611810-a2c7cf00-d08a-11eb-8ad6-13b54b40cc51.png)

## Squeezing the last drop of efficiency

```
// Makes cin faster
ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
```

By adding this line, cin is getting faster which is important since we are reading a lot of numbers. Surprisingly, this enables me to pass the rest of the tests.

![2](https://user-images.githubusercontent.com/79721547/122612004-0520cf80-d08b-11eb-9523-eccaa035eba4.png)

