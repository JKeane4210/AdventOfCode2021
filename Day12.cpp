//
// Created by Jonny Keane on 12/11/21.
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

// loops
#define WHILE(n) while(n--)
#define FOR(a) for(ll i=0;i<a;i++)
#define FIND(a, e) find(a.begin(), a.end(), e)
#define minimum(a) *min_element(a.begin(), a.end())
#define maximum(a) *max_element(a.begin(), a.end())

#define nl '\n'

// use M_PI for PI (imported from cmath within stdc++.h)

using namespace std;

bool is_big_cave(const string & node) {
    for (char c: node) {
        if (c < 65 || c > 90) {
            return false;
        }
    }
    return true;
}

bool is_small_cave(const string & node) {
    return !is_big_cave(node) && node != "start" && node != "end";
}

int paths(const string & node,
          const vector<string> & path,
          const set<string> &visited,
          const map<string, vector<string>> & graph) {
    set<string> new_visited(visited);
    vector<string> new_path(path);
    new_path.emplace_back(node);
    if (!is_big_cave(node)) {
        new_visited.insert(node);
    }
    if (node == "end") {
        return 1;
    }
    int total = 0;
    for (const string& adj: graph.at(node)) {
        if (new_visited.find(adj) == new_visited.end()) {
            total += paths(adj, new_path, new_visited, graph);
        }
    }
    return total;
}

bool has_double_smalls(const multiset<string> & visited) {
    for (const string& s: visited) {
        if (is_small_cave(s) && visited.count(s) == 2) {
            return true;
        }
    }
    return false;
}

int paths2(const string & node,
          const vector<string> & path,
          const multiset<string> &visited,
          const map<string, vector<string>> & graph) {
    multiset<string> new_visited(visited);
    vector<string> new_path(path);
    new_path.emplace_back(node);
    if (!is_big_cave(node)) {
        new_visited.insert(node);
    }
    if (node == "end") {
        return 1;
    }
    int total = 0;
    for (const string& adj: graph.at(node)) {
        if (new_visited.count(adj) == 0 ||
            (!has_double_smalls(new_visited) && is_small_cave(adj) && new_visited.count(adj) == 1)) {
            total += paths2(adj, new_path, new_visited, graph);
        }
    }
    return total;
}

void part_1() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day12.txt");
    map<string, vector<string>> graph;
    string line;
    while (getline(cin, line)) {
        string a = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);
        string b = line;
        if (graph.find(a) == graph.end()) {
            graph[a] = vector<string>();
        }
        if (graph.find(b) == graph.end()) {
            graph[b] = vector<string>();
        }
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    int g_paths = paths("start", vector<string>(), set<string>(), graph);
    cout << "Solution for Part 1: " << g_paths << endl;
}

void part_2() {
    ifstream cin("/Users/jkeane/CLionProjects/AdventOfCode2021/Input/day12.txt");
    map<string, vector<string>> graph;
    string line;
    while (getline(cin, line)) {
        string a = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);
        string b = line;
        if (graph.find(a) == graph.end()) {
            graph[a] = vector<string>();
        }
        if (graph.find(b) == graph.end()) {
            graph[b] = vector<string>();
        }
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    int g_paths = paths2("start", vector<string>(), multiset<string>(), graph);
    cout << "Solution for Part 2: " << g_paths << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    part_1();
    part_2();

    return 0;
}