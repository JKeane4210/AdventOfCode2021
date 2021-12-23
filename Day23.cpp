//
// Created by Jonny Keane on 12/23/21.
//

#include <bits/stdc++.h>

#include <utility>

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

const int DELTAS[4][2] = {{-1, 0}, {0, 1}, {0, -1}};
const string FINAL[5] = {"#############",
                         "#...........#",
                         "###A#B#C#D###",
                         "  #A#B#C#D#",
                         "  #########"};
const string FINAL_2[7] = {"#############",
                         "#...........#",
                         "###A#B#C#D###",
                         "  #A#B#C#D#",
                         "  #A#B#C#D#",
                         "  #A#B#C#D#",
                         "  #########"};
const map<char, long> COSTS = {{'A', 1},
                              {'B', 10},
                              {'C', 100},
                              {'D', 1000}};
const map<char, int> COLS = {{'A', 3},
                             {'B', 5},
                             {'C', 7},
                             {'D', 9}};
const set<int> ROOMS = {3, 5, 7, 9};
const int HALLWAY = 1;

struct destination {
public:
    int row;
    int col;
    long energy_cost;
    destination(int row, int col, int energy_cost) : row(row), col(col), energy_cost(energy_cost) {}
};

template <size_t t>
struct step {
public:
    long energy;
    array<string, t> grid;
    set<pair<int, int>> locked;
    step(int energy, array<string, t> grid) : energy(energy), grid(grid) {}
    vector<step> valid_moves() {
        vector<step> res;
        for (int i = 0; i < t; ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (COSTS.find(grid[i][j]) != COSTS.end()) { // if is amphipod
                    for (auto dest: dests(i, j, 0, i, j, COSTS.at(grid[i][j]), set<pair<int, int>>(), grid[i][j])) {
                        if (dest.row > HALLWAY && COLS.at(grid[i][j]) != dest.col) continue; // if got to wrong room, skip
                        if (i == HALLWAY && !(COLS.at(grid[i][j]) == dest.col)) continue; // if in hallway to start and doesn't end up in room, skip
                        step new_step = step(energy + dest.energy_cost, array<string, t>(grid));
                        new_step.grid[dest.row][dest.col] = grid[i][j];
                        new_step.grid[i][j] = '.';
                        if (!new_step.valid_grid()) { // DEBUG
                            for (int k = 0; k < t; ++k) {
                                cout << new_step.grid[k] << endl;
                            }
                            cout << endl;
                        }
                        res.emplace_back(new_step);
                    }
                }
            }
        }
        return res;
    }

    vector<destination> dests(int r, int c, int energy_cost, int start_r, int start_c, int jump_cost, set<pair<int, int>> visited, char amphipod) {
        vector<destination> res;
        if (start_c == COLS.at(amphipod) && room_ready(amphipod)) return res;
        if ((r != start_r || c != start_c) && ROOMS.find(c) == ROOMS.end()) { // current location valid
            res.emplace_back(destination(r, c, energy_cost));
        }
        if (c == COLS.at(amphipod) && room_ready(amphipod)) {
            while (grid[r + 1][c] == '.') {
                ++r;
                energy_cost += jump_cost;
            }
            res.emplace_back(destination(r, c, energy_cost));
            return res;
        }
        for (auto delta: DELTAS) { // add all other dests
            int nr = r + delta[0];
            int nc = c + delta[1];
            if (grid[nr][nc] == '.' && visited.find(make_pair(nr, nc)) == visited.end()) {
                set<pair<int, int>> new_visited(visited);
                new_visited.insert(make_pair(nr, nc));
                for (auto dest: dests(nr, nc, energy_cost + jump_cost, start_r, start_c, jump_cost, new_visited, amphipod)) {
                    res.emplace_back(dest);
                }
            }
        }
        return res;
    }

    bool valid_grid() {
        int count = 0;
        for (int i = 0; i < t; ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (COSTS.find(grid[i][j]) != COSTS.end()) {
                    ++count;
                }
            }
        }
        return count == (t - 3) * 4;
    }

    bool room_ready(char amphipod) {
        bool res = true;
        for (int i = 0; i < t - 3; ++i) {
            res &= (grid[HALLWAY + 1 + i][COLS.at(amphipod)] == '.' ||
                    grid[HALLWAY + 1 + i][COLS.at(amphipod)] == amphipod);
        }
        return res;
    }

    string grid_str() const {
        string res;
        for (int i = 0; i < t; ++i) {
            res += grid[i];
        }
        return res;
    }

    friend bool operator <(const step & s1, const step & s2) {
        return s1.energy > s2.energy;
    }
};

bool is_done(step<5> s) {
    for (int i = 0; i < 5; ++i) {
        if (s.grid[i] != FINAL[i]) {
            return false;
        }
    }
    return true;
}

bool is_done2(step<7> s) {
    for (int i = 0; i < 7; ++i) {
        if (s.grid[i] != FINAL_2[i]) {
            return false;
        }
    }
    return true;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day23.txt");
    array<string, 5> grid;
    for (int i = 0; i < 5; ++i) {
        string line;
        getline(cin, line);
        grid[i] = line;
    }
    map<string, long> visited_grids;
    priority_queue<step<5>> pq;
    pq.push(step<5>(0, grid));
    long min_ = LONG_MAX;
    while (!pq.empty()) {
        step<5> top = pq.top();
        pq.pop();
        if (visited_grids.find(top.grid_str()) != visited_grids.end() ||
            visited_grids[top.grid_str()] < top.energy) continue;
        if (is_done(top)) {
            min_ = min(min_, top.energy);
            break;
        }
        visited_grids[top.grid_str()] = top.energy;
        for (const step<5> & s: top.valid_moves()) {
            pq.push(s);
        }
    }
    cout << "Solution for Part 1: " << min_ << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day23b.txt");
    array<string, 7> grid;
    for (int i = 0; i < 7; ++i) {
        string line;
        getline(cin, line);
        grid[i] = line;
    }
    map<string, long> visited_grids;
    queue<step<7>> q;
    q.push(step<7>(0, grid));
    long min_ = LONG_MAX;
    while (!q.empty()) {
        step<7> top = q.front();
        q.pop();
        if (is_done2(top)) {
            min_ = min(min_, top.energy);
        }
        if (visited_grids.find(top.grid_str()) != visited_grids.end() &&
            visited_grids[top.grid_str()] < top.energy) continue;
        visited_grids[top.grid_str()] = top.energy;
        for (const step<7>& s: top.valid_moves()) {
            q.push(s);
        }
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