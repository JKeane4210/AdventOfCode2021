//
// Created by Jonny Keane on 12/10/21.
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

const set<char> OPEN = {'[', '<', '{', '('};
const set<char> CLOSE = {']', '>', '}', ')'};
const map<char, char> MAPPINGS = {{']', '['}, {'>', '<'}, {'}', '{'}, {')', '('}};
const map<char, int> SCORES = {{']', 57}, {'>', 25137}, {'}', 1197}, {')', 3}};
const map<char, int> AUTO_SCORES = {{'[',2}, {'<', 4}, {'{', 3}, {'(', 1}};

int score(string line) {
    stack<char> stack;
    for (char c: line) {
        if (OPEN.find(c) != OPEN.end()) {
            stack.push(c);
        } else if (CLOSE.find(c) != CLOSE.end()) {
            if (stack.top() == MAPPINGS.at(c)) {
                stack.pop();
            } else {
                return SCORES.at(c);

            }
        }
    }
    return 0;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day10.txt");
    string line;
    int total = 0;
    while (getline(cin, line)) {
        total += score(line);
    }
    cout << "Solution for Part 1: " << total << endl;
}

long autocomplete_score(string line) {
    stack<char> stack;
    for (char c: line) {
        if (OPEN.find(c) != OPEN.end()) {
            stack.push(c);
        } else if (CLOSE.find(c) != CLOSE.end()) {
            if (stack.top() == MAPPINGS.at(c)) {
                stack.pop();
            } else {
                throw exception();
            }
        }
    }
    long score = 0;
    while (!stack.empty()) {
        score *= 5;
        score += AUTO_SCORES.at(stack.top());
        stack.pop();
    }
    return score;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day10.txt");
    string line;
    vector<long> scores;
    while (getline(cin, line)) {
        if (score(line) == 0) {
            scores.emplace_back(autocomplete_score(line));
        }
    }
    sort(scores.begin(), scores.end());
    int middle = scores.size() / 2;
    cout << "Solution for Part 2: " << scores[middle] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}