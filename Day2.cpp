//
// Created by Jonny Keane on 12/2/21.
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
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day2.txt");
    int depth = 0;
    int horizontal = 0;
    string cmd;
    int amt;
    while (cin >> cmd) {
        cin >> amt;
        if (cmd == "forward") {
            horizontal += amt;
        } else if (cmd == "up") {
            depth -= amt;
        } else {
            depth += amt;
        }
    }
    cout << "Solution for Part 1: " << depth * horizontal << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day2.txt");
    int depth = 0;
    int horizontal = 0;
    int aim = 0;
    string cmd;
    int amt;
    while (cin >> cmd) {
        cin >> amt;
        if (cmd == "forward") {
            horizontal += amt;
            depth += amt * aim;
        } else if (cmd == "up") {
            aim -= amt;
        } else {
            aim += amt;
        }
    }
    cout << "Solution for Part 2: " << depth * horizontal << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}
