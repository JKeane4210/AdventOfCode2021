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

struct on_cube {
public:
    int x0, xf, y0, yf, z0, zf;
    on_cube(int x0, int xf, int y0, int yf, int z0, int zf) :
             x0(x0), xf(xf), y0(y0), yf(yf), z0(z0), zf(zf) {}
    long long volume() {
        return (abs((long long)(xf - x0)) + 1) * (abs((long long)(yf - y0)) + 1) * (abs((long long)(zf - z0)) + 1);
    }
    on_cube intersect(on_cube other) {
        return on_cube(max(other.x0, x0), min(other.xf, xf),
                       max(other.y0, y0), min(other.yf, yf),
                       max(other.z0, z0), min(other.xf, zf));
    }

    vector<on_cube> apply_instruction(instruction instr, bool keep_inner = true) {
        if (instr.turn_on) {
            vector<on_cube> res;
            if (keep_inner) {
                res.emplace_back(on_cube(x0, xf, y0, yf, z0, zf)); // original cube
            }
            if (instr.x0 < x0) {
                res.emplace_back(on_cube(instr.x0, min(instr.xf, x0 - 1),
                                     instr.y0, instr.yf,
                                     instr.z0, instr.zf)); // left
            }
            if (instr.xf > xf) {
                res.emplace_back(on_cube(max(instr.x0, xf + 1), instr.xf,
                                         instr.y0, instr.yf,
                                         instr.z0, instr.zf)); // right
            }
            if (instr.y0 < y0) {
                res.emplace_back(on_cube(max(x0, instr.x0), min(xf, instr.xf),
                                         instr.y0, min(instr.yf, y0 - 1),
                                         instr.z0, instr.zf)); // front
            }
            if (instr.yf > yf) {
                res.emplace_back(on_cube(max(x0, instr.x0), min(xf, instr.xf),
                                         max(instr.y0, yf + 1), instr.yf,
                                         instr.z0, instr.zf)); // back
            }
            if (instr.z0 < z0) {
                res.emplace_back(on_cube(max(x0, instr.x0), min(xf, instr.xf),
                                         max(y0, instr.y0), min(yf, instr.yf),
                                         instr.z0, min(instr.zf, z0 - 1))); // bottom
            }
            if (instr.zf > zf) {
                res.emplace_back(on_cube(max(x0, instr.x0), min(xf, instr.xf),
                                         max(y0, instr.y0), min(yf, instr.yf),
                                         max(instr.z0, zf + 1), instr.zf)); // bottom
            }
            return res;
        } else {
            on_cube inner(instr.x0, instr.xf, instr.y0, instr.yf, instr.z0, instr.zf);
            return inner.apply_instruction(instruction(true, x0, xf, y0, yf, z0, zf), false);
        }
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
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day22test.txt");
    vector<instruction> instructions;
    vector<on_cube> on_cubes;
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
    int ind = 0;
    for (auto instr: instructions) {
        if (on_cubes.empty() && instr.turn_on) {
            on_cubes.emplace_back(on_cube(instr.x0, instr.xf, instr.y0, instr.yf, instr.z0, instr.zf));
        } else {
            vector<on_cube> new_cubes;
            for (auto cube: on_cubes) {
                for (auto new_cube: cube.apply_instruction(instr)) {
//                    cout << new_cube.volume() << endl;
                    if (new_cube.volume() > 0) {
                        new_cubes.emplace_back(new_cube);
                    }
                }
            }
            on_cubes = new_cubes;
        }
        cout << on_cubes.size() << endl;
        long long total_volume = 0;
        for (auto c: on_cubes) {
            total_volume += c.volume();
        }
//        cout << "*" <<  total_volume << endl;
//        if (ind++ > 3) {
//            return;
//        }
    }
    long long on_count = 0;
    for (auto cube: on_cubes) {
        on_count += cube.volume();
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