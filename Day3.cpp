//
// Created by Jonny Keane on 12/3/21.
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

const int S = 12;

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day3.txt");
    string curr;
    int bit_counts[S][2];
    while (cin >> curr) {
        reverse(curr.begin(), curr.end());
        bitset<S> curr_bitset = bitset<S>(curr);
//        cout << curr << endl;
        for (int i = 0; i < S; ++i) {
//            cout << curr_bitset[i];
            ++bit_counts[i][curr_bitset[i]];
        }
//        cout << endl << endl;
    }
    int gamma = 0;
    int epsilon = 0;
    for (int i = 0; i < S; ++i) {
        if (bit_counts[i][1] > bit_counts[i][0]) {
            gamma |= 1 << (S - 1 - i);
        } else {
            epsilon |= 1 << (S - 1 - i);
        }
    }
//    cout << epsilon << " " << gamma << endl;
    cout << "Solution for Part 1: " << gamma * epsilon << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day3.txt");
    string curr;
    vector<bitset<S>> vals;
    vector<bool> vis1;
    vector<bool> vis2;
    int ind = 0;
    // take in all of the bitsets
    while (cin >> curr) {
        reverse(curr.begin(), curr.end());
        bitset<S> curr_bitset = bitset<S>(curr);
        vals.emplace_back(curr_bitset);
        vis1.emplace_back(true);
        vis2.emplace_back(true);
        ++ind;
    }
    vector<int> ones;
    vector<int> zeros;
    // OX
    // goes through all of the iterations whittling down the ox numbers
    u_long ox = 0;
    for (int i = 0; i < S; ++i) {
        ones.clear();
        zeros.clear();
        // get all the remaining zeros and ones for the current index
        for (int j = 0; j < vals.size(); ++j) {
            if (vis1[j]) {
                if (vals[j][i]) {
                    ones.emplace_back(j);
                } else {
                    zeros.emplace_back(j);
                }
            }
        }
        // check if done
        if (ones.size() == 1 && zeros.empty()) {
            string ox_s = vals[ones[0]].to_string();
            reverse(ox_s.begin(), ox_s.end());
            ox = bitset<S>(ox_s).to_ulong();
            break;
        }
        if (ones.empty() && zeros.size() == 1) {
            string ox_s = vals[zeros[0]].to_string();
            reverse(ox_s.begin(), ox_s.end());
            ox = bitset<S>(ox_s).to_ulong();
            break;
        }
        // remove smaller side or the zeros if equal
        if (ones.size() >= zeros.size()) {
            for (int idx: zeros) {
                vis1[idx] = false;
            }
        } else {
            for (int idx: ones) {
                vis1[idx] = false;
            }
        }
    }
    // check if down to 1 and 1 at the end
    if (ones.size() == 1 && zeros.size() == 1) {
        string ox_s = vals[ones[0]].to_string();
        reverse(ox_s.begin(), ox_s.end());
        ox = bitset<S>(ox_s).to_ulong();
    }
    // CO2
    // goes through all of the iterations whittling down the co2 numbers
    u_long co2 = 0;
    for (int i = 0; i < S; ++i) {
        ones.clear();
        zeros.clear();
        // collects all remaining ones and zeros for current index
        for (int j = 0; j < vals.size(); ++j) {
            if (vis2[j]) {
                if (vals[j][i]) {
                    ones.emplace_back(j);
                } else {
                    zeros.emplace_back(j);
                }
            }
        }
        // check if done
        if (ones.size() == 1 && zeros.empty()) {
            string co2_s = vals[ones[0]].to_string();
            reverse(co2_s.begin(), co2_s.end());
            co2 = bitset<S>(co2_s).to_ulong();
            break;
        }
        if (ones.empty() && zeros.size() == 1) {
            string co2_s = vals[zeros[0]].to_string();
            reverse(co2_s.begin(), co2_s.end());
            co2 = bitset<S>(co2_s).to_ulong();
            break;
        }
        // remove the larger side or the ones if equal
        if (ones.size() < zeros.size()) {
            for (int idx: zeros) {
                vis2[idx] = false;
            }
        } else {
            for (int idx: ones) {
                vis2[idx] = false;
            }
        }
    }
    // check if down to 1 and 1 at the end
    if (ones.size() == 1 && zeros.size() == 1) {
        string co2_s = vals[zeros[0]].to_string();
        reverse(co2_s.begin(), co2_s.end());
        co2 = bitset<S>(co2_s).to_ulong();
    }

    cout << "Solution for Part 2: " << ox * co2 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}