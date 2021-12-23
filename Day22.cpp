//
// Created by Jonny Keane on 12/21/21.
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

struct instruction {
public:
    bool turn_on;
    int x0, xf, y0, yf, z0, zf;
    instruction(bool turn_on, int x0, int xf, int y0, int yf, int z0, int zf) :
        turn_on(turn_on), x0(x0), xf(xf), y0(y0), yf(yf), z0(z0), zf(zf) {}
};

struct cube {
public:
    int x0, xf, y0, yf, z0, zf;
    cube(int x0, int xf, int y0, int yf, int z0, int zf) :
             x0(x0), xf(xf), y0(y0), yf(yf), z0(z0), zf(zf) {
        if (x0 > xf || y0 > yf || z0 > zf) {
            cout << "Something wrong" << endl;
        }
    }

    long long volume() const {
        return (abs((long long)(xf - x0)) + 1) *
                (abs((long long)(yf - y0)) + 1) *
                (abs((long long)(zf - z0)) + 1);
    }

    bool does_intersect(cube other) const {
        return !(other.x0 > xf || other.xf < x0 ||
                 other.y0 > yf || other.yf < y0 ||
                 other.z0 > zf || other.zf < z0);
    }

    cube intersect(cube other) const {
        return {max(other.x0, x0), min(other.xf, xf),
                max(other.y0, y0), min(other.yf, yf),
                max(other.z0, z0), min(other.zf, zf)};
    }

    friend bool operator == (const cube & c1, const cube & c2) {
        return c1.x0 == c2.x0 && c1.xf == c2.xf &&
                c1.y0 == c2.y0 && c1.yf == c2.yf &&
                c1.z0 == c2.z0 && c1.zf == c2.zf;
    }

    friend bool operator < (const cube & c1, const cube & c2) {
        return make_tuple(c1.x0, c1.xf, c1.y0, c1.yf, c1.z0, c1.zf) < make_tuple(c2.x0, c2.xf, c2.y0, c2.yf, c2.z0, c2.zf);
    }

    string to_string() const {
        return "Cube:\n"
                        "\tx [" + std::__1::to_string(x0) + "," + std::__1::to_string(xf) + "]\n" +
                        "\ty [" + std::__1::to_string(y0) + "," + std::__1::to_string(yf) + "]\n" +
                        "\tz [" + std::__1::to_string(z0) + "," + std::__1::to_string(zf) + "]";
    }
};

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day22test.txt");
    bool grid[101][101][101];
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            for (int k = 0; k < 101; ++k) {
                grid[i][j][k] = false;
            }
        }
    }
    vector<instruction> instructions;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        string on_str = line.substr(0, 2);
        bool turn_on = on_str == "on";
        line.erase(0, line.find('=') + 1);
        int x0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int xf = stoi(line.substr(0, line.find(',')));
        line.erase(0, line.find('=') + 1);
        int y0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int yf = stoi(line.substr(0, line.find(',')));
        line.erase(0, line.find('=') + 1);
        int z0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int zf = stoi(line);
        instructions.emplace_back(instruction(turn_on, x0, xf, y0, yf, z0, zf));
    }
    for (auto instr: instructions) {
        for (int x = max(-50, instr.x0); x <= min(50, instr.xf); ++x) {
            for (int y = max(-50, instr.y0); y <= min(50, instr.yf); ++y) {
                for (int z = max(-50, instr.z0); z <= min(50, instr.zf); ++z) {
                    grid[x + 50][y + 50][z + 50] = instr.turn_on;
                }
            }
        }
    }
    int on_count = 0;
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            for (int k = 0; k < 101; ++k) {
                if (grid[i][j][k]) { ++on_count; }
            }
        }
    }
    cout << "Solution for Part 1: " << on_count << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day22.txt");
    vector<instruction> instructions;
    map<cube, int> on_cubes;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        string on_str = line.substr(0, 2);
        bool turn_on = on_str == "on";
        line.erase(0, line.find('=') + 1);
        int x0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int xf = stoi(line.substr(0, line.find(',')));
        line.erase(0, line.find('=') + 1);
        int y0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int yf = stoi(line.substr(0, line.find(',')));
        line.erase(0, line.find('=') + 1);
        int z0 = stoi(line.substr(0, line.find('.')));
        line.erase(0, line.find('.') + 2);
        int zf = stoi(line);
        instructions.emplace_back(instruction(turn_on, x0, xf, y0, yf, z0, zf));
    }
    long long on_count = 0;
    for (auto instr: instructions) {
        map<cube, int> new_cubes;
        cube new_cube = cube(instr.x0, instr.xf, instr.y0, instr.yf, instr.z0, instr.zf);

        for (auto p: on_cubes) {
            if (p.first.does_intersect(new_cube)) {
                auto intersect = p.first.intersect(new_cube);
                if (new_cubes.find(intersect) == new_cubes.end()) {
                    new_cubes[intersect] = 0;
                }
                new_cubes[intersect] -= p.second;
            }
        }
        if (instr.turn_on) {
            if (new_cubes.find(new_cube) == new_cubes.end()) {
                new_cubes[new_cube] = 1;
            } else {
                new_cubes[new_cube] += 1;
            }
        }

        for (auto p: new_cubes) {
            if (on_cubes.find(p.first) != on_cubes.end()) {
                on_cubes[p.first] += p.second;
            } else {
                on_cubes[p.first] = p.second;
            }
        }
    }
    for (auto p: on_cubes) {
        on_count += p.first.volume() * p.second;
    }
    cout << "Solution for Part 2: " << on_count << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}