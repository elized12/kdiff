#include "kdiff/_detail/algorithm/BaseDiff.hpp"

namespace kdiff {
namespace _detail {
namespace algorithm {

BaseDiff::BaseDiff(
    const kdiff::Config& config,
    std::unique_ptr<std::wfstream> fileStream1,
    std::unique_ptr<std::wfstream> fileStream2)
    : _fileStream1(std::move(fileStream1)),
      _fileStream2(std::move(fileStream2)),
      _config(config) {
}

std::vector<kdiff::Differance> BaseDiff::getDifferances() {
    this->preprocessingFileStream(this->_fileStream1, 1);
    this->preprocessingFileStream(this->_fileStream2, 2);

    std::vector<std::pair<size_t, std::wstring>> linesFile1;
    std::vector<std::pair<size_t, std::wstring>> linesFile2;

    std::wstring line1;
    while (std::getline(*this->_fileStream1, line1)) {
        if (this->checkStopConditionFirstStream(linesFile1.size() + 1, line1)) {
            break;
        }

        line1 = this->processLine(line1);
        linesFile1.emplace_back(std::hash<std::wstring>{}(line1), std::move(line1));
    }

    std::wstring line2;
    while (std::getline(*this->_fileStream2, line2)) {
        if (this->checkStopConditionSecondStream(linesFile2.size() + 1, line2)) {
            break;
        }

        line2 = this->processLine(line2);
        linesFile2.emplace_back(std::hash<std::wstring>{}(line2), std::move(line2));
    }
}

void BaseDiff::preprocessingFileStream(const std::unique_ptr<std::wfstream>& fileStream, int streamNumber) {
}

bool BaseDiff::checkStopConditionFirstStream(int lineNumber, const std::wstring& line) {
    return false;
}

bool BaseDiff::checkStopConditionSecondStream(int lineNumber, const std::wstring& line) {
    return false;
}

std::wstring BaseDiff::processLine(const std::wstring& line) {
    return line;
}

}  // namespace algorithm
}  // namespace _detail
}  // namespace kdiff