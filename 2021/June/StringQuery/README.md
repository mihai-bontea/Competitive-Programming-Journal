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
```4
aaaa
4
1 2 b
1 3 c
0 1 2
0 2 4
```

#### Output
```2
3
```


