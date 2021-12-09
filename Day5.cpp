//
// Created by Jonny Keane on 12/4/21.
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

const string ARROW = " -> ";

int part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day5.txt");
    string line;

    vector<pair<pair<int, int>, pair<int, int>>> vents;
    int X_MAX = 0;
    int Y_MAX = 0;

    while (getline(cin, line)) {
        size_t pos = line.find(",");
        int x1 = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(ARROW);
        int y1 = stoi(line.substr(0, pos));
        line.erase(0, pos + ARROW.size());
        pos = line.find(",");
        int x2 = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        int y2 = stoi(line);
        X_MAX = max(x1, X_MAX);
        X_MAX = max(x2, X_MAX);
        Y_MAX = max(y1, Y_MAX);
        Y_MAX = max(y2, Y_MAX);
        if (x1 == x2 || y1 == y2) {
            vents.emplace_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
        }
    }
    int grid[Y_MAX + 1][X_MAX + 1];
    for (int i = 0; i < Y_MAX + 1; ++i) {
        for (int j = 0; j < X_MAX + 1; ++j) {
            grid[i][j] = 0;
        }
    }
    for (auto vent: vents) {
        if (vent.first.first == vent.second.first) {
            int x = vent.first.first;
            int y1 = min(vent.first.second, vent.second.second);
            int y2 = max(vent.first.second, vent.second.second);
            for (int i = y1; i <= y2; ++i) {
                ++grid[i][x];
            }
        } else {
            int y = vent.first.second;
            int x1 = min(vent.first.first, vent.second.first);
            int x2 = max(vent.first.first, vent.second.first);
            for (int i = x1; i <= x2; ++i) {
                ++grid[y][i];
            }
        }
    }
    int hotspots = 0;
    for (int i = 0; i < Y_MAX + 1; ++i) {
        for (int j = 0; j < X_MAX + 1; ++j) {
            if (grid[i][j] >= 2) {
                ++hotspots;
            }
        }
    }
    cout << "Solution for Part 1: " << hotspots << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day5.txt");
    string line;

    vector<pair<pair<int, int>, pair<int, int>>> vents;
    int X_MAX = 0;
    int Y_MAX = 0;

    while (getline(cin, line)) {
        size_t pos = line.find(",");
        int x1 = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(ARROW);
        int y1 = stoi(line.substr(0, pos));
        line.erase(0, pos + ARROW.size());
        pos = line.find(",");
        int x2 = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        int y2 = stoi(line);
        X_MAX = max(x1, X_MAX);
        X_MAX = max(x2, X_MAX);
        Y_MAX = max(y1, Y_MAX);
        Y_MAX = max(y2, Y_MAX);
//        if (x1 == x2 || y1 == y2) {
            vents.emplace_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
//        }
    }
    int grid[Y_MAX + 1][X_MAX + 1];
    for (int i = 0; i < Y_MAX + 1; ++i) {
        for (int j = 0; j < X_MAX + 1; ++j) {
            grid[i][j] = 0;
        }
    }
    for (auto vent: vents) {
        if (vent.first.first == vent.second.first) {
            int x = vent.first.first;
            int y1 = min(vent.first.second, vent.second.second);
            int y2 = max(vent.first.second, vent.second.second);
            for (int i = y1; i <= y2; ++i) {
                ++grid[i][x];
            }
        } else if (vent.first.second == vent.second.second) {
            int y = vent.first.second;
            int x1 = min(vent.first.first, vent.second.first);
            int x2 = max(vent.first.first, vent.second.first);
            for (int i = x1; i <= x2; ++i) {
                ++grid[y][i];
            }
        } else { // angle
            int x1 = vent.first.first;
            int y1 = vent.first.second;
            int x2 = vent.second.first;
            int y2 = vent.second.second;
            int dx = x2 > x1 ? 1: -1;
            int dy = y2 > y1 ? 1: -1;
            for (int i = 0; i <= abs(x2 - x1); ++i) {
                int cx = x1 + i * dx;
                int cy = y1 + i * dy;
                ++grid[cy][cx];
            }
        }
    }
    int hotspots = 0;
    for (int i = 0; i < Y_MAX + 1; ++i) {
        for (int j = 0; j < X_MAX + 1; ++j) {
            if (grid[i][j] >= 2) {
                ++hotspots;
            }
        }
    }
    cout << "Solution for Part 2: " << hotspots << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}