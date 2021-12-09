//
// Created by Jonny Keane on 12/6/21.
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

void transform(vector<int> & fish) {
    long new_fish = 0;
    for (int & f: fish) {
        if (f > 0) { --f; }
        else {
            f = 6;
            ++new_fish;
        }
    }
    for (long i = 0; i < new_fish; ++i) { fish.emplace_back(8); }
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day6.txt");
    string line;
    cin >> line;
    vector<int> fish;
    size_t pos;
    while ((pos = line.find(",")) != string::npos) {
        fish.emplace_back(stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    }
    fish.emplace_back(stoi(line));
    for (int i = 0; i < 80; ++i) {
        transform(fish);
    }
    cout << "Solution for Part 1: " << fish.size() << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day6.txt");
    string line;
    cin >> line;
    long fish_counts[9];
    for (long & fish_count : fish_counts) {
        fish_count = 0;
    }
    size_t pos;
    while ((pos = line.find(",")) != string::npos) {
        int stage = stoi(line.substr(0, pos));
        ++fish_counts[stage];
        line.erase(0, pos + 1);
    }
    int stage = stoi(line);
    ++fish_counts[stage];
    for (int i = 0; i < 256; ++i) {
        long new_fish_counts[9];
        for (long & new_fish_count : new_fish_counts) { new_fish_count = 0; }
        long ready_fish = fish_counts[0];
        for (int j = 1; j <= 8; ++j) {
            new_fish_counts[j - 1] = fish_counts[j];
        }
        new_fish_counts[6] += ready_fish;
        new_fish_counts[8] += ready_fish;
        for (int j = 0; j < 9; ++j) {
            fish_counts[j] = new_fish_counts[j];
        }
    }
    long res = 0;
    for (long fish_count : fish_counts) {
        res += fish_count;
    }
    cout << "Solution for Part 2: " << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}