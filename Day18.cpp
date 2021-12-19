//
// Created by Jonny Keane on 12/18/21.
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

pair<bool, vector<pair<int, int>>> split(const vector<pair<int, int>> & snail_num) {
    bool passes = true;
    vector<pair<int, int>> res;
    for (int i = 0; i < snail_num.size(); ++i) {
        if (passes && snail_num[i].first > 9) {
            passes = false;
            res.emplace_back(make_pair(snail_num[i].first / 2, snail_num[i].second + 1));
            res.emplace_back(make_pair(snail_num[i].first - snail_num[i].first / 2, snail_num[i].second + 1));
//            cout << "splitted ";
        } else {
            res.emplace_back(snail_num[i]);
        }
    }
    return make_pair(passes, res);
}

pair<bool, vector<pair<int, int>>> explode(const vector<pair<int, int>> & snail_num) {
    bool passes = true;
    vector<pair<int, int>> res;
    for (int i = 0; i < snail_num.size(); ++i) {
        if (passes && i != snail_num.size() - 1 &&
                   snail_num[i].second > 4 && snail_num[i + 1].second > 4) {
            passes = false;
            if (!res.empty()) {
                res[res.size() - 1].first += snail_num[i].first;
            }
            res.emplace_back(make_pair(0, snail_num[i].second - 1));
            if (i + 1 < snail_num.size() - 1) {
                res.emplace_back(make_pair(snail_num[i + 2].first + snail_num[i + 1].first, snail_num[i + 2].second));
            }
            i += 2; // keep on track
//            cout << "exploded ";
        } else {
            res.emplace_back(snail_num[i]);
        }
    }
    return make_pair(passes, res);
}

vector<pair<int, int>> simplify(const vector<pair<int, int>> & snail_num) {
    vector<pair<int, int>> res = vector<pair<int, int>>(snail_num);
    bool passes = false;
    while (!passes) {
        auto step = explode(res);
        bool explodes = step.first;
        res = step.second;
        if (explodes) {
            step = split(res);
            res = step.second;
            passes = step.first;
        }
        if (passes) {
            for (auto p: res) {
                cout << p.first << "(" << p.second << ") ";
            }
            cout << endl;
        }
    }
    return res;
}

long long magnitude(vector<pair<int, int>> snail_num) {
    return 0;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day18test.txt");
    vector<pair<int, int>> snail_num;
    string line;
    getline(cin, line);
    int bracket_count = 0;
    for (char c: line) {
        if (c == '[') ++bracket_count;
        else if (c == ']') --bracket_count;
        else if (c >= '0' && c <= '9') {
            snail_num.emplace_back(make_pair(c - 0x30, bracket_count));
        }
    }
    while (getline(cin, line)) {
        bracket_count = 0;
        for (char c: line) {
            if (c == '[') ++bracket_count;
            else if (c == ']') --bracket_count;
            else if (c >= '0' && c <= '9') {
                snail_num.emplace_back(make_pair(c - 0x30, bracket_count));
            }
        }
        for (auto & p: snail_num) { ++p.second; } // increases everything by one
        snail_num = simplify(snail_num);
    }
    cout << "Solution for Part 1: " << magnitude(snail_num) << endl;
}

void part_2() {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}