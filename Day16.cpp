//
// Created by Jonny Keane on 12/16/21.
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

const map<char, string> hex_bin =
        {
                {'0', "0000"},
                {'1', "0001"},
                {'2', "0010"},
                {'3', "0011"},
                {'4', "0100"},
                {'5', "0101"},
                {'6', "0110"},
                {'7', "0111"},
                {'8', "1000"},
                {'9', "1001"},
                {'A', "1010"},
                {'B', "1011"},
                {'C', "1100"},
                {'D', "1101"},
                {'E', "1110"},
                {'F', "1111"}
        };

long long bin_string(string s) {
    long long res = 0;
    for (char i : s) {
        if (i == '1') {
            res |= 1;
        }
        res <<= 1;
    }
    res >>= 1;
    return res;
}

string hex_to_bin_string(const string& s) {
    string res;
    for (char c: s) {
        res += hex_bin.at(c);
    }
    return res;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day16.txt");
    string pkt;
    cin >> pkt;
    pkt = hex_to_bin_string(pkt);
    int res = 0;
    stringstream hex_conv;
    while (!pkt.empty()) {
        string version_string = pkt.substr(0, 3);
        pkt.erase(0, 3);
        string type_string = pkt.substr(0, 3);
        pkt.erase(0, 3);
        long long version = bin_string(version_string);
        long long type = bin_string(type_string);
        res += version;
        if (type == 4) {
            while (pkt[0] == '1') { pkt.erase(0, 5); }
            pkt.erase(0, 5);
        } else {
            int length_type = pkt[0] - 0x30;
            pkt.erase(0, 1);
            if (length_type == 0) {
                string total_length_str = pkt.substr(0, 15);
                pkt.erase(0, 15);
                // at this point, can return to parse sub-packet
            } else {
                string packet_cnt_str = pkt.substr(0, 11);
                pkt.erase(0, 11);
                // at this point, can return to parse sub-packet
            }
        }
    }
    cout << "Solution for Part 1: " << res << endl;
}

pair<string, long long> next_packet(string pkt) {
    string version_string = pkt.substr(0, 3);
    pkt.erase(0, 3);
    string type_string = pkt.substr(0, 3);
    pkt.erase(0, 3);
    long long version = bin_string(version_string);
    long long type = bin_string(type_string);
    long long value = 0;
    vector<long long> sub_packets;
    // handling length bit if not type 4
    if (type != 4) {
        int length_type = pkt[0] - 0x30;
        pkt.erase(0, 1);
        if (length_type == 0) { // defines number of bits used for sub-packets
            string total_length_str = pkt.substr(0, 15);
            pkt.erase(0, 15);
            long long total_length = bin_string(total_length_str);
            string sub_packet = pkt.substr(0, total_length);
            pkt.erase(0, total_length);
            while (!sub_packet.empty()) {

                auto read_pkt = next_packet(sub_packet);
                sub_packet = read_pkt.first;
                sub_packets.emplace_back(read_pkt.second);
            }
        } else { // defines number of sub-packets
            string packet_cnt_str = pkt.substr(0, 11);
            pkt.erase(0, 11);
            long long packet_cnt = bin_string(packet_cnt_str);
            for (int i = 0; i < packet_cnt; ++i) {
                auto read_pkt = next_packet(pkt);
                pkt = read_pkt.first;
                sub_packets.emplace_back(read_pkt.second);
            }
        }
    }
    // handling different types
    switch (type) {
        case 0: {
            for (auto sub_pkt: sub_packets) { value += sub_pkt; }
            break;
        }
        case 1: {
            value = 1;
            for (auto sub_pkt: sub_packets) { value *= sub_pkt; }
            break;
        }
        case 2: {
            value = minimum(sub_packets);
            break;
        }
        case 3: {
            value = maximum(sub_packets);
            break;
        }
        case 4: { // literal case
            string literal;
            while (pkt[0] == '1') {
                literal += pkt.substr(1, 4);
                pkt.erase(0, 5);
            }
            literal += pkt.substr(1, 4);
            pkt.erase(0, 5);
            value = bin_string(literal);
            break;
        }
        case 5: {
            if (sub_packets[0] > sub_packets[1]) {
                value = 1;
            } else {
                value = 0;
            }
            break;
        }
        case 6: {
            if (sub_packets[0] < sub_packets[1]) {
                value = 1;
            } else {
                value = 0;
            }
            break;
        }
        case 7: {
            if (sub_packets[0] == sub_packets[1]) {
                value = 1;
            } else {
                value = 0;
            }
            break;
        }
    }

    return make_pair(pkt, value);
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day16.txt");
    string pkt;
    cin >> pkt;
    pkt = hex_to_bin_string(pkt);
    long long res = 0;
    stringstream hex_conv;
    while (!pkt.empty()) {
        auto read_pkt = next_packet(pkt);
        pkt = read_pkt.first;
        res += read_pkt.second;
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