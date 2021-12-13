//
// Created by Jonny Keane on 12/13/21.
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

const string FOLD = "fold along ";

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day13.txt");
    string line;
    vector<pair<char, int>> folds;
    vector<pair<int, int>> dots;
    while (getline(cin, line)) {
        if (line.find(',') != string::npos) {
            int x = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
            int y = stoi(line);
            dots.emplace_back(make_pair(x, y));
        } else if (line.find(FOLD) != string::npos) {
            line.erase(0, FOLD.size());
            char var = line[0];
            line.erase(0, 2);
            int num = stoi(line);
            folds.emplace_back(make_pair(var, num));
        }
    }
    for (int i = 0; i < 1; ++i) {
        auto fold = folds[i];
        if (fold.first == 'y') {
            for (auto & dot: dots) {
                if (dot.second > fold.second) {
                    dot.second -= 2 * (dot.second - fold.second);
                }
            }
        } else if (fold.first == 'x') {
            for (auto & dot: dots) {
                if (dot.first > fold.second) {
                    dot.first -= 2 * (dot.first - fold.second);
                }
            }
        }
    }
    set<pair<int, int>> rem;
    for (auto dot: dots) {
        rem.insert(dot);
    }
    cout << "Solution for Part 1: " << rem.size() << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day13.txt");
    string line;
    vector<pair<char, int>> folds;
    vector<pair<int, int>> dots;
    while (getline(cin, line)) {
        if (line.find(',') != string::npos) {
            int x = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
            int y = stoi(line);
            dots.emplace_back(make_pair(x, y));
        } else if (line.find(FOLD) != string::npos) {
            line.erase(0, FOLD.size());
            char var = line[0];
            line.erase(0, 2);
            int num = stoi(line);
            folds.emplace_back(make_pair(var, num));
        }
    }
    int max_x = INT_MAX;
    int max_y = INT_MAX;
    for (int i = 0; i < folds.size(); ++i) {
        auto fold = folds[i];
        if (fold.first == 'y') {
            for (auto & dot: dots) {
                if (dot.second > fold.second) {
                    dot.second -= 2 * (dot.second - fold.second);
                }
            }
            max_y = fold.second;
        } else if (fold.first == 'x') {
            for (auto & dot: dots) {
                if (dot.first > fold.second) {
                    dot.first -= 2 * (dot.first - fold.second);
                }
            }
            max_x = fold.second;
        }
    }
    set<pair<int, int>> rem;
    for (auto dot: dots) {
        rem.insert(dot);
    }
    cout << "Solution for Part 2: " << endl;
    for (int y = 0; y < max_y; ++y) {
        for (int x = 0; x < max_x; ++x) {
            if (rem.find(make_pair(x, y)) != rem.end()) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}