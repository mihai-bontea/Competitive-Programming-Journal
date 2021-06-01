#include <iostream>
#define NMax 5000001

using namespace std;

int segment_tree[NMax * 4], n, m;
string str;

inline void build_tree(int node, int left, int right)
{
    if (left == right)
        segment_tree[node] = (1 << (str[left - 1] - 'a'));
    else
    {
        int mid = (left + right) / 2;
        build_tree(2 * node, left, mid);
        build_tree(2 * node + 1, mid + 1, right);
        segment_tree[node] = (segment_tree[2 * node] | segment_tree[2 * node + 1]);
    }
}

inline int query_tree(int node, int left, int right, int x, int y)
{
    if (x <= left && right <= y)
        return segment_tree[node];
    else
    {
        int mid = (left + right) / 2;
        int res1 = 0, res2 = 0;

        if (x <= mid)
            res1 = query_tree(2 * node, left, mid, x, y);
        if (y > mid)
            res2 = query_tree(2 * node + 1, mid + 1, right, x, y);

        return res1 | res2;
    }
}

inline void update_tree(int node, int left, int right, int x, char c)
{
    if (left == right && left == x)
        segment_tree[node] = (1 << (c - 'a'));
    else
    {
        int mid = (left + right) / 2;
        if (x <= mid)
            update_tree(2 * node, left, mid, x, c);
        else
            update_tree(2 * node + 1, mid + 1, right, x, c);

        segment_tree[node] = (segment_tree[2 * node] | segment_tree[2 * node + 1]);
    }
}

int main()
{
    // Makes cin faster
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n;
    cin.ignore();
    getline(cin, str);
    build_tree(1, 1, n);

    cin >> m;

    bool op;
    int x, y;
    char c;

    for (int i = 1; i <= m; ++i)
    {
        cin >> op >> x;
        // Update
        if (op)
        {
            cin >> c;
            update_tree(1, 1, n, x, c);
        }
        // Query
        else
        {
            cin >> y;
            int res = query_tree(1, 1, n, x, y);
            int cnt = 0;

            // Counting the positive bits
            while (res)
            {
                cnt += (res % 2);
                res >>= 1;
            }
            cout << cnt << '\n';
        }
    }
    return 0;
}
