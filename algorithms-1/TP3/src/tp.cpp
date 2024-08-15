#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const int MAX_SECTIONS = 105;
const int MAX_TRICKS = 15;
const int MAX_COMBINATIONS = 1025;

int numSections, numTricks;
int sectionMultiplier[MAX_SECTIONS], sectionTimeLimit[MAX_SECTIONS];
int trickPoints[MAX_TRICKS], trickDuration[MAX_TRICKS];
long precomputedTrickScores[MAX_COMBINATIONS][MAX_COMBINATIONS];
long dp[MAX_SECTIONS][MAX_COMBINATIONS], previousTrickCombination[MAX_SECTIONS][MAX_COMBINATIONS];

void precomputeAllPossibleTrickScores() {
    for (int previousCombination = 0; previousCombination < (1 << numTricks); ++previousCombination) {
        for (int currentCombination = 0; currentCombination < (1 << numTricks); ++currentCombination) {
            int score = 0;
            int numSelectedTricks = 0;

            for (int trickIndex = 0; trickIndex < numTricks; ++trickIndex) {
                bool isTrickInCurrentCombination = currentCombination & (1 << trickIndex);

                if (isTrickInCurrentCombination) {
                    bool isRepeatedTrick = previousCombination & (1 << trickIndex);

                    if (isRepeatedTrick) {
                        score += trickPoints[trickIndex] / 2;
                    } else {
                        score += trickPoints[trickIndex];
                    }

                    numSelectedTricks++;
                }
            }

            bool isThereAnySelectedTrick = numSelectedTricks > 0;

            if (isThereAnySelectedTrick) {
                precomputedTrickScores[previousCombination][currentCombination] = score * numSelectedTricks;
            } else {
                precomputedTrickScores[previousCombination][currentCombination] = score;
            }
        }
    }
}

bool trickCombinationCanBeExecutedWithinTimeLimit(int trickCombination, int timeLimit) {
    int totalTime = 0;

    for (int trickIndex = 0; trickIndex < numTricks; ++trickIndex) {
        bool isTrickPartOfCombination = trickCombination & (1 << trickIndex);

        if (isTrickPartOfCombination) {
            totalTime += trickDuration[trickIndex];
        }
    }

    return totalTime <= timeLimit;
}

void initializeDynamicProgrammingMatrix() {
    for (int i = 0; i < MAX_SECTIONS; ++i) {
        for (int j = 0; j < MAX_COMBINATIONS; ++j) {
            dp[i][j] = INT_MIN;
        }
    }

    dp[0][0] = 0;
}

void calculateMaxScoreWithDynamicProgramming() {
    for (int sectionIndex = 0; sectionIndex < numSections; ++sectionIndex)  {
        for (int previousCombination = 0; previousCombination < (1 << numTricks); ++previousCombination) {
            bool isTrickCombinationUnreachable = dp[sectionIndex][previousCombination] == INT_MIN;

            if (isTrickCombinationUnreachable) {
                continue;
            }

            for (int currentCombination = 0; currentCombination < (1 << numTricks); ++currentCombination) {
                if (trickCombinationCanBeExecutedWithinTimeLimit(currentCombination, sectionTimeLimit[sectionIndex])) {
                    long score = precomputedTrickScores[previousCombination][currentCombination] * sectionMultiplier[sectionIndex];
                    long newScore = dp[sectionIndex][previousCombination] + score;

                    bool isNewScoreBetter = newScore > dp[sectionIndex + 1][currentCombination];

                    if (isNewScoreBetter) {
                        dp[sectionIndex + 1][currentCombination] = newScore;
                        previousTrickCombination[sectionIndex + 1][currentCombination] = previousCombination;
                    }
                }
            }
        }
    }
}

void extractBestTrickCombination() {
    long maxScore = INT_MIN;
    int bestTrickCombination = 0;

    for (int combination = 0; combination < (1 << numTricks); ++combination) {
        long currentScore = dp[numSections][combination];

        if (currentScore > maxScore) {
            maxScore = currentScore;
            bestTrickCombination = combination;
        }
    }

    std::cout << maxScore << std::endl;

    std::vector<std::vector<int>> sections(numSections);

    for (int i = numSections; i > 0; --i) {
        for (int trickIndex = 0; trickIndex < numTricks; ++trickIndex) {
            bool isTrickInBestCombination = bestTrickCombination & (1 << trickIndex);

            if (isTrickInBestCombination) {
                sections[i-1].push_back(trickIndex + 1);
            }
        }

        bestTrickCombination = previousTrickCombination[i][bestTrickCombination];
    }
    
    for (const auto& section : sections) {
        std::cout << section.size();

        for (int trick : section) {
            std::cout << " " << trick;
        }

        std::cout << std::endl;
    }
}

int main() {
    std::cin >> numSections >> numTricks;

    for (int i = 0; i < numSections; ++i) {
        std::cin >> sectionMultiplier[i] >> sectionTimeLimit[i];
    }

    for (int i = 0; i < numTricks; ++i) {
        std::cin >> trickPoints[i] >> trickDuration[i];
    }

    precomputeAllPossibleTrickScores();
    initializeDynamicProgrammingMatrix();
    calculateMaxScoreWithDynamicProgramming();
    extractBestTrickCombination();

    return 0;
}
