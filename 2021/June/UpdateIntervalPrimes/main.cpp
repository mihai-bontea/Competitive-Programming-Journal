#include <bits/stdc++.h>
#define NMax 100001
#define VMax 1000000
#define maximum(x, y) ((x > y)? (x) : (y))

using namespace std;

bitset<VMax + 1> is_prime;
int N, Q;

struct
{
    bool lazy;

    int left_prime_length;
    int right_prime_length;
    int longest_prime_seq;
    int nr_primes;
}segment_tree[NMax * 3 + 7000];

struct packet
{
    int left_prime_length;
    int right_prime_length;
    int longest_prime_seq;

    packet(int _left_prime_length, int _right_prime_length, int _longest_prime_seq)
    {
        left_prime_length = _left_prime_length;
        right_prime_length = _right_prime_length;
        longest_prime_seq = _longest_prime_seq;
    }
};

ofstream fout("numbers_tree.out");

class InParser {
private:
    FILE *fin;
    char *buff;
    int sp;
    int res;

    char read_ch() {
        ++sp;
        if (sp == 4096) {
            sp = 0;
            res = fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }

public:
    InParser(const char* nume) {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
        res = 0;
    }

    InParser& operator >> (int &n) {
        char c;
        while (!isdigit(c = read_ch()) && sp != res);
    	n = c - '0';
        while (isdigit(c = read_ch()) && sp != res) {
            n = 10 * n + c - '0';
        }
        return *this;
    }

};

InParser fin("numbers_tree.in");

inline void build_tree(int node, int left, int right)
{
    if (left == right)
    {
        int val;
        fin >> val;
        segment_tree[node].left_prime_length = segment_tree[node].right_prime_length = 1 * is_prime[val];
        segment_tree[node].longest_prime_seq = segment_tree[node].nr_primes = 1 * is_prime[val];
    }
    else
    {
        int mid = (left + right) / 2;
        build_tree(2 * node, left, mid);
        build_tree(2 * node + 1, mid + 1, right);

        // If whole [2 * node] is prime, we might update [node].left_prime_length
        if (segment_tree[2 * node].left_prime_length == (mid - left + 1))
            segment_tree[node].left_prime_length = (mid - left + 1) + segment_tree[2 * node + 1].left_prime_length;
        else
            segment_tree[node].left_prime_length = segment_tree[2 * node].left_prime_length;

        // If whole [2 * node + 1] is prime, we might update [node].right_prime_length
        if (segment_tree[2 * node + 1].right_prime_length == (right - mid))
            segment_tree[node].right_prime_length = (right - mid) + segment_tree[2 * node].right_prime_length;
        else
            segment_tree[node].right_prime_length = segment_tree[2 * node + 1].right_prime_length;

        // Update longest_prime_seq
        int longest_prime_seq1 = maximum(segment_tree[2 * node].longest_prime_seq, segment_tree[2 * node + 1].longest_prime_seq);
        int longest_prime_seq2 = maximum(segment_tree[node].left_prime_length, segment_tree[node].right_prime_length);
        int longest_prime_seq3 = segment_tree[2 * node].right_prime_length + segment_tree[2 * node + 1].left_prime_length;
        segment_tree[node].longest_prime_seq = maximum(maximum(longest_prime_seq1, longest_prime_seq2), longest_prime_seq3);

        // Update nr_primes
        segment_tree[node].nr_primes = segment_tree[2 * node].nr_primes + segment_tree[2 * node + 1].nr_primes;
    }
}

inline void update_interval(int node, int left, int right, int x, int y, int val)
{
    if (x <= left && right <= y)
    {
        // Set node as lazy
        segment_tree[node].lazy = true;

        // Set left_prime_length and right_prime_length
        segment_tree[node].left_prime_length = segment_tree[node].right_prime_length = (right - left + 1) * is_prime[val];

        // Set longest_prime_seq and nr_primes
        segment_tree[node].longest_prime_seq = segment_tree[node].nr_primes = (right - left + 1) * is_prime[val];
    }
    else
    {
        int mid = (left + right) / 2;

        // Update children if lazy
        if (segment_tree[node].lazy)
        {
            // Mark node as no longer lazy
            segment_tree[node].lazy = false;

            // Update left_prime_length and right_prime_length
            segment_tree[2 * node].left_prime_length = segment_tree[2 * node].right_prime_length = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].left_prime_length = segment_tree[2 * node + 1].right_prime_length = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Update longest_prime_seq and nr_primes
            segment_tree[2 * node].longest_prime_seq = segment_tree[2 * node].nr_primes = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].longest_prime_seq = segment_tree[2 * node + 1].nr_primes = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Mark children as lazy
            segment_tree[2 * node].lazy = segment_tree[2 * node + 1].lazy = true;
        }

        if (x <= mid)
            update_interval(2 * node, left, mid, x, y, val);
        if (y > mid)
            update_interval(2 * node + 1, mid + 1, right, x, y, val);

        // If whole [2 * node] is prime, we might update [node].left_prime_length
        if (segment_tree[2 * node].left_prime_length == (mid - left + 1))
            segment_tree[node].left_prime_length = (mid - left + 1) + segment_tree[2 * node + 1].left_prime_length;
        else
            segment_tree[node].left_prime_length = segment_tree[2 * node].left_prime_length;

        // If whole [2 * node + 1] is prime, we might update [node].right_prime_length
        if (segment_tree[2 * node + 1].right_prime_length == (right - mid))
            segment_tree[node].right_prime_length = (right - mid) + segment_tree[2 * node].right_prime_length;
        else
            segment_tree[node].right_prime_length = segment_tree[2 * node + 1].right_prime_length;

