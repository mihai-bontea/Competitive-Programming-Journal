#include <cstdio>
#include <algorithm>
#define NMax 100010
#define INF 2000000000000000LL
#define MAX 1000000000

using namespace std;

int n, q, t[NMax], d[NMax], leftt[NMax];

struct arbint
{
    int ap;
    long long dif, lazy;
    arbint *left, *right;

    arbint ()
    {
        ap = 0;
        dif = INF;
        lazy = 0LL;

        left = right = NULL;
    }
} *root;

inline void propag (arbint *node, int left, int right)
{
    node->dif += node->lazy;

    if (left != right)
    {
        if (node->left == NULL)
            node->left = new arbint;
        if (node->right == NULL)
            node->right = new arbint;

        node->left->lazy += node->lazy;
        node->right->lazy += node->lazy;
    }

    node->lazy = 0LL;
}

inline void update(int left, int right, int x, int y, int val, arbint *node)
{
    if (left != right)
    {
        if (node->left == NULL)
            node->left = new arbint;
        if (node->right == NULL)
            node->right = new arbint;
    }

    if (node->lazy != 0)
        propag (node, left, right);

    if (x <= left && right <= y)
    {
        node->lazy += 1LL * val;
        propag (node, left, right);
        return;
    }

    int mid = (left + right) >> 1;
    if (x <= mid)
        update (left, mid, x, y, val, node->left);

    else if (node->left->lazy != 0)
        propag (node->left, left, mid);

    if (y > mid)
        update (mid + 1, right, x, y, val, node->right);

    else if (node->right->lazy != 0)
        propag (node->right, mid + 1, right);

    node->dif = min(node->left->dif, node->right->dif);
}

inline bool query()
{
    if (root->left == NULL) root->left = new arbint;
    if (root->right == NULL) root->right = new arbint;

    propag (root, 1, MAX);

    return (root->dif > 0LL);
}

inline void change(int left, int right, int nr, arbint *node)
{
    if (left != right)
    {
        if (node->left == NULL)
            node->left = new arbint;
        if (node->right == NULL)
            node->right = new arbint;
    }

    if (node->lazy != 0)
        propag (node, left, right);

    if (nr <= left && right <= nr)
    {
        if (node->ap == 0) node->dif -= INF - nr;

        node->ap++;

        return;
    }

    int mid = (left + right) >> 1;
    if (nr <= mid)
    {
        change (left, mid, nr, node->left);
        if (node->right->lazy != 0)
            propag (node->right, mid + 1, right);
    }

    else if (nr > mid)
    {
        change (mid + 1, right, nr, node->right);
        if (node->left->lazy != 0)
            propag (node->left, left, mid);
    }
    node->dif = min (node->left->dif, node->right->dif);
}

int main ()
{
    scanf ("%d %d", &n, &q);

    for (int i = 1; i <= n; ++i)
        scanf("%d %d", &t[i], &d[i]);

    root = new arbint;

    int pos = 1;
    for (int i = 1; i <= n; ++i)
    {
        // Set the element at position d[i] with value d[i]
        change (1, MAX, d[i], root);
        // Subtract t[i] from [d[i], MAX]
        update (1, MAX, d[i], MAX, -t[i], root);

        while(!query())
        {
            update (1, MAX, d[pos], MAX, t[pos], root);
            ++pos;
        }

        leftt[i] = pos;
    }

    while (q--)
    {
        int st, dr;
        scanf ("%d %d", &st, &dr);
        // [st, dr] has a solution if leftt[dr] <= st
        printf("%d\n", (leftt[dr] <= st)? 1 : 0);
    }
    return 0;
}
