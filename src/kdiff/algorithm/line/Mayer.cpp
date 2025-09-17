#include "kdiff/algorithm/line/Mayer.hpp"

namespace kdiff {
namespace algorithm {
namespace line {

std::vector<kdiff::Difference> Mayer::getDifferences(
    const kdiff::Config& config,
    std::vector<std::wstring>& fileLines1,
    std::vector<std::wstring>& fileLines2) const {
    std::vector<size_t> lineHashes1(fileLines1.size());
    for (size_t i = 0; i < fileLines1.size(); i++) {
        lineHashes1[i] = std::hash<std::wstring>{}(fileLines1[i]);
    }

    std::vector<size_t> lineHashes2(fileLines2.size());
    for (size_t i = 0; i < fileLines2.size(); i++) {
        lineHashes2[i] = std::hash<std::wstring>{}(fileLines2[i]);
    }

    const long long maxSize = fileLines1.size() + fileLines2.size();
    std::vector<std::unordered_map<long long, long long>> historyDiagonalPosX(maxSize + 1);

    for (long long countEdits = 0; countEdits <= maxSize; countEdits++) {
        bool foundSolution = false;

        for (long long diagonal = -countEdits; diagonal <= countEdits; diagonal += 2) {
            long long x = 0;

            bool hasMinus1 = countEdits != 0 ? historyDiagonalPosX[countEdits - 1].count(diagonal - 1) : false;
            bool hasPlus1 = countEdits != 0 ? historyDiagonalPosX[countEdits - 1].count(diagonal + 1) : false;

            if (hasMinus1 && hasPlus1) {
                x = (historyDiagonalPosX[countEdits - 1][diagonal - 1] >=
                     historyDiagonalPosX[countEdits - 1][diagonal + 1])
                        ? historyDiagonalPosX[countEdits - 1][diagonal - 1] + 1
                        : historyDiagonalPosX[countEdits - 1][diagonal + 1];
            } else if (!hasMinus1 && !hasPlus1) {
                x = 0;
            } else if (hasMinus1) {
                x = historyDiagonalPosX[countEdits - 1][diagonal - 1] + 1;
            } else if (hasPlus1) {
                x = historyDiagonalPosX[countEdits - 1][diagonal + 1];
            }

            long long y = x - diagonal;

            while (x < static_cast<long long>(fileLines1.size()) &&
                   y < static_cast<long long>(fileLines2.size()) &&
                   this->isQualLine(fileLines1[x], lineHashes1[x], fileLines2[y], lineHashes2[y])) {
                x++;
                y++;
            }

            historyDiagonalPosX[countEdits][diagonal] = x;

            if (x == static_cast<long long>(fileLines1.size()) &&
                y == static_cast<long long>(fileLines2.size())) {
                foundSolution = true;
                break;
            }
        }

        if (foundSolution) {
            return this->backtrack(
                historyDiagonalPosX,
                fileLines1,
                fileLines2,
                countEdits,
                lineHashes1,
                lineHashes2);
        }
    }

    return {};
}

bool Mayer::isQualLine(const std::wstring& line1, size_t hash1, const std::wstring& line2, size_t hash2) const {
    if (hash1 != hash2) {
        return false;
    }

    return line1 == line2;
}

std::vector<kdiff::Difference> Mayer::backtrack(
    const std::vector<std::unordered_map<long long, long long>>& mapEdits,
    std::vector<std::wstring>& fileLines1,
    std::vector<std::wstring>& fileLines2,
    long long countEdits,
    const std::vector<size_t>& hashes1,
    const std::vector<size_t>& hashes2) const {
    std::vector<kdiff::Difference> results;
    long long x = fileLines1.size();
    long long y = fileLines2.size();

    for (long long d = countEdits; d > 0; d--) {
        long long k = x - y;

        while (x > 0 && y > 0 &&
               isQualLine(fileLines1[x - 1], hashes1[x - 1], fileLines2[y - 1], hashes2[y - 1])) {
            results.emplace_back(std::move(fileLines1[x - 1]), kdiff::Difference::DiffType::UNCHANGED);
            x--;
            y--;
        }

        if (d > 0 && mapEdits[d - 1].count(k + 1) && mapEdits[d - 1].at(k + 1) == x) {
            results.emplace_back(std::move(fileLines2[y - 1]), kdiff::Difference::DiffType::ADDED);
            y--;
            continue;
        }

        if (d > 0 && mapEdits[d - 1].count(k - 1) && mapEdits[d - 1].at(k - 1) == x - 1) {
            results.emplace_back(std::move(fileLines1[x - 1]), kdiff::Difference::DiffType::DELETED);
            x--;
            continue;
        }
    }

    while (x > 0 && y > 0 &&
           isQualLine(fileLines1[x - 1], hashes1[x - 1], fileLines2[y - 1], hashes2[y - 1])) {
        results.emplace_back(std::move(fileLines1[x - 1]), kdiff::Difference::DiffType::UNCHANGED);
        x--;
        y--;
    }

    std::reverse(results.begin(), results.end());
    return results;
}

}  // namespace line
}  // namespace algorithm
}  // namespace kdiff