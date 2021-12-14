//
// Created by Jonny Keane on 12/14/21.
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

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day14.txt");
    string pattern;
    cin >> pattern;
    string line;
    map<string, char> pair_insertions;
    while (getline(cin, line)) {
        if (!line.empty()) {
            string a = line.substr(0, line.find(' '));
            char b = line[line.size() - 1];
            pair_insertions[a] = b;
        }
    }
    for (int i = 0; i < 10; ++i) {
        string n_patten;
        n_patten += pattern[0];
        for (int j = 0; j < pattern.size() - 1; ++j) {
            if (pair_insertions.find(pattern.substr(j, 2)) != pair_insertions.end()) {
                n_patten += pair_insertions[pattern.substr(j, 2)];
                n_patten += pattern[j + 1];
            } else {
                n_patten += pattern[j + 1];
            }
        }
        pattern = n_patten;
    }
    map<char, int> counts;
    for (char c: pattern) {
        if (counts.find(c) == counts.end()) {
            counts[c] = 0;
        }
        ++counts[c];
    }
    int min_ = INT_MAX;
    int max_ = 0;
    for (auto p: counts) {
        min_ = min(min_, p.second);
        max_ = max(max_, p.second);
    }
    cout << "Solution for Part 1: " << max_ - min_ << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day14.txt");
    string pattern;
    cin >> pattern;
    string line;
    map<string, char> pair_insertions;
    while (getline(cin, line)) {
        if (!line.empty()) {
            string a = line.substr(0, line.find(' '));
            char b = line[line.size() - 1];
            pair_insertions[a] = b;
        }
    }
    map<string, long> pair_counts;
    for (int i = 0; i < pattern.size() - 1; ++i) {
        if (pair_counts.find(pattern.substr(i, 2)) == pair_counts.end()) {
            pair_counts[pattern.substr(i, 2)] = 0;
        }
        ++pair_counts[pattern.substr(i, 2)];
    }
    for (int i = 0; i < 40; ++i) {
        map<string, long> n_pair_counts(pair_counts);
        for (const auto& p: pair_counts) {
            if (pair_insertions.find(p.first) != pair_insertions.end()) {
                string a = p.first.substr(0, 1) + pair_insertions[p.first];
                string b = pair_insertions[p.first] + p.first.substr(1, 1);
                if (n_pair_counts.find(a) == n_pair_counts.end()) {
                    n_pair_counts[a] = 0;
                }
                if (n_pair_counts.find(b) == n_pair_counts.end()) {
                    n_pair_counts[b] = 0;
                }
                n_pair_counts[a] += p.second;
                n_pair_counts[b] += p.second;
                n_pair_counts[p.first] -= p.second;
            }
        }
        pair_counts = n_pair_counts;
    }
    map<char, long> counts;
    for (const auto& p: pair_counts) {
        if (counts.find(p.first[0]) == counts.end()) {
            counts[p.first[0]] = 0;
        }
        if (counts.find(p.first[1]) == counts.end()) {
            counts[p.first[1]] = 0;
        }
        counts[p.first[0]] += p.second;
        counts[p.first[1]] += p.second;
    }
    for (auto & p: counts) {
        p.second /= 2;
    }
    ++counts[pattern[0]];
    ++counts[pattern[pattern.size() - 1]];
    long min_ = LONG_MAX;
    long max_ = 0;
    for (auto p: counts) {
        min_ = min(min_, p.second);
        max_ = max(max_, p.second);
    }
    cout << "Solution for Part 2: " << max_ - min_ << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}