#include <iostream>
#include <vector>
#include <array>
#include <limits>

using namespace std;

struct Trick {
    int points;
    int time;
};

struct Section {
    int multiplier;
    int time_limit;
};

vector<Section> sections;
vector<Trick> tricks;

vector<vector<int> > precompute_score_matrix(int k) {
    vector<vector<int> > score_matrix(1 << k, vector<int>(1 << k));
    for (int prev = 0; prev < (1 << k); ++prev) {
        for (int curr = 0; curr < (1 << k); ++curr) {
            int score = 0, count = 0;
            for (int i = 0; i < k; ++i) {
                if (curr & (1 << i)) {
                    score += (prev & (1 << i)) ? tricks[i].points / 2 : tricks[i].points;
                    count++;
                }
            }
            score_matrix[prev][curr] = count > 0 ? score * count : score;
        }
    }
    return score_matrix;
}

int get_max_points(int section, int prev_trick_set, int n, int k, const vector<vector<int> >& score_matrix, 
                   vector<vector<int> >& dp, vector<vector<bool> >& computed, 
                   vector<vector<int> >& next_tricks) {
    if (section == n) return 0;

    if (computed[section][prev_trick_set]) return dp[section][prev_trick_set];

    int max_score = numeric_limits<int>::min();
    for (int curr_trick_set = 0; curr_trick_set < (1 << k); ++curr_trick_set) {
        int total_time = 0;
        for (int i = 0; i < k; ++i) {
            if (curr_trick_set & (1 << i)) {
                total_time += tricks[i].time;
            }
        }

        if (total_time <= sections[section].time_limit) {
            int score = score_matrix[prev_trick_set][curr_trick_set] * sections[section].multiplier;
            int next_score = score + get_max_points(section + 1, curr_trick_set, n, k, score_matrix, dp, computed, next_tricks);
            if (next_score > max_score) {
                max_score = next_score;
                next_tricks[section][prev_trick_set] = curr_trick_set;
            }
        }
    }

    computed[section][prev_trick_set] = true;
    return dp[section][prev_trick_set] = max_score;
}

void print_tricks(int n, int k, const vector<vector<int> >& next_tricks) {
    int curr_trick_set = 0;
    for (int i = 0; i < n; ++i) {
        int next_trick_set = next_tricks[i][curr_trick_set];
        vector<int> tricks_list;
        for (int j = 0; j < k; ++j) {
            if (next_trick_set & (1 << j)) tricks_list.push_back(j + 1);
        }

        cout << tricks_list.size();
        for (int trick : tricks_list) cout << " " << trick;
        cout << endl;

        curr_trick_set = next_trick_set;
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    sections.resize(n);
    tricks.resize(k);

    for (int i = 0; i < n; ++i) {
        cin >> sections[i].multiplier >> sections[i].time_limit;
    }
    for (int i = 0; i < k; ++i) {
        cin >> tricks[i].points >> tricks[i].time;
    }

    auto score_matrix = precompute_score_matrix(k);
    vector<vector<int> > dp(n, vector<int>(1 << k, 0));
    vector<vector<bool> > computed(n, vector<bool>(1 << k, false));
    vector<vector<int> > next_tricks(n, vector<int>(1 << k, 0));

    int max_score = get_max_points(0, 0, n, k, score_matrix, dp, computed, next_tricks);
    cout << max_score << endl;

    print_tricks(n, k, next_tricks);

    return 0;
}
