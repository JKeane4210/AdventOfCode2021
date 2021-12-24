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

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day24.txt");

    if (valid_code("99598963999971")) {
        cout << "Solution for Part 1: " << 99598963999971 << endl;
    }
}

void part_2() {
    if (valid_code("93151411711211")) {
        cout << "Solution for Part 2: " << 93151411711211 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}