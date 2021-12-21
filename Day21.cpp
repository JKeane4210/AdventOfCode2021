//
// Created by Jonny Keane on 12/20/21.
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

void part_1(int p1_loc, int p2_loc) {
    int score_1 = 0;
    int score_2 = 0;
    int moves = 0;
    int curr_die = 0;
    bool p1_turn = true;
    while (score_1 < 1000 && score_2 < 1000) {
        int jump = 0;
        for (int i = 0; i < 3; ++i) {
            jump += curr_die + 1;
            curr_die = (curr_die + 1) % 100;
            ++moves;
        }
        if (p1_turn) {
            p1_turn = false;
            p1_loc = (p1_loc + jump) % 10;
            score_1 += p1_loc + 1;
        } else {
            p1_turn = true;
            p2_loc = (p2_loc + jump) % 10;
            score_2 += p2_loc + 1;
        }
    }
    int res = p1_turn ? score_1 * moves : score_2 * moves;
    cout << "Solution for Part 1: " << res << endl;
}

void part_2(int p1, int p2) {
    const int MOVES = 24; // just to be safe in case getting 1, 2, 1, 2
    long long dp1[MOVES][10][31]; // [move, position, score] -> scores up to 30 because highest you can get to
    long long dp2[MOVES][10][31]; // [move, position, score] -> scores up to 30 because highest you can get to
    for (int i = 0; i < MOVES; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 31; ++k) {
                dp1[i][j][k] = 0;
                dp2[i][j][k] = 0;
            }
        }
    }
    dp1[0][p1][0] = 1;
    dp2[1][p2][0] = 1;
    for (int move = 0; move < MOVES - 2; ++move) {
        for (int r1 = 1; r1 <= 3; ++r1) {
            for (int r2 = 1; r2 <= 3; ++r2) {
                for (int r3 = 1; r3 <= 3; ++r3) {
                    int jump = r1 + r2 + r3;
                    for (int pos = 0; pos < 10; ++pos) {
                        int move_score = (pos + jump) % 10 + 1;
                        for (int score = 0; score < 21; ++score) { // don't want to add for finished games
                            if (move % 2 == 0) {
                                dp1[move + 2][(pos + jump) % 10][score + move_score] += dp1[move][pos][score];
                            } else {
                                dp2[move + 2][(pos + jump) % 10][score + move_score] += dp2[move][pos][score];
                            }
                        }
                    }
                }
            }
        }
    }

    long long p1_games = 0;
    long long p2_games = 0;
    for (int moves = 0; moves < MOVES; ++moves) {
        for (int p2_score = 0; p2_score <= 30; ++p2_score) {
            for (int p1_score = 0; p1_score <= 30; ++p1_score) {
                for (int p1_loc = 0; p1_loc < 10; ++p1_loc) {
                    for (int p2_loc = 0; p2_loc < 10; ++p2_loc) {
                        // if the score is winning, see how many games of this at this location from the
                        // previous move it would have beat and multiply by number of instances of the
                        // winning game there are to add to the given player
                        //
                        // for a second, this felt like I was missing the fact that the universes split
                        // for both, meaning more scalings by 27 rolls; however, if I am just solving how
                        // many instances each player gets to a situation I am trying to compute, then I
                        // get the number of universes that got to this state by multiplying the counts
                        // of each of the separate states
                        if (p1_score >= 21 && p2_score < 21) {
                            p1_games += dp1[moves][p1_loc][p1_score] * dp2[moves - 1][p2_loc][p2_score];
                        }
                        if (p2_score >= 21 && p1_score < 21) {
                            p2_games += dp2[moves][p2_loc][p2_score] * dp1[moves - 1][p1_loc][p1_score];
                        }
                    }
                }
            }
        }
    }
    cout << "Solution for Part 2: " << max(p1_games, p2_games) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day21.txt");
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    int p1_loc = stoi(s1.substr(s1.find(":") + 1));
    int p2_loc = stoi(s2.substr(s2.find(":") + 1));
    part_1(p1_loc - 1, p2_loc - 1);
    part_2(p1_loc - 1, p2_loc - 1);
    return 0;
}