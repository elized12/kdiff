#include "kdiff/differ/LineDiffer.hpp"

#include "kdiff/differ/line/CaseSensitiveDecorator.hpp"
#include "kdiff/differ/line/IgnoringSymbolDecorator.hpp"
#include "kdiff/differ/line/LineDifferDecorator.hpp"
#include "kdiff/differ/line/RangeDecorator.hpp"

namespace kdiff {
namespace differ {

LineDiffer::LineDiffer(
    const kdiff::Config& config,
    std::unique_ptr<std::wfstream> fileStream1,
    std::unique_ptr<std::wfstream> fileStream2)
    : _fileStream1(std::move(fileStream1)),
      _fileStream2(std::move(fileStream2)),
      _config(config) {
}

std::vector<kdiff::Difference> LineDiffer::getDifferences() {
    this->preprocessingFirstFileStream(this->_fileStream1);
    this->preprocessingSecondFileStream(this->_fileStream2);

    std::vector<std::wstring> linesFile1;
    std::vector<std::wstring> linesFile2;

    std::wstring line1;
    while (std::getline(*this->_fileStream1, line1)) {
        if (this->checkStopConditionFirstStream(linesFile1.size() + 1, line1)) {
            break;
        }

        this->processLine(line1);
        linesFile1.emplace_back(std::move(line1));
    }

    this->_fileStream1->close();

    std::wstring line2;
    while (std::getline(*this->_fileStream2, line2)) {
        if (this->checkStopConditionSecondStream(linesFile2.size() + 1, line2)) {
            break;
        }

        this->processLine(line2);
        linesFile2.emplace_back(std::move(line2));
    }

    this->_fileStream2->close();

    return this->createDiffStrategy()->getDifferences(this->_config, linesFile1, linesFile2);
}

void LineDiffer::preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
}

void LineDiffer::preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
}

bool LineDiffer::checkStopConditionFirstStream(int lineNumber, const std::wstring& line) {
    return false;
}

bool LineDiffer::checkStopConditionSecondStream(int lineNumber, const std::wstring& line) {
    return false;
}

void LineDiffer::processLine(std::wstring& line) {
}

std::unique_ptr<kdiff::algorithm::IDiffStategy> LineDiffer::createDiffStrategy() const {
    return std::make_unique<kdiff::algorithm::line::Mayer>();
}

}  // namespace differ
}  // namespace kdiff