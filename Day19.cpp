//
// Created by Jonny Keane on 12/19/21.
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

class coord {
public:
    int x;
    int y;
    int z;
    coord() : x(0), y(0), z(0) {}
    coord(int x, int y, int z) : x(x), y(y), z(z) {}
    coord(const coord & c) : x(c.x), y(c.y), z(c.z) {}
    bool operator ==(const coord & c) const {
        return x == c.x && y == c.y && z == c.z;
    }
    friend bool operator <(const coord & c1, const coord & c2) {
        if (c1.x == c2.x) {
            if (c1.y == c2.y) { return c1.z < c2.z; }
            else { return c1.y < c2.y; }
        } else { return c1.x < c2.x; }
    }
};

coord add(const coord& c1, const coord & c2) {
    return {c1.x + c2.x, c1.y + c2.y, c1.z + c2.z};
}

coord sub(const coord & c1, const coord & c2) {
    return {c1.x - c2.x, c1.y - c2.y, c1.z - c2.z};
}

// might need to check later down the road
vector<coord> coord_mappings(const coord & c) {
    return vector<coord>
                   {
                        coord(c.x, c.y, c.z),
                        coord(c.x, c.z, -c.y),
                        coord(c.x, -c.y, -c.z),
                        coord(c.x, -c.z, c.y),

                        coord(-c.x, c.y, -c.z),
                        coord(-c.x, c.z, c.y),
                        coord(-c.x, -c.y, c.z),
                        coord(-c.x, -c.z, -c.y),

                        coord(c.y, c.x, -c.z),
                        coord(c.z ,c.x , c.y),
                        coord(-c.y, c.x, c.z),
                        coord(-c.z, c.x , -c.y),

                        coord(c.y, -c.x, c.z),
                        coord(c.z, -c.x, -c.y),
                        coord(-c.y,-c.x ,-c.z),
                        coord(-c.z, -c.x ,c.y),

                        coord(c.y, c.z, c.x),
                        coord(-c.z, c.y, c.x),
                        coord(-c.y, -c.z, c.x),
                        coord(c.z, -c.y, c.x),

                        coord(c.y, -c.z, -c.x),
                        coord(c.z, c.y, -c.x),
                        coord(-c.y, c.z, -c.x),
                        coord(-c.z, -c.y, -c.x)
                   };
}

// scanner1 will always come in with the generalized coordinates (from our "origin")
pair<vector<coord>, coord> similar(const vector<coord>& scanner1, const vector<coord>& scanner2) {
    for (int i = 0; i < 24; ++i) { // orientations
        vector<coord> mapped_coords;
        // creates this orientation's points
        for (const auto & c : scanner2) {
            mapped_coords.emplace_back(coord_mappings(c)[i]);
        }
        // for every possible base point in scanner 1 that can be a point of comparison
        for (const auto & base: scanner1) {
            // for every possible coordinate that can be associated with the base
            for (const auto & c1: mapped_coords) {
                coord scanner2_loc = sub(base, c1);
                int count = 0;
                for (const auto & c2: mapped_coords) {
                    coord c_gen = add(scanner2_loc, c2);
                    // if the scanner1 list has the adjusted c2, add to matches count
                    if (find_if(scanner1.begin(), scanner1.end(), [c_gen] (const coord& sc1_c) { return sc1_c == c_gen; }) != scanner1.end()) {
                        ++count;
                    }
                }
                if (count >= 12) {
                    vector<coord> res;
                    for (const auto & rel_coord: mapped_coords) {
                        res.emplace_back(add(scanner2_loc, rel_coord));
                    }
                    return make_pair(res, scanner2_loc);
                }
            }
        }
    }
    return make_pair(vector<coord>(), coord(-1, -1, -1));
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day19.txt");
    vector<vector<coord>> scanners;
    string line;
    while (getline(cin, line)) {
        if (line.find("scanner") != string::npos) {
            vector<coord> scanner;
            while(getline(cin, line)) {
                if (line.find(',') == string::npos) { break; }
                int x = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',') + 1);
                int y = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',') + 1);
                int z = stoi(line);
                scanner.emplace_back(coord(x, y, z));
            }
            scanners.emplace_back(scanner);
        }
    }
    set<coord> general_coords;
    for (const auto& coord: scanners[0]) {
        general_coords.insert(coord);
    }
    queue<int> generalized;
    set<pair<int, int>> visited;
    generalized.push(0);
    coord scanner_locs[scanners.size()];
    while (!generalized.empty()) {
        int top = generalized.front();
        generalized.pop();
        for (int i = 0; i < scanners.size(); ++i) {
            if (i == top) continue;
            if (visited.find(make_pair(i, top)) != visited.end() || visited.find(make_pair(top, i)) != visited.end()) continue;
            auto & scanner1 = scanners[top];
            auto & scanner2 = scanners[i];
            auto similar_coords = similar(scanner1, scanner2);
            if (!similar_coords.first.empty()) {
                generalized.push(i);
                for (const auto& c: similar_coords.first) {
                    general_coords.insert(c);
                }
                visited.insert(make_pair(i, top));
                scanners[i] = similar_coords.first;
                scanner_locs[i] = similar_coords.second;
            }
        }
    }
    cout << "Solution for Part 1: " << general_coords.size() << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day19.txt");
    vector<vector<coord>> scanners;
    string line;
    while (getline(cin, line)) {
        if (line.find("scanner") != string::npos) {
            vector<coord> scanner;
            while(getline(cin, line)) {
                if (line.find(',') == string::npos) { break; }
                int x = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',') + 1);
                int y = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',') + 1);
                int z = stoi(line);
                scanner.emplace_back(coord(x, y, z));
            }
            scanners.emplace_back(scanner);
        }
    }
    set<coord> general_coords;
    for (const auto& coord: scanners[0]) {
        general_coords.insert(coord);
    }
    queue<int> generalized;
    set<pair<int, int>> visited;
    generalized.push(0);
    coord scanner_locs[scanners.size()];
    while (!generalized.empty()) {
        int top = generalized.front();
        generalized.pop();
        for (int i = 0; i < scanners.size(); ++i) {
            if (i == top) continue;
            if (visited.find(make_pair(i, top)) != visited.end() || visited.find(make_pair(top, i)) != visited.end()) continue;
            auto & scanner1 = scanners[top];
            auto & scanner2 = scanners[i];
            auto similar_coords = similar(scanner1, scanner2);
            if (!similar_coords.first.empty()) {
                generalized.push(i);
                for (const auto& c: similar_coords.first) {
                    general_coords.insert(c);
                }
                visited.insert(make_pair(i, top));
                scanner2 = similar_coords.first;
                if (similar_coords.second == coord(0, 0, 0)) continue;
                scanner_locs[i] = similar_coords.second;
            }
        }
    }
    int max_dist = 0;
    for (const auto& c1: scanner_locs) {
        for (const auto& c2: scanner_locs) {
            int manhattan_distance = abs(c1.x - c2.x) + abs(c1.y - c2.y) + abs(c1.z - c2.z);
            max_dist = max(max_dist, manhattan_distance);
        }
    }
    cout << "Solution for Part 2: " << max_dist << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    part_1();
    part_2();

    return 0;
}
