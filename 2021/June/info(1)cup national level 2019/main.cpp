#include <iostream>
#define NMax 200001
#include <cassert>
#include <limits>

using namespace std;

int N, M;
const long long MAX = numeric_limits<long long int>::max();
const long long MIN = numeric_limits<long long int>::min();

struct
{
    long long min_even;   // In query
    long long max_even;

    long long max_odd;    // In query
    long long min_odd;
    long long lazy;
}segment_tree[NMax * 4];

inline void build_tree(int node, int left, int right)
{
    if (left == right)
    {
        long long aux;
        cin >> aux;
        segment_tree[node].min_even = (aux % 2 == 0)? aux : MAX;
        segment_tree[node].max_even = (aux % 2 == 0)? aux : MIN;

        segment_tree[node].max_odd = (aux % 2 != 0)? aux : MIN;
        segment_tree[node].min_odd = (aux % 2 != 0)? aux : MAX;
    }
    else
    {
        int mid = (left + right) / 2;
        build_tree(2 * node, left, mid);
        build_tree(2 * node + 1, mid + 1, right);

        segment_tree[node].min_even = min(segment_tree[2 * node].min_even, segment_tree[2 * node + 1].min_even);
        segment_tree[node].max_even = max(segment_tree[2 * node].max_even, segment_tree[2 * node + 1].max_even);

        segment_tree[node].max_odd = max(segment_tree[2 * node].max_odd, segment_tree[2 * node + 1].max_odd);
        segment_tree[node].min_odd = min(segment_tree[2 * node].min_odd, segment_tree[2 * node + 1].min_odd);
    }
}

inline void update_helper(int node, long long val)
{
    // 1) Mark as lazy
    segment_tree[node].lazy += val;

    // 2) Add val
    // There are odd numbers in the interval
    if (segment_tree[node].max_odd != MIN)
    {
        segment_tree[node].max_odd += val;
        segment_tree[node].min_odd += val;
    }
    // There are even numbers in the interval
    if (segment_tree[node].min_even != MAX)
    {
        segment_tree[node].min_even += val;
        segment_tree[node].max_even += val;
    }

    // 3) Swap parity if val is odd
    if (val % 2 != 0)
    {
        swap(segment_tree[node].min_even, segment_tree[node].min_odd);
        swap(segment_tree[node].max_even, segment_tree[node].max_odd);
    }
}

inline void update_tree(int node, int left, int right, int x, int y, long long val)
{
    if (x <= left && right <= y)
        update_helper(node, val);
    else
    {
        int mid = (left + right) / 2;

        // If node is lazy
        if (segment_tree[node].lazy != 0)
        {
            // Set children to lazy and update them
            update_helper(2 * node, segment_tree[node].lazy);
            update_helper(2 * node + 1, segment_tree[node].lazy);

            // Set node as no longer lazy
            segment_tree[node].lazy = 0;
        }

        if (x <= mid)
            update_tree(2 * node, left, mid, x, y, val);
        if (y > mid)
            update_tree(2 * node + 1, mid + 1, right, x, y, val);

        segment_tree[node].min_even = min(segment_tree[2 * node].min_even, segment_tree[2 * node + 1].min_even);
        segment_tree[node].max_even = max(segment_tree[2 * node].max_even, segment_tree[2 * node + 1].max_even);

        segment_tree[node].max_odd = max(segment_tree[2 * node].max_odd, segment_tree[2 * node + 1].max_odd);
        segment_tree[node].min_odd = min(segment_tree[2 * node].min_odd, segment_tree[2 * node + 1].min_odd);
    }
}

inline pair<long long, long long> query_tree(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return make_pair(segment_tree[node].min_even, segment_tree[node].max_odd);

    int mid = (left + right) / 2;
    pair<long long, long long> res1 = make_pair(MAX, MIN);
    pair<long long, long long> res2 = make_pair(MAX, MIN);

    // If node is lazy
    if (segment_tree[node].lazy != 0)
    {
        // Set children to lazy and update them
        update_helper(2 * node, segment_tree[node].lazy);
        update_helper(2 * node + 1, segment_tree[node].lazy);

        // Set node as no longer lazy
        segment_tree[node].lazy = 0;
    }


    if (x <= mid)
        res1 = query_tree(2 * node, left, mid, x, y);
    if (y > mid)
        res2 = query_tree(2 * node + 1, mid + 1, right, x, y);

    pair<long long, long long> final_res = make_pair(min(res1.first, res2.first), max(res1.second, res2.second));
    return final_res;
}

int main()
{
    // Makes cin faster
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
    build_tree(1, 1, N);

    int M, op, left, right, val;
    cin >> M;
    while (M--)
    {
        cin >> op >> left >> right;
        // Update
        if (!op)
        {
            cin >> val;
            update_tree(1, 1, N, left, right, val);
        }
        // Query
        else
        {
            pair<long long, long long> res = query_tree(1, 1, N, left, right);
            cout << ((res.first != MAX)? res.first : -1) << ' ';
            cout << ((res.second != MIN)? res.second : -1) << '\n';
        }
    }
    return 0;
}
