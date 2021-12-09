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

int part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day4.txt");
    vector<vector<vector<pair<int, bool>>>> grids;
    string order;
    cin >> order;
    bool done = false;
    while (true) {
        vector<vector<pair<int, bool>>> grid(5, vector<pair<int, bool>>(5));
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int num;
                if (cin >> num) {
                    grid[i][j] = make_pair(num, false);
                } else {
                    done = true;
                    break;
                }
            }
        }
        if (done) {
            break;
        } else {
            grids.emplace_back(grid);
        }
    }
    int res = 0;
    size_t pos = 0;
    while ((pos = order.find(",")) != string::npos) {
        int num = stoi(order.substr(0, pos));
        bool winner = false;
        for (auto & grid: grids) {
            // check off any hits
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (grid[i][j].first == num) {
                        grid[i][j].second = true;
                    }
                }
            }
            // check if winner
            for (int i = 0; i < 5; ++i) {
                bool rowTrue = true;
                bool colTrue = true;
                for (int j = 0; j < 5; ++j) {
                    if (!grid[i][j].second) {
                        rowTrue = false;
                    }
                    if (!grid[j][i].second) {
                        colTrue = false;
                    }
                }
                if (rowTrue || colTrue) {
                    winner = true;
                    break;
                }
            }
            // if winner, get result
            int total = 0;
            if (winner) {
                for (int i = 0; i < 5; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        if (!grid[i][j].second) {
                            total += grid[i][j].first;
                        }
                    }
                }
                res = total * num;
                break;
            }
        }
        if (winner) {
            break;
        }
        order.erase(0, order.find(",") + 1);
    }
    cout << "Solution for Part 1: " << res << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day4.txt");
    vector<vector<vector<pair<int, bool>>>> grids;
    vector<bool> isWinner;
    string order;
    cin >> order;
    bool done = false;
    while (true) {
        vector<vector<pair<int, bool>>> grid(5, vector<pair<int, bool>>(5));
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int num;
                if (cin >> num) {
                    grid[i][j] = make_pair(num, false);
                } else {
                    done = true;
                    break;
                }
            }
        }
        if (done) {
            break;
        } else {
            grids.emplace_back(grid);
            isWinner.emplace_back(false);
        }
    }
    int res = 0;
    size_t pos = 0;
    while ((pos = order.find(",")) != string::npos) {
        int num = stoi(order.substr(0, pos));
        int grid_idx = 0;
        int latest_winner = -1;
        for (auto & grid: grids) {
            if (isWinner[grid_idx]) {
                ++grid_idx;
                continue;
            }
            bool winner = false;
            // check off any hits
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (grid[i][j].first == num) {
                        grid[i][j].second = true;
                    }
                }
            }
            // check if winner
            for (int i = 0; i < 5; ++i) {
                bool rowTrue = true;
                bool colTrue = true;
                for (int j = 0; j < 5; ++j) {
                    if (!grid[i][j].second) {
                        rowTrue = false;
                    }
                    if (!grid[j][i].second) {
                        colTrue = false;
                    }
                }
                if (rowTrue || colTrue) {
                    winner = true;
                    break;
                }
            }
            // if winner, add to list of winners
            if (winner) {
                latest_winner = grid_idx;
                isWinner[grid_idx] = true;
            }
            ++grid_idx;
        }
        // check if everyone has won
        bool all_won = true;
        for (bool b: isWinner) {
            if (!b) {
                all_won = false;
                break;
            }
        }
        if (all_won) {
            int total = 0;
            vector<vector<pair<int, bool>>> last = grids[latest_winner];
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (!last[i][j].second) {
                        total += last[i][j].first;
                    }
                }
            }
            res = total * num;
            break;
        }
        order.erase(0, order.find(",") + 1);
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