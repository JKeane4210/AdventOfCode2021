//
// Created by Jonny Keane on 12/7/21.
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

// made this part into a nice sweep problem althought excessive for input size :)
void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day7.txt");
    vector<int> crabs;
    int move_cost = 0;
    size_t pos;
    string line;
    cin >> line;
    while ((pos = line.find(",")) != string::npos) {
        int crab = stoi(line.substr(0, pos));
        crabs.emplace_back(crab);
        move_cost += crab;
        line.erase(0, pos + 1);
    }
    int crab = stoi(line);
    crabs.emplace_back(crab);
    move_cost += crab;
    sort(crabs.begin(), crabs.end());
    int curr = 0;
    int curr_ind = 0;
    int min_ = move_cost;
    while (curr_ind != crabs.size()) {
        ++curr;
        // shifting right by 1 means:
        // - all to the left get larger by 1
        // - all to the right get smaller by 1
        while (curr_ind != crabs.size() && crabs[curr_ind] < curr) {
            ++curr_ind;
        }
        move_cost += curr_ind;
        move_cost -= crabs.size() - curr_ind;
        min_ = min(move_cost, min_);
    }
    cout << "Solution for Part 1: " << min_ << endl;
}

int fuel_cost(int n) {
    return n * (n + 1) / 2;
}

// I went slightly more brute force but made a couple speed improvements with the
// map and equation for the fuel cost
void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day7.txt");
    map<int, int> crabs;
    size_t pos;
    string line;
    cin >> line;
    int max_ = 0;
    while ((pos = line.find(",")) != string::npos) {
        int crab = stoi(line.substr(0, pos));
        if (crabs.find(crab) == crabs.end()) {
            crabs[crab] = 0;
        }
        ++crabs[crab];
        max_ = max(crab, max_);
        line.erase(0, pos + 1);
    }
    int crab = stoi(line);
    if (crabs.find(crab) == crabs.end()) {
        crabs[crab] = 0;
    }
    ++crabs[crab];
    int min_ = INT_MAX;
    for (int curr = 0; curr <= max_; ++curr) {
        int total = 0;
        for (auto p: crabs) {
            total += fuel_cost(abs(curr - p.first)) * p.second;
        }
        min_ = min(min_, total);
    }
    cout << "Solution for Part 2: " << min_ << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}