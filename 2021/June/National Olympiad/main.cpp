#include <bits/stdc++.h>
#define NMax 250001
#define MAX 0xFFFFFF

using namespace std;

ofstream fout("lexicografic.out");

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

    InParser& operator >> (long long &n) {
        char c;
        while (!isdigit(c = read_ch()) && sp != res);
    	n = c - '0';
        while (isdigit(c = read_ch()) && sp != res) {
            n = 10 * n + c - '0';
        }
        return *this;
    }

};

InParser fin("lexicografic.in");

struct tree
{
    int nr_elems;
    int pos_min;
}segment_tree[NMax * 4];

int elements[NMax];

inline void build_tree(int node, int left, int right)
{
    if (left == right)
    {
        segment_tree[node].pos_min = left;
        segment_tree[node].nr_elems = 1;
    }
    else
    {
        int mid = (left + right) / 2;
        build_tree(2 * node, left, mid);
        build_tree(2 * node + 1, mid + 1, right);

        segment_tree[node].nr_elems = segment_tree[2 * node].nr_elems + segment_tree[2 * node + 1].nr_elems;
        segment_tree[node].pos_min = elements[segment_tree[2 * node].pos_min] <= elements[segment_tree[2 * node + 1].pos_min]? segment_tree[2 * node].pos_min : segment_tree[2 * node + 1].pos_min;
    }
}

inline void update_nr_elems(int node, int left, int right, int pos, int val)
{
    if (left == right)
        segment_tree[node].nr_elems = val;
    else
    {
        int mid = (left + right) / 2;
        if (pos <= mid)
            update_nr_elems(2 * node, left, mid, pos, val);
        if (pos > mid)
            update_nr_elems(2 * node + 1, mid + 1, right, pos, val);

        segment_tree[node].nr_elems = segment_tree[2 * node].nr_elems + segment_tree[2 * node + 1].nr_elems;
    }
}

inline void update_min(int node, int left, int right, int pos, int val)
{
    if (left == right)
        segment_tree[node].pos_min = val;
    else
    {
        int mid = (left + right) / 2;
        if (pos <= mid)
            update_min(2 * node, left, mid, pos, val);
        if (pos > mid)
            update_min(2 * node + 1, mid + 1, right, pos, val);

        segment_tree[node].pos_min = elements[segment_tree[2 * node].pos_min] <= elements[segment_tree[2 * node + 1].pos_min]? segment_tree[2 * node].pos_min : segment_tree[2 * node + 1].pos_min;
    }
}

inline int query_nr_elems(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return segment_tree[node].nr_elems;

    int mid = (left + right) / 2, sum = 0;
    if (x <= mid)
        sum += query_nr_elems(2 * node, left, mid, x, y);
    if (y > mid)
        sum += query_nr_elems(2 * node + 1, mid + 1, right, x, y);

    return sum;
}

inline int query_right_limit(int node, int left, int right, long long nr)
{
    if (left == right)
        return left;

    int mid = (left + right) / 2;

    if (segment_tree[2 * node].nr_elems >= nr)
        return query_right_limit(2 * node, left, mid, nr);
    return query_right_limit(2 * node + 1, mid + 1, right, nr - segment_tree[2 * node].nr_elems);
}

inline int query_min(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return segment_tree[node].pos_min;

    int mid = (left + right) / 2, res = 0;
    if (x <= mid)
    {
        int res1 = query_min(2 * node, left, mid, x, y);
        res = elements[res] <= elements[res1]? res : res1;
    }
    if (y > mid)
    {
        int res1 = query_min(2 * node + 1, mid + 1, right, x, y);
        res = elements[res] <= elements[res1]? res : res1;
    }
    return res;
}


int main()
{
    long long T, N;
    long long K;
    fin >> T;

    elements[0] = MAX;
    while (T--)
    {
        fin >> N >> K;

        for (int i = 1 ; i <= N ; ++i)
            fin >> elements[i];

        // K is large enough to sort
        if (K == N * (N - 1) / 2)
        {
            sort(elements + 1, elements + N + 1);

            for (int i = 1 ; i <= N ; ++i)
                fout << elements[i] << " ";
            fout << '\n';
        }
        else
        {
            // Build the segment tree
            build_tree(1, 1, N);

            for (int i = 1 ; i <= N ; ++i)
            {
                // Find the right limit of the interval we'll search
                int right_limit = query_right_limit(1, 1, N, K + 1);

                // Find the minimum from [1, right_limit]
                int min_pos = query_min(1, 1, N, 1, right_limit);

                fout << elements[min_pos] << " ";

                // Update K and the segment tree
                K -= query_nr_elems(1, 1, N, 1, min_pos) - 1;
                update_nr_elems(1, 1, N, min_pos, 0);
                update_min(1, 1, N, min_pos, 0);
            }
            fout << '\n';
        }
    }
    return 0;
}
