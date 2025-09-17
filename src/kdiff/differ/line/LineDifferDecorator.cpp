#include "kdiff/differ/line/LineDifferDecorator.hpp"

namespace kdiff {
namespace differ {
namespace line {

LineDifferDecorator::LineDifferDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ)
    : LineDiffer(differ->_config,
                 std::move(differ->_fileStream1),
                 std::move(differ->_fileStream2)),
      _parent(std::move(differ)) {
}

void LineDifferDecorator::preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
    this->_parent->preprocessingFirstFileStream(fileStream);
}

void LineDifferDecorator::preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream) {
    this->_parent->preprocessingSecondFileStream(fileStream);
}

void LineDifferDecorator::processLine(std::wstring& line) {
    this->_parent->processLine(line);
}

bool LineDifferDecorator::checkStopConditionFirstStream(int lineNumber, const std::wstring& line) {
    return this->_parent->checkStopConditionFirstStream(lineNumber, line);
}

bool LineDifferDecorator::checkStopConditionSecondStream(int lineNumber, const std::wstring& line) {
    return this->_parent->checkStopConditionSecondStream(lineNumber, line);
}

}  // namespace line
}  // namespace differ
}  // namespace kdiff