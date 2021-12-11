//
// Created by Jonny Keane on 12/11/21.
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

const int DELTAS[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};

const int GRID_DIM = 10;

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day11.txt");

    int grid[GRID_DIM][GRID_DIM];
    for (int i = 0; i < GRID_DIM; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < GRID_DIM; ++j) {
            grid[i][j] = line[j] - 0x30;
        }
    }
    long flashes = 0;
    for (int step = 0; step < 100; ++step) {
        for (int i = 0; i < GRID_DIM; ++i) {
            for (int j = 0; j < GRID_DIM; ++j) {
                ++grid[i][j];
            }
        }
        set<pair<int, int>> has_flashed;
        queue<pair<int, int>> will_flash;
        for (int i = 0; i < GRID_DIM; ++i) {
            for (int j = 0; j < GRID_DIM; ++j) {
                if (grid[i][j] > 9) {
                    will_flash.push(make_pair(i, j));
                }
                while (!will_flash.empty()) {
                    auto top = will_flash.front();
                    will_flash.pop();
                    if (has_flashed.find(top) != has_flashed.end()) continue;
                    has_flashed.insert(top);
                    for (int k = 0; k < 8; ++k) {
                        int nr = top.first + DELTAS[k][0];
                        int nc = top.second + DELTAS[k][1];
                        if (nr >= 0 && nr < GRID_DIM && nc >= 0 && nc < GRID_DIM) {
                            ++grid[nr][nc];
                            if (grid[nr][nc] > 9) {
                                will_flash.push(make_pair(nr,nc));
                            }
                        }
                    }
                }
            }
        }
        for (auto p: has_flashed) {
            grid[p.first][p.second] = 0;
            ++flashes;
        }
    }
    cout << "Solution for Part 1: " << flashes << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day11.txt");

    int grid[GRID_DIM][GRID_DIM];
    for (int i = 0; i < GRID_DIM; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < GRID_DIM; ++j) {
            grid[i][j] = line[j] - 0x30;
        }
    }
    int step = 0;
    while (true) {
        ++step;
        for (int i = 0; i < GRID_DIM; ++i) {
            for (int j = 0; j < GRID_DIM; ++j) {
                ++grid[i][j];
            }
        }
        set<pair<int, int>> has_flashed;
        queue<pair<int, int>> will_flash;
        for (int i = 0; i < GRID_DIM; ++i) {
            for (int j = 0; j < GRID_DIM; ++j) {
                if (grid[i][j] > 9) {
                    will_flash.push(make_pair(i, j));
                }
                while (!will_flash.empty()) {
                    auto top = will_flash.front();
                    will_flash.pop();
                    if (has_flashed.find(top) != has_flashed.end()) continue;
                    has_flashed.insert(top);
                    for (int k = 0; k < 8; ++k) {
                        int nr = top.first + DELTAS[k][0];
                        int nc = top.second + DELTAS[k][1];
                        if (nr >= 0 && nr < GRID_DIM && nc >= 0 && nc < GRID_DIM) {
                            ++grid[nr][nc];
                            if (grid[nr][nc] > 9) {
                                will_flash.push(make_pair(nr,nc));
                            }
                        }
                    }
                }
            }
        }
        if (has_flashed.size() == 100) {
            break;
        }
        for (auto p: has_flashed) {
            grid[p.first][p.second] = 0;
        }
    }
    cout << "Solution for Part 2: " << step << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}