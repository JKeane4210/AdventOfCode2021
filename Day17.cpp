//
// Created by Jonny Keane on 12/17/21.
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

int sum_of_steps(int n) {
    return (n * (n + 1)) / 2;
}

bool fits(int x1, int x2, int y1, int y2, int vel_x, int vel_y) {
    int start_vel = vel_y;
    int y_n = 0;
    int x_n = 0;
    while (vel_y >= 0 || y_n >= y1) {
        y_n += vel_y;
        x_n += vel_x;
        if (vel_x > 0) { --vel_x; }
        --vel_y;
        if (x_n >= x1 && x_n <= x2 && y_n >= y1 && y_n <= y2) {
            return true;
        }
    }
    return false;
}

/**
 * I would think for this that you would want to have
 * an x where the drag becomes 0 and drops into the target
 * zone, so you can put as much power on it as possible.
 *
 * Then, I would have to try a series of y values to see if
 * they would work (not sure of this).
 */
void part_1(int x1, int x2, int y1, int y2) {
    vector<int> vels_x;
    int vel_x = 0;
    while (true) {
        int steps = sum_of_steps(vel_x);
        if (steps >= x1 && steps <= x2) {
            vels_x.emplace_back(vel_x);
        } else if (!vels_x.empty()) { break; }
        ++vel_x;
    }
    int max_ = 0;
    for (int vel_y = 0; vel_y < abs(y1) + 10; ++vel_y) {
        for (int poss_vel_x: vels_x) {
            if (fits(x1, x2, y1, y2, poss_vel_x, vel_y)) {
                max_ = max(max_, vel_y);
            }
        }
    }
    cout << "Solution for Part 1: " << sum_of_steps(max_) << endl;
}

void part_2(int x1, int x2, int y1, int y2) {
    int num_fits = 0;
    for (int vel_y = -(abs(y1) + 10); vel_y < abs(y1) + 10; ++vel_y) {
        for (int vel_x = 1; vel_x < x2 + 10; ++vel_x) {
            if (fits(x1, x2, y1, y2, vel_x, vel_y)) {
                ++num_fits;
            }
        }
    }
    cout << "Solution for Part 2: " << num_fits << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

//    part_1(20, 30, -10, -5);
    part_1(139, 187, -148, -89);

//    part_2(20, 30, -10, -5);
    part_2(139, 187, -148, -89);

    return 0;
}