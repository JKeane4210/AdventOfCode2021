//
// Created by Jonny Keane on 12/19/21.
//

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back

#define V vector
#define vi V<int>
#define vll V<ll>
#define vd V<double>
#define pii pair<int, int>
#define pll pair<ll,ll>
#define vpii V<pii>
#define vpll V<pll>
#define graph V<vi>

// loops
#define WHILE(n) while(n--)
#define FOR(a) for(ll i=0;i<a;i++)
#define FIND(a, e) find(a.begin(), a.end(), e)
#define minimum(a) *min_element(a.begin(), a.end())
#define maximum(a) *max_element(a.begin(), a.end())

#define nl '\n'

// use M_PI for PI (imported from cmath within stdc++.h)

using namespace std;

struct tree_node {
public:
    int value;
    tree_node *  left_node = nullptr;
    tree_node * right_node = nullptr;
    tree_node * parent = nullptr;
    tree_node(): value(-1) {}
    tree_node(int value): value(value) {}
};

tree_node * create_tree(string line, tree_node * parent) {
    auto * node = new tree_node();
    node->parent = parent;
    if (line[0] == '[' && line[line.size() - 1] == ']') {
        int sep_idx = 0;
        int count = 0;
        int idx = 1;
        for (char c: line.substr(1, line.size() - 2)) {
            if (c == '[') { ++count; }
            if (c == ']') { --count; }
            if (c == ',' && count == 0) {
                sep_idx = idx;
                break;
            }
            ++idx;
        }
        auto * left = create_tree(line.substr(1, sep_idx - 1), node);
        auto * right = create_tree(line.substr(sep_idx + 1, line.size() - 1 - (sep_idx + 1)), node);
        node->left_node = left;
        node->right_node = right;
    } else {
        node->value = stoi(line);
    }
    return node;
}

vector<pair<tree_node *, int>> preorder(tree_node * node, int depth, vector<pair<tree_node *, int>> v) {
    if (node->left_node != nullptr) {
        for (auto p: preorder(node->left_node, depth + 1, vector<pair<tree_node *, int>>())) {
            v.emplace_back(p);
        }
    }
    if (node->value != -1) {
        v.emplace_back(make_pair(node, depth));
    }
    if (node->right_node != nullptr) {
        for (auto p: preorder(node->right_node, depth + 1, vector<pair<tree_node *, int>>())) {
            v.emplace_back(p);
        }
    }
    return v;
}

bool explodes(tree_node * tree) {
    auto pre = preorder(tree, 0, vector<pair<tree_node *, int>>());
    for (int i = 0; i < pre.size() - 1; ++i) {
        if (pre[i].second == 5 && pre[i + 1].second == 5) {
            if (i > 0) {
                pre[i - 1].first->value += pre[i].first->value;
            }
            if (i + 1 < pre.size() - 1) {
                pre[i + 2].first->value += pre[i + 1].first->value;
            }
            auto * parent = pre[i].first->parent;
            parent->left_node = nullptr;
            parent->right_node = nullptr;
            parent->value = 0;
            return true;
        }
    }
    return false;
}

bool splits(tree_node * tree) {
    auto pre = preorder(tree, 0, vector<pair<tree_node *, int>>());
    for (auto & p : pre) {
        if (p.first->value > 9) {
            p.first->left_node = new tree_node(p.first->value / 2);
            p.first->left_node->parent = p.first;
            p.first->right_node = new tree_node(p.first->value - p.first->value / 2);
            p.first->right_node->parent = p.first;
            p.first->value = -1;
            return true;
        }
    }
    return false;
}

long long magnitude(tree_node * node) {
    long long a;
    if (node->left_node->value != -1) {
        a = 3 * node->left_node->value;
    } else {
        a = 3 * magnitude(node->left_node);
    }
    long long b;
    if (node->right_node->value != -1) {
        b = 2 * node->right_node->value;
    } else {
        b = 2 * magnitude(node->right_node);
    }
    return a + b;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day18.txt");
    string line;
    getline(cin, line);
    auto * root = create_tree(line, nullptr);
    while(getline(cin, line)) {
        auto * new_root = new tree_node();
        auto * sub_root = create_tree(line, nullptr);
        root->parent = new_root;
        sub_root->parent = new_root;
        new_root->left_node = root;
        new_root->right_node = sub_root;
        root = new_root;
        bool passes = false;
        while (!passes) {
            passes = true;
            if (explodes(root)) {
                passes = false;
                continue;
            }
            if (splits(root)) {
                passes = false;
            }
        }
    }
    cout << "Solution for Part 1: " << magnitude(root) << endl;
}

long long add_res(string l1, string l2) {
    tree_node * root = new tree_node();
    tree_node * left = create_tree(l1, nullptr);
    tree_node * right = create_tree(l2, nullptr);
    root->left_node = left;
    left->parent = root;
    root->right_node = right;
    right->parent = root;
    bool passes = false;
    while (!passes) {
        passes = true;
        if (explodes(root)) {
            passes = false;
            continue;
        }
        if (splits(root)) {
            passes = false;
        }
    }
    return magnitude(root);
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day18.txt");
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.emplace_back(line);
    }
    long long max_ = 0;
    for (const string & l1: lines) {
        for (const string & l2: lines) {
            if (l1 != l2) {
                max_ = max(max_, add_res(l1, l2));
            }
        }
    }
    cout << "Solution for Part 2: " << max_ << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}