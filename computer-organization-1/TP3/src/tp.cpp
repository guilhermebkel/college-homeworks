#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <unordered_map>

struct CacheData {
    bool valid;
    uint32_t tag;
};

struct CacheLogInfo {
    uint32_t numSets;
    uint32_t linesPerSet;
    uint32_t hits;
    uint32_t misses;
};

class Cache {
public:
    Cache(uint32_t cacheSize, uint32_t lineSize, uint32_t numSets) {
        this->cacheSize = cacheSize;
        this->lineSize = lineSize;
        this->numSets = numSets;
        this->hits = 0;
        this->misses = 0;

        this->numLines = this->cacheSize / this->lineSize;
        this->linesPerSet = this->numLines / this->numSets;
        this->store.resize(this->numSets, std::vector<CacheData>(this->linesPerSet));
    }

    void access (uint32_t address) {
        uint32_t blockAddress = address / this->lineSize;
        uint32_t setIndex = blockAddress % this->numSets;
        uint32_t tag = blockAddress / this->numSets;

        bool hit = false;

        for (auto& line : this->store[setIndex]) {
            if (line.valid && line.tag == tag) {
                hit = true;
                break;
            }
        }

        if (hit) {
            this->hits++;
        } else {
            this->misses++;
            uint32_t lineIndex = this->setNextLine[setIndex] % this->linesPerSet;
            this->store[setIndex][lineIndex] = { true, tag };
            this->setNextLine[setIndex]++;
        }
    }

    std::string getBlockIdentifierByTag(uint32_t tag) {
        uint32_t rawIdentifier = (tag * this->lineSize) >> 10;

        std::stringstream identifier;
        identifier << std::hex << std::uppercase << rawIdentifier;

        return identifier.str();
    }

    CacheData getCacheData (int setIndex, int setLineIndex) {
        return this->store[setIndex][setLineIndex];
    }

    CacheLogInfo getCacheLogInfo () {
        return {
            .numSets = this->numSets,
            .linesPerSet = this->linesPerSet,
            .hits = this->hits,
            .misses = this->misses,
        };
    }

private:
    uint32_t cacheSize;
    uint32_t lineSize;
    uint32_t numSets;
    uint32_t numLines;
    uint32_t linesPerSet;
    uint32_t hits;
    uint32_t misses;
    std::vector<std::vector<CacheData>> store;
    std::unordered_map<uint32_t, uint32_t> setNextLine;
};

void logCacheState(Cache cache, std::ofstream &logFile) {
    logFile << "================" << std::endl;
    logFile << "IDX V ** ADDR **" << std::endl;

    CacheLogInfo cacheLogInfo = cache.getCacheLogInfo();

    for (uint32_t setIndex = 0; setIndex < cacheLogInfo.numSets; setIndex++) {
        for (uint32_t setLineIndex = 0; setLineIndex < cacheLogInfo.linesPerSet; setLineIndex++) {
            uint32_t lineIndex = setIndex * cacheLogInfo.linesPerSet + setLineIndex;
            CacheData cacheData = cache.getCacheData(setIndex, setLineIndex);

            logFile << std::setw(3) << std::setfill('0') << lineIndex << " " << cacheData.valid << " ";

            if (cacheData.valid) {
                logFile << "0x" << std::setw(8) << std::setfill('0') << std::hex << cache.getBlockIdentifierByTag(cacheData.tag) << std::dec;
            }

            logFile << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    uint32_t cacheSize = std::stoi(argv[1]);
    uint32_t lineSize = std::stoi(argv[2]);
    uint32_t associativity = std::stoi(argv[3]);

    std::string inputFilePath = argv[4];
    std::string outputFilePath = "./output.txt";

    uint32_t numSets = cacheSize / (lineSize * associativity);

    Cache cache(cacheSize, lineSize, numSets);

    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);

    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    uint32_t address;

    while (inputFile >> std::hex >> address) {
        cache.access(address);
        logCacheState(cache, outputFile);
    }

    CacheLogInfo cacheLogInfo = cache.getCacheLogInfo();

    outputFile << "================" << std::endl;
    outputFile << "#hits: " << cacheLogInfo.hits << std::endl;
    outputFile << "#miss: " << cacheLogInfo.misses << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
