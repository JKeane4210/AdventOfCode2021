//
// Created by Jonny Keane on 12/9/21.
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

const int DELTAS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day9.txt");
    vector<vector<int>> grid;
    string line;
    while (getline(cin, line)) {
        vector<int> row;
        for (char c: line) {
            row.emplace_back((int)c - 0x30);
        }
        grid.emplace_back(row);
    }
    int risk = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            bool passes = true;
            for (int k = 0; k < 4; ++k) {
                int nr = i + DELTAS[k][0];
                int nc = j + DELTAS[k][1];
                if (nr >= 0 && nr < grid.size() &&
                      nc >= 0 && nc < grid[0].size() &&
                      grid[i][j] >= grid[nr][nc]) {
                    passes = false;
                    break;
                }
            }
            if (passes) {
                risk += grid[i][j] + 1;
            }
        }
    }
    cout << "Solution for Part 1: " << risk << endl;
}

// approach was based off component painting using DFS
void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day9.txt");
    vector<vector<int>> grid;
    string line;
    while (getline(cin, line)) {
        vector<int> row;
        for (char c: line) {
            row.emplace_back((int)c - 0x30);
        }
        grid.emplace_back(row);
    }
    int visited[grid.size()][grid[0].size()];
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) { visited[i][j] = (grid[i][j] == 9 ? -2 : -1); };
    }
    queue<pair<int, int>> q;
    int component = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (visited[i][j] == -1) {
                q.push(make_pair(i, j));
                while (!q.empty()) {
                    auto top = q.front();
                    visited[top.first][top.second] = component;
                    q.pop();
                    for (int k = 0; k < 4; ++k) {
                        int nr = top.first + DELTAS[k][0];
                        int nc = top.second + DELTAS[k][1];
                        if (nr >= 0 && nr < grid.size() &&
                            nc >= 0 && nc < grid[0].size() &&
                            visited[nr][nc] == -1) {
                            q.push(make_pair(nr, nc));
                        }
                    }
                }
                ++component;
            }
        }
    }
    int sizes[component];
    for (int i = 0; i < component; ++i) { sizes[i] = 0; }
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (visited[i][j] != -2) {
                ++sizes[visited[i][j]];
            }
        }
    }
    sort(sizes, sizes + component);
    int res = 1;
    for (int i = 0; i < 3; ++i) {
        res *= sizes[component - 1 - i];
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