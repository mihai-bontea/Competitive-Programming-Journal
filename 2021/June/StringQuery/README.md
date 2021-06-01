# StringQuery

## Problem statement

A string **s** of length **n** is given along with **q** queries of type **(op, x, y)**
where **op** can be either **0** or **1**. If **op** is **1**, then the character on
the position **x** will become **y**. If **op** is **0**, the number of distinct
characters from the interval **[x, y]** will be written to standard output.

## Restrictions and remarks

* 1 <= n <= 5.000.000
* 1 <= q <= 250.000
* s is formed only of lowercase letters

## Example

#### Input
```
4
aaaa
4
1 2 b
1 3 c
0 1 2
0 2 4
```

#### Output
```
2
3
```


## Solution

Due to the high number of queries, the data structure I chose is a **segment tree**, where every node will hold the set of letters that its corresponding interval contains.
Additionally, *segment_tree[node] = segment_tree[2 * node] ∪ segment_tree[2 * node + 1]*.

A frequency array could be used for the set implementation, but since the string can only contain lowercase letters, a space and time efficient solution would be to **use a
single integer as a representation for a set**. When the set contains the i-th letter of the alphabet, the i-th bit will be set to 1. Conveniently, performing **set union**
is done by simply performing **bitwise or** on two integers.

#### Example

Union of a set containing the letter 'a' with a set containing the letter 'z'(last 6 bits are unused).
```
10000000.00000000.00000000.00000000 |
00000000.00000000.00000000.01000000
===================================
10000000.00000000.00000000.01000000
```

