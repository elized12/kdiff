#include "kdiff/differ/line/RangeDecorator.hpp"

namespace kdiff {
namespace differ {
namespace line {

RangeDecorator::RangeDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ) : LineDifferDecorator(std::move(differ)) {
}

void RangeDecorator::preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
    std::vector<std::pair<size_t, size_t>> ranges = this->_config.getRanges();
    if (ranges.size() == 0 || ranges[0].first == 0) {
        return;
    }

    std::wstring temp;
    for (size_t i = 0; i < ranges[0].first - 1; i++) {
        if (!(bool)std::getline(*fileStream, temp)) {
            throw kdiff::differ::line::RangeException(
                "First file : start line " + std::to_string(ranges[0].first) +
                " is out of file bounds. File has fewer lines.");
        }
    }

    this->_parent->preprocessingFirstFileStream(fileStream);
}

void RangeDecorator::preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
    std::vector<std::pair<size_t, size_t>> ranges = this->_config.getRanges();
    if (ranges.size() != 2 || ranges[1].first == 0) {
        return;
    }

    std::wstring temp;
    for (size_t i = 0; i < ranges[1].first - 1; i++) {
        if (!(bool)std::getline(*fileStream, temp)) {
            throw kdiff::differ::line::RangeException(
                "Second file : start line " + std::to_string(ranges[1].first) +
                " is out of file bounds. File has fewer lines.");
        }
    }

    this->_parent->preprocessingSecondFileStream(fileStream);
}

bool RangeDecorator::checkStopConditionFirstStream(int lineNumber, const std::wstring& line) {
    std::vector<std::pair<size_t, size_t>> ranges = this->_config.getRanges();
    if (ranges.size() == 0 || ranges[0].second == 0) {
        return this->_parent->checkStopConditionFirstStream(lineNumber, line);
    }

    const int countReadLine = (ranges[0].second - ranges[0].first) + 1;
    if (countReadLine < lineNumber) {
        return true;
    } else {
        return this->_parent->checkStopConditionFirstStream(lineNumber, line);
    }
}

bool RangeDecorator::checkStopConditionSecondStream(int lineNumber, const std::wstring& line) {
    std::vector<std::pair<size_t, size_t>> ranges = this->_config.getRanges();
    if (ranges.size() != 2 || ranges[1].second == 0) {
        return this->_parent->checkStopConditionSecondStream(lineNumber, line);
    }

    const int countReadLine = (ranges[1].second - ranges[1].first) + 1;
    if (countReadLine < lineNumber) {
        return true;
    } else {
        return this->_parent->checkStopConditionSecondStream(lineNumber, line);
    }
}

}  // namespace line
}  // namespace differ
}  // namespace kdiff