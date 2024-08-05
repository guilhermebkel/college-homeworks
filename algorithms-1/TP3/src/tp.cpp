#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>

const int MAX_N = 105;
const int MAX_K = 15;
const int MAX_M = 1025;

int N, K;
int multiplier[MAX_N], timeLimit[MAX_N];
int trickPoints[MAX_K], trickTime[MAX_K];
long scoreMatrix[MAX_M][MAX_M];
long dp[MAX_N][MAX_M], previousTricks[MAX_N][MAX_M];

void preComputeScoreMatrix() {
    for (int previousTrickIndex = 0; previousTrickIndex < (1 << K); ++previousTrickIndex) {
        for (int currentTrickIndex = 0; currentTrickIndex < (1 << K); ++currentTrickIndex) {
            int score = 0;
            int count = 0;

            for (int trickIndex = 0; trickIndex < K; ++trickIndex) {
                if (currentTrickIndex & (1 << trickIndex)) {
                    if (previousTrickIndex & (1 << trickIndex)) {
                        score += trickPoints[trickIndex] / 2;
                    } else {
                        score += trickPoints[trickIndex];
                    }

                    count++;
                }
            }

            scoreMatrix[previousTrickIndex][currentTrickIndex] = count > 0 ? score * count : score;
        }
    }
}

bool fitsTimeLimit(int tricks, int limit) {
    int totalTime = 0;

    for (int trickIndex = 0; trickIndex < K; ++trickIndex) {
        if (tricks & (1 << trickIndex)) {
            totalTime += trickTime[trickIndex];
        }
    }

    return totalTime <= limit;
}

void calculateMaxPoints() {
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_M; ++j) {
            dp[i][j] = INT_MIN;
        }
    }

    dp[0][0] = 0;

    for (int sectionIndex = 0; sectionIndex < N; ++sectionIndex)  {
        for (int previousTrickIndex = 0; previousTrickIndex < (1 << K); ++previousTrickIndex) {
            if (dp[sectionIndex][previousTrickIndex] == INT_MIN) {
                continue;
            }

            for (int currentTrickIndex = 0; currentTrickIndex < (1 << K); ++currentTrickIndex) {
                if (fitsTimeLimit(currentTrickIndex, timeLimit[sectionIndex])) {
                    long score = scoreMatrix[previousTrickIndex][currentTrickIndex] * multiplier[sectionIndex];
                    long nextScore = dp[sectionIndex][previousTrickIndex] + score;

                    if (nextScore > dp[sectionIndex + 1][currentTrickIndex]) {
                        dp[sectionIndex + 1][currentTrickIndex] = nextScore;
                        previousTricks[sectionIndex + 1][currentTrickIndex] = previousTrickIndex;
                    }
                }
            }
        }
    }
}

int main() {
    std::cin >> N >> K;

    for (int i = 0; i < N; ++i) {
        std::cin >> multiplier[i] >> timeLimit[i];
    }

    for (int i = 0; i < K; ++i) {
        std::cin >> trickPoints[i] >> trickTime[i];
    }

    preComputeScoreMatrix();
    calculateMaxPoints();

    long maxScore = INT_MIN, lastIndex = 0;

    for (int j = 0; j < (1 << K); ++j) {
        if (dp[N][j] > maxScore) {
            maxScore = dp[N][j];
            lastIndex = j;
        }
    }

    std::cout << maxScore << std::endl;
    std::vector<std::vector<int> > sections(N);

    for (int i = N; i > 0; --i) {
        for (int k = 0; k < K; ++k) {
            if (lastIndex & (1 << k)) {
                sections[i-1].push_back(k + 1);
            }
        }

        lastIndex = previousTricks[i][lastIndex];
    }
    
    for (const auto& section : sections) {
        std::cout << section.size();

        for (int trick : section) {
            std::cout << " " << trick;
        }

        std::cout << std::endl;
    }

    return 0;
}