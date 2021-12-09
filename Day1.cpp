//
// Created by Jonny Keane on 12/2/21.
//

#include <bits/stdc++.h>
#include <istream>

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
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day1.txt");
    int prev;
    cin >> prev;
    int curr;
    int res = 0;
    while (cin >> curr) {

        if (curr > prev) {
//            cout << curr << ">" << prev << endl;
            ++res;
        }
        prev = curr;
    }
    cout << "Solution for Part 1: " << res << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day1.txt");
    vector<int> vals;
    int curr;
    while (cin >> curr) {
        vals.emplace_back(curr);
    }
    int res = 0;
    for (int i = 0; i < vals.size() - 2; ++i) {
        int s_prev = vals[i] + vals[i + 1] + vals[i + 2];
        int s_curr = vals[i + 1] + vals[i + 2] + vals[i + 3];
        if (s_curr > s_prev) {
            ++res;
        }
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