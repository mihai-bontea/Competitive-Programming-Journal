# Numbers-tree

Translated from https://www.pbinfo.ro/probleme/3600/numbers-tree

## Problem statement

A list of positive integers indexed from 1 is given. On this list 3 types of operations are applied:

* **1 left right val** - all values **a[i]** with **i** belonging to **[left, right]** become **val**.

* **2 left right** - display how many elements from the interval **[left, right]** are NOT prime.

* **3 left right** - display the length of the longest sequence of prime numbers found in the interval **left, right]**(consecutive positions).

## Restrictions and remarks

* 1 <= n, Q <= 100.000

* 2 <= a[i], val <= 1.000.000

* 1 <= left <= right <= n

* Memory: 8MB/4MB

## Example

#### Input
```
7 7
2 3 4 5 6 7 8
2 1 7
3 1 7
1 2 5 4
2 2 5
3 2 5
1 2 4 3
3 1 6
```

#### Output
```
3
2
4
0
4
```
## Solution

* Since the numbers are not particularly large, I used the sieve of Eratosthenes. Initially I used a bool array, but after some problems with memory I switched to a **bitset**.

* Since the update operations work on an interval rather than a single index, **lazy propagation** is used, which makes the time complexity of an update **O(log n)**.

* For the type 3 operation which is more challenging, I needed to add 3 **int**(short will not work here because of overflows) to the struct: **left_prime_length**, 
**right_prime_length**, **longest_prime_seq**. So for a particular node, the longest prime sequence will be the maximum between the longest prime sequence of its
left and right child, or the sum of **right_prime_length** of the left child and **left_prime_lengt** of the right child.

![1](https://user-images.githubusercontent.com/79721547/120897309-151dc580-c62e-11eb-976a-d1fb65d3fa64.png)

## Squeezing the last drop of efficiency

Inlining the functions decreases the time further.

Since the size of the input file is large, **input file parsing** is used, which makes a huge difference(see time below).

![2](https://user-images.githubusercontent.com/79721547/120897429-ca507d80-c62e-11eb-982e-21cd0ab33c59.png)

I used https://www.infoarena.ro/parsare-fisier-intrare as inspiration for parsing.
However, that version will cause some tests to fail because it doesn't take the return value of **fread** into account. The fix is available in my final code.

