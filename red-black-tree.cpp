#include <iostream>
#include <algorithm>
#include <stack>

struct Node {
    char color;
    int key;
    Node* p;
    Node* left;
    Node* right;
    Node(char color, int key, Node* p, Node* left, Node* right) : color(color), key(key), p(p), left(left), right(right) {};
};

Node* fix(Node*& start) {
    Node* curr = start;
    while (curr->p) {
        Node* p = curr->p;
        if (curr->color == 'B' || p->color == 'B') {
            curr = p;
            continue;
        }
        Node* gp = p->p;
        if (!gp) {
            curr = p;
            continue;
        }
        Node* uncle;
        if (gp->left != p) {
            uncle = gp->left;
        } else {
            uncle = gp->right;
        }
        if (uncle && uncle->color == 'R') {
            p->color = 'B';
            uncle->color = 'B';
            gp->color = 'R';
            curr = gp;
            continue;
        }
        if (p == gp->left && curr == p->right) {
            p->right = curr->left;
            if (curr->left) {
                curr->left->p = p;
            }
            curr->left = p;
            p->p = curr;
            gp->left = curr;
            curr->p = gp;
            std::swap(curr, p);
        }
        if (p == gp->right && curr == p->left) {
            p->left = curr->right;
            if (curr->right) {
                curr->right->p = p;
            }
            curr->right = p;
            p->p = curr;
            gp->right = curr;
            std::swap(curr, p);
        }
        if (p == gp->left) {
            gp->left = p->right;
            if (p->right) {
                p->right->p = gp;
            }
            p->right = gp;
        } else {
            gp->right = p->left;
            if (p->left) {
                p->left->p = gp;
            }
            p->left = gp;
        }
        if (gp->p && gp == gp->p->left) {
            gp->p->left = p;
        } else if (gp->p) {
            gp->p->right = p;
        }
        p->p = gp->p;
        gp->p = p;
        gp->color = 'R';
        p->color = 'B';
        curr = p;
    }
    curr->color = 'B';
    return curr;
}

void insert(Node*& root, int x) {
    Node* curr = root;
    Node* last = nullptr;
    while (curr) {
        last = curr;
        if (x < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (last) {
        if (x < last->key) {
            last->left = new Node('R', x, last, nullptr, nullptr);
            root = fix(last->left);
        } else {
            last->right = new Node('R', x, last, nullptr, nullptr);
            root = fix(last->right);
        }
    } else {
        root = new Node('B', x, nullptr, nullptr, nullptr);
    }
}

bool find(Node* root, int x) {
    Node* curr = root;
    while (curr && curr->key != x) {
        if (x < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (!curr) {
        return false;
    }
    return true;
}

void print(Node* root) {
    std::stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        if (!curr) {
            continue;
        }
        std::cout << curr->key << ' ';
        if (curr->left) {
            std::cout << curr->left->key << ' ';
        } else {
            std::cout << "null" << ' ';
        }
        if (curr->right) {
            std::cout << curr->right->key << ' ';
        } else {
            std::cout << "null" << ' ';
        }
        std::cout << curr->color << std::endl;
        s.push(curr->left);
        s.push(curr->right);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Node* root = nullptr;
    int n;
    std::cin >> n;
    int cnt = 0;
    while (n--) {
        char type;
        int x;
        std::cin >> type >> x;
        if (type == '0') {
            if (!find(root, x)) {
                insert(root, x);
                ++cnt;
            }
        } else {
            if (find(root, x)) {
                std::cout << "Yes" << std::endl;
            } else {
                std::cout << "No" << std::endl;
            }
        }
    }
    std::cout << cnt << std::endl;
    print(root);
}
