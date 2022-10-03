#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <random>
#include <vector>

std::mt19937 mt(214214214);
using ll = long long;

struct Node {
    int val;
    int k;
    ll y;
    Node* left;
    Node* right;
    explicit Node (int x) {
        val = x;
        k = 1;
        y = mt();
        left = nullptr;
        right = nullptr;
    }
};

Node* copy (Node *curr) {
    return new Node(*curr);
}

void upd(Node* T) {
    if (!T) {
        return;
    }
    T->k = 1;
    if (T->left) {
        T->k += T->left->k;
    }
    if (T->right) {
        T->k += T->right->k;
    }
}

Node* merge(Node* L, Node* R) {
    if (!L) {
        return R;
    }
    if (!R) {
        return L;
    }
    L = copy(L);
    R = copy(R);
    if (L->y < R->y) {
        L->right = merge(L->right, R);
        upd(L);
        return L;
    } else {
        R->left = merge(L, R->left);
        upd(R);
        return R;
    }
}

void split(Node* T, Node*& L, Node*& R, int k) {
    if (!T) {
        L = nullptr;
        R = nullptr;
        return;
    }
    T = copy(T);
    int d = 1;
    if (T->left) {
        d += T->left->k;
    }
    if (k < d) {
        split(T->left, L, T->left, k);
        upd(T);
        R = T;
    } else {
        split(T->right, T->right, R, k - d);
        upd(T);
        L = T;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, c, t, m;
    std::cin >> n;
    std::vector<Node*> v = {};
    while (n--) {
        std::cin >> c >> t;
        --t;
        if (c == 1) {
            std::cin >> m;
            Node* x = new Node(m);
            if (t != -1) {
                v.push_back(merge(v[t], x));
            } else {
                v.push_back(x);
            }
        } else {
            Node* x = new Node(-1e9);
            Node* y = new Node(-1e9);
            split(v[t], x, y, 1);
            std::cout << x->val << '\n';
            v.push_back(y);
        }
    }
}
