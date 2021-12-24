//
// Created by Jonny Keane on 12/23/21.
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

struct instr {
public:
    string op, a, b;
    instr(string op, string a, string b) : op(op), a(a), b(b) {}
};

// these are the constraints for a code
// I calculated these by hand :)
bool valid_code(string code) {
    return code[3] == code[2] + 4 &&
            code[6] == code[5] - 3 &&
            code[8] == code[7] + 6 &&
            code[10] == code[9] &&
            code[11] == code[4] + 1 &&
            code[12] == code[1] - 2 &&
            code[13] == code[0] - 8;
}

string max_code(vector<tuple<int, int, int>> pairs) {
    string code(' ', 14);
    for (auto pair: pairs) {
        int max_ = 0;
        for (int i = 1; i <= 9; ++i) {
            if (i + get<2>(pair) > 0 && i + get<2>(pair) < 10) {
                max_ = max(max_, i + get<2>(pair));
            }
        }
        code[get<0>(pair)] = (char)(max_ + 0x30);
        code[get<1>(pair)] = (char)(max_ - get<2>(pair) + 0x30);
    }
    return code;
}

string min_code(vector<tuple<int, int, int>> pairs) {
    string code(' ', 14);
    for (auto pair: pairs) {
        int min_ = 10;
        for (int i = 1; i <= 9; ++i) {
            if (i + get<2>(pair) > 0 && i + get<2>(pair) < 10) {
                min_ = min(min_, i + get<2>(pair));
            }
        }
        code[get<0>(pair)] = (char)(min_ + 0x30);
        code[get<1>(pair)] = (char)(min_ - get<2>(pair) + 0x30);
    }
    return code;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day24.txt");
    stack<pair<int, int>> deltas;
    vector<tuple<int, int, int>> pairs;
    for (int i = 0; i < 14; ++i) {
        vector<instr> instrs;
        for (int j = 0; j < 18 ; ++j) {
            string op, a;
            cin >> op >> a;
            if (op != "inp") {
                string b;
                cin >> b;
                instrs.emplace_back(instr(op, a, b));
            } else {
                instrs.emplace_back(instr(op, a, ""));
            }
        }
        if (stoi(instrs[4].b) == 1) {
            deltas.push(make_pair(i, stoi(instrs[15].b)));
        } else {
            auto top = deltas.top();
            deltas.pop();
            pairs.emplace_back(i, top.first, top.second + stoi(instrs[5].b));
        }
    }
    string code = max_code(pairs);

    cout << "Solution for Part 1: " <<  code << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day24.txt");
    stack<pair<int, int>> deltas;
    vector<tuple<int, int, int>> pairs;
    for (int i = 0; i < 14; ++i) {
        vector<instr> instrs;
        for (int j = 0; j < 18 ; ++j) {
            string op, a;
            cin >> op >> a;
            if (op != "inp") {
                string b;
                cin >> b;
                instrs.emplace_back(instr(op, a, b));
            } else {
                instrs.emplace_back(instr(op, a, ""));
            }
        }
        if (stoi(instrs[4].b) == 1) {
            deltas.push(make_pair(i, stoi(instrs[15].b)));
        } else {
            auto top = deltas.top();
            deltas.pop();
            pairs.emplace_back(i, top.first, top.second + stoi(instrs[5].b));
        }
    }
    string code = min_code(pairs);

    cout << "Solution for Part 2: " <<  code << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}