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

int light_dark_val(string s) {
    int res = 0;
    for (char c: s) {
        if (c == '#') {
            res |= 1;
        }
        res <<= 1;
    }
    res >>= 1;
    return res;
}

// need the default because of the algorithm that was given to me
// (every other switch would turn on infinity and then turn off infinity)
vector<string> enhance(vector<string> grid, string alg, char def) {
    vector<string> res_grid;
    for (int i = 0; i < grid.size() + 4; ++i) {
        res_grid.emplace_back(string(grid[0].size() + 4, def));
    }
    for (int i = 0; i < res_grid.size(); ++i) {
        for (int j = 0; j < res_grid[0].size(); ++j) {
            string light_dark;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = i + dr - 2;
                    int nc = j + dc - 2;
                    if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size()) {
                        light_dark += grid[nr][nc];
                    } else {
                        light_dark += def;
                    }
                }
            }
            res_grid[i][j] = alg[light_dark_val(light_dark)];
        }
    }
    return res_grid;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day20.txt");
    string alg;
    getline(cin, alg);
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        grid.emplace_back(line);
    }
    for (int i = 0; i < 2; ++i) {
        grid = enhance(grid, alg, i % 2 == 0 ? '.' : '#');
    }

    int lit_count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '#') {
                ++lit_count;
            }
        }
    }
    cout << "Solution for Part 1: " << lit_count << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day20.txt");
    string alg;
    getline(cin, alg);
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        grid.emplace_back(line);
    }
    for (int i = 0; i < 50; ++i) {
        grid = enhance(grid, alg, i % 2 == 0 ? '.' : '#');
    }

    int lit_count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '#') {
                ++lit_count;
            }
        }
    }
    cout << "Solution for Part 1: " << lit_count << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}