        // Update longest_prime_seq
        int longest_prime_seq1 = maximum(segment_tree[2 * node].longest_prime_seq, segment_tree[2 * node + 1].longest_prime_seq);
        int longest_prime_seq2 = maximum(segment_tree[node].left_prime_length, segment_tree[node].right_prime_length);
        int longest_prime_seq3 = segment_tree[2 * node].right_prime_length + segment_tree[2 * node + 1].left_prime_length;
        segment_tree[node].longest_prime_seq = maximum(maximum(longest_prime_seq1, longest_prime_seq2), longest_prime_seq3);
        //segment_tree[node].longest_prime_seq = maximum(longest_prime_seq1, longest_prime_seq2);

        // Update nr_primes
        segment_tree[node].nr_primes = segment_tree[2 * node].nr_primes + segment_tree[2 * node + 1].nr_primes;
    }
}

inline int query_tree_nr_primes(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return segment_tree[node].nr_primes;
    else
    {
        int mid = (left + right) / 2;

        // Update children if lazy
        if (segment_tree[node].lazy)
        {
            // Mark node as no longer lazy
            segment_tree[node].lazy = false;

            // Update left_prime_length and right_prime_length
            segment_tree[2 * node].left_prime_length = segment_tree[2 * node].right_prime_length = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].left_prime_length = segment_tree[2 * node + 1].right_prime_length = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Update longest_prime_seq and nr_primes
            segment_tree[2 * node].longest_prime_seq = segment_tree[2 * node].nr_primes = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].longest_prime_seq = segment_tree[2 * node + 1].nr_primes = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Mark children as lazy
            segment_tree[2 * node].lazy = segment_tree[2 * node + 1].lazy = true;
        }

        int res1 = 0, res2 = 0;

        if (x <= mid)
            res1 = query_tree_nr_primes(2 * node, left, mid, x, y);
        if (y > mid)
            res2 = query_tree_nr_primes(2 * node + 1, mid + 1, right, x, y);

        return res1 + res2;
    }
}

inline packet query_tree_longest_prime_seq(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return packet(segment_tree[node].left_prime_length, segment_tree[node].right_prime_length, segment_tree[node].longest_prime_seq);
    else
    {
        int mid = (left + right) / 2;

        // Update children if lazy
        if (segment_tree[node].lazy)
        {
            // Mark node as no longer lazy
            segment_tree[node].lazy = false;

            // Update left_prime_length and right_prime_length
            segment_tree[2 * node].left_prime_length = segment_tree[2 * node].right_prime_length = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].left_prime_length = segment_tree[2 * node + 1].right_prime_length = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Update longest_prime_seq and nr_primes
            segment_tree[2 * node].longest_prime_seq = segment_tree[2 * node].nr_primes = (mid - left + 1) * (segment_tree[node].left_prime_length != 0);
            segment_tree[2 * node + 1].longest_prime_seq = segment_tree[2 * node + 1].nr_primes = (right - mid) * (segment_tree[node].left_prime_length != 0);

            // Mark children as lazy
            segment_tree[2 * node].lazy = segment_tree[2 * node + 1].lazy = true;
        }

        packet res1(-1, -1, -1);
        packet res2(-1, -1, -1);

        if (x <= mid)
            res1 = query_tree_longest_prime_seq(2 * node, left, mid, x, y);
        if (y > mid)
            res2 = query_tree_longest_prime_seq(2 * node + 1, mid + 1, right, x, y);

        if (res1.left_prime_length == -1)
            return res2;
        if (res2.left_prime_length == -1)
            return res1;

        int left_prime_length, right_prime_length, longest_prime_seq;

        // Set left_prime_length
        if (res1.left_prime_length == (mid - left + 1))
            left_prime_length = (mid - left + 1) + res2.left_prime_length;
        else
            left_prime_length = res1.left_prime_length;

        // Set right_prime_length
        if (res2.right_prime_length == (right - mid))
            right_prime_length = (right - mid) + res1.right_prime_length;
        else
            right_prime_length = res2.right_prime_length;

        // Set longest_prime_seq
        int longest_prime_seq1 = maximum(res1.longest_prime_seq, res2.longest_prime_seq);
        int longest_prime_seq2 = maximum(left_prime_length, right_prime_length);
        int longest_prime_seq3 = res1.right_prime_length + res2.left_prime_length;
        longest_prime_seq = maximum(maximum(longest_prime_seq1, longest_prime_seq2), longest_prime_seq3);

        return packet(left_prime_length, right_prime_length, longest_prime_seq);
    }
}

inline void initialize_sieve()
{
    is_prime.set();

    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= VMax; ++i)
        if (is_prime[i])
            for (int j = i + i; j <= VMax; j += i)
                is_prime[j] = false;
}

int main()
{
    initialize_sieve();

    fin >> N >> Q;
    build_tree(1, 1, N);

    int op, left, right, val;
    for (int i = 1; i <= Q; ++i)
    {
        fin >> op >> left >> right;
        if (op == 1)
        {
            fin >> val;
            update_interval(1, 1, N, left, right, val);
        }
        else if (op == 2)
            fout << (right - left + 1) - query_tree_nr_primes(1, 1, N, left, right) << '\n';
        else
            fout << query_tree_longest_prime_seq(1, 1, N, left, right).longest_prime_seq << '\n';
    }
    return 0;
}
