//
// Created by Jonny Keane on 12/15/21.
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

class DijkstrasStep {
public:
    pair<int, int> nodeID;
    int totalDist;

    /// Initializes node ID and total distance
    /// \param nodeID Node ID
    /// \param totalDist Total distance
    DijkstrasStep(pair<int, int> nodeID, int totalDist) : nodeID(nodeID), totalDist(totalDist) {};

    /// Comparator of DijkstrasSteps for use in priority queue
    /// \param a A step
    /// \param b Another step
    /// \return If a is "lesser"
    /// \tparam The type of the weight (int/double)
    friend bool operator<(const DijkstrasStep &a, const DijkstrasStep &b) {
        return a.totalDist > b.totalDist;
    }
};

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day15.txt");
    vector<vector<int>> grid;
    vector<vector<int>> min_paths;
    string line;
    while (getline(cin, line)) {
        vector<int> gridline;
        vector<int> min_paths_line;
        for (char c: line) {
            gridline.emplace_back((int)(c - 0x30));
            min_paths_line.emplace_back(INT_MAX);
        }
        grid.emplace_back(gridline);
        min_paths.emplace_back(min_paths_line);
    }
    priority_queue<DijkstrasStep> pq;
    pq.push(DijkstrasStep(make_pair(0, 0), 0));
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        if (top.totalDist + grid[top.nodeID.first][top.nodeID.second] < min_paths[top.nodeID.first][top.nodeID.second]) {
            min_paths[top.nodeID.first][top.nodeID.second] = top.totalDist + grid[top.nodeID.first][top.nodeID.second];
            if (top.nodeID.first == grid.size() - 1 && top.nodeID.second == grid[0].size() - 1) {
                break;
            }
            for (auto delta : DELTAS) {
                int nr = top.nodeID.first + delta[0];
                int nc = top.nodeID.second + delta[1];
                if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size()) {
                    pq.push(DijkstrasStep(make_pair(nr, nc), top.totalDist + grid[top.nodeID.first][top.nodeID.second]));
                }
            }
        }
    }
    cout << "Solution for Part 1: " << min_paths[grid.size() - 1][grid[0].size() - 1] - min_paths[0][0] << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day15.txt");
    vector<vector<int>> tile;
    string line;
    while (getline(cin, line)) {
        vector<int> gridline;
        for (char c: line) {
            gridline.emplace_back((int)(c - 0x30));
        }
        tile.emplace_back(gridline);
    }
    vector<vector<int>> grid;
    vector<vector<int>> min_paths;
    for (int i = 0; i < 5; ++i) {
        for (const auto& row: tile) {
                vector<int> gridline;
                vector<int> min_paths_line;
                for (int j = 0; j < 5; ++j) {
                    int add = i + j;
                    for (int tile_el: row) {
                        int curr_tile_el = tile_el + add;
                        while (curr_tile_el > 9) { curr_tile_el -= 9; }
                        gridline.emplace_back(curr_tile_el);
                        min_paths_line.emplace_back(INT_MAX);
                    }
                }
                grid.emplace_back(gridline);
                min_paths.emplace_back(min_paths_line);
        }
    }
    priority_queue<DijkstrasStep> pq;
    pq.push(DijkstrasStep(make_pair(0, 0), 0));
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        if (top.totalDist + grid[top.nodeID.first][top.nodeID.second] < min_paths[top.nodeID.first][top.nodeID.second]) {
            min_paths[top.nodeID.first][top.nodeID.second] = top.totalDist + grid[top.nodeID.first][top.nodeID.second];
            if (top.nodeID.first == grid.size() - 1 && top.nodeID.second == grid[0].size() - 1) {
                break;
            }
            for (auto delta : DELTAS) {
                int nr = top.nodeID.first + delta[0];
                int nc = top.nodeID.second + delta[1];
                if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size()) {
                    pq.push(DijkstrasStep(make_pair(nr, nc), top.totalDist + grid[top.nodeID.first][top.nodeID.second]));
                }
            }
        }
    }
    cout << "Solution for Part 2: " << min_paths[grid.size() - 1][grid[0].size() - 1] - min_paths[0][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}