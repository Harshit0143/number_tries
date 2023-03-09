#include "bits/stdc++.h"
#include <unordered_map>
// #include "crush.cpp"
using namespace std;
#define ll int
#define pb push_back
#define pob pop_back()
#define mp make_pair
#define fo(i, a, b) for (ll i = a; i < b; i++)
#define all(v) (v).begin(), (v).end()
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define mod 100000000
#define mod2 992942057

struct node
{
    node **arr = new node *[2]{};
    bool is = false;
    ~node() { delete[] arr; }
};
class numTrie
{
public:
    node *root;
    int size = 0;
    int LOG;
    numTrie(int x = 32)
    {
        root = new node();
        LOG = x;
    }
    ~numTrie()
    {

        queue<node *> q;
        q.push(root);
        while (!q.empty())
        {
            node *curr = q.front();
            q.pop();
            for (int i = 0; i < 2; i++)
                if (curr->arr[i])
                    q.push(curr->arr[i]);

            delete curr;
        }
    }
    void insert(int num)
    {

        node *curr = root;
        for (int i = LOG - 1; i >= 0; i--)
        {
            int bit = ((num >> i) & 1);

            if (!curr->arr[bit])
                curr->arr[bit] = new node();
            curr = curr->arr[bit];
        }
        if (!curr->is)
            size++;

        curr->is = true;
    }

    bool search(int num)
    {

        node *curr = root;
        for (int i = LOG - 1; i >= 0; i--)
        {
            int bit = ((num >> i) & 1);

            if (!curr->arr[bit])
                return false;
            curr = curr->arr[bit];
        }
        return curr->is;
    }
    int max_xor(int a, numTrie *tree)
    {
    int ans = 0;
    node *curr = tree->root;
    for (int i = LOG-1; i >= 0; i--)
    {
        int bit = (a >> i) & 1;

        if (curr->arr[1 ^ bit])
        {
            ans += (1 << i);
            curr = curr->arr[1 ^ bit];
        }
        else
            curr = curr->arr[bit];
    }
    return ans;
}

};

int main()
{
    int n, x;
    cin >> n;
    numTrie *tree = new numTrie();
    for (int i = 0; i < n; i++)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            cin >> x;
            tree->insert(x);
            cout << "inserted " << x << "\n";
        }
        else if (q == 2)
        {
            cin >> x;
            if (!tree->search(x))
                cout << "not ";
            cout << "found " << x << "\n";
        }
        else
        {
            cout << "size of set: " << tree->size << "\n";
        }
    }

    return 0;
}
