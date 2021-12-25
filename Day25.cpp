//
// Created by Jonny Keane on 12/24/21.
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

pair<int, vector<string>> apply_step(vector<string> grid) {
    vector<string> new_grid(grid);
    int moved = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '>') {
                if (grid[i][(j + 1) % grid[0].size()] == '.') {
                    new_grid[i][(j + 1) % grid[0].size()] = '>';
                    new_grid[i][j] = '.';
                    ++moved;
                }
            }
        }
    }
    grid = new_grid;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'v') {
                if (grid[(i + 1) % grid.size()][j] == '.') {
                    new_grid[(i + 1) % grid.size()][j] = 'v';
                    new_grid[i][j] = '.';
                    ++moved;
                }
            }
        }
    }
    return make_pair(moved, new_grid);
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day25.txt");
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.emplace_back(line);
    }
    int step = 1;
    while (true) {
        auto step_res = apply_step(grid);
        if (step_res.first == 0) {
            break;
        }
        grid = step_res.second;
        ++step;
    }
    cout << "Solution for Part 1: " << step << endl;
}

void part_2() {
    cout << "Sleigh has been rebooted. 50* achieved. Christmas has been saved!!!" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}
