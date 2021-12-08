//
// Created by Jonny Keane on 12/8/21.
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

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day8.txt");
    int count_easy = 0;
    string line;
    while (getline(cin, line)) {

        line.erase(0, line.find("|") + 2);
        for (int i = 0; i < 3; ++i) {
            int num = line.substr(0, line.find(" ")).size();
            if (num != 5 && num != 6) {
                ++count_easy;
            }
            line.erase(0, line.find(" ") + 1);
        }

        int num = line.size();
        if (num != 5 && num != 6) {
            ++count_easy;
        }
    }
    cout << "Solution for Part 1: " << count_easy << endl;
}

set<char> set_xor(set<char> a, set<char> b) {
    set<char> res;
    for (char c: a) {
        if (b.find(c) == b.end()) {
            res.insert(c);
        }
    }
    for (char c: b) {
        if (a.find(c) == a.end()) {
            res.insert(c);
        }
    }
    return res;
}

bool set_equal(set<char> a, set<char> b) {
    for (char c: a) {
        if (b.find(c) == b.end()) {
            return false;
        }
    }
    for (char c: b) {
        if (a.find(c) == a.end()) {
            return false;
        }
    }
    return true;
}

int solve(string line) {
    vector<set<char>> nums;
    vector<set<char>> outputs;
    // loading in nums and outputs
    for (int i = 0; i < 10 ; ++i) {
        string num = line.substr(0, line.find(" "));
        set<char> num_set;
        for (char c: num) {
            num_set.insert(c);
        }
        nums.emplace_back(num_set);
        line.erase(0, line.find(" ") + 1);
    }

    line.erase(0, 2); // erases "| "
    for (int i = 0; i < 3; ++i) {
        string num = line.substr(0, line.find(" "));
        set<char> num_set;
        for (char c: num) {
            num_set.insert(c);
        }
        outputs.emplace_back(num_set);
        line.erase(0, line.find(" ") + 1);
    }
    set<char> num_set;
    for (char c: line) {
        num_set.insert(c);
    }
    outputs.emplace_back(num_set);
    // finding easy
    set<char> num_map[10];
    for (const set<char>& s: nums) {
        if (s.size() == 4) {
            num_map[4] = s;
        } else if (s.size() == 2) {
            num_map[1] = s;
        } else if (s.size() == 3) {
            num_map[7] = s;
        } else if (s.size() == 7) {
            num_map[8] = s;
        }
    }
    // finding 6 segs
    for (const set<char>& s: nums) {
        if (s.size() == 6) {
            if (set_xor(s, num_map[7]).size() == 3) {
                if (set_xor(s, num_map[4]).size() == 2) {
                    num_map[9] = set<char>(s);
                } else {
                    num_map[0] = set<char>(s);
                }
            } else if (set_xor(s, num_map[7]).size() == 5) {
                num_map[6] = set<char>(s);
            }
        }
    }
    // finding five segs
    for (set<char> s: nums) {
        if (s.size() == 5) {
            if (set_xor(s, num_map[6]).size() == 1) {
                num_map[5] = set<char>(s);
            } else {
                if (set_xor(s, num_map[9]).size() == 3) {
                    num_map[2] = set<char>(s);
                } else {
                    num_map[3] = set<char>(s);
                }
            }
        }
    }
    string out;
    for (const set<char>& output: outputs) {
        for (int i = 0; i < 10; ++i) {
            if (set_equal(output, num_map[i])) {
                out += to_string(i);
                break;
            }
        }
    }

    return stoi(out);
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day8.txt");
    int total = 0;
    string line;
    while (getline(cin, line)) {
        total += solve(line);
    }
    cout << "Solution for Part 2: " << total << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}