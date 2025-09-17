#pragma once

#include <fstream>
#include <memory>
#include <unordered_map>

#include "kdiff/Config.hpp"
#include "kdiff/algorithm/line/Mayer.hpp"
#include "kdiff/differ/IDiffer.hpp"

namespace kdiff {
namespace differ {
namespace line {

class LineDifferDecorator;
class RangeDecorator;
class CaseSensitiveDecorator;
class IgnoringSymbolDecorator;

}  // namespace line
}  // namespace differ
}  // namespace kdiff

namespace kdiff {
namespace differ {

class LineDiffer : public IDiffer {
   public:
    friend class line::LineDifferDecorator;
    friend class line::RangeDecorator;
    friend class line::CaseSensitiveDecorator;
    friend class line::IgnoringSymbolDecorator;

   protected:
    std::unique_ptr<std::wfstream> _fileStream1;
    std::unique_ptr<std::wfstream> _fileStream2;
    kdiff::Config _config;

   public:
    LineDiffer(
        const kdiff::Config& config,
        std::unique_ptr<std::wfstream> fileStream1,
        std::unique_ptr<std::wfstream> fileStream2);
    virtual ~LineDiffer() = default;

   public:
    std::vector<kdiff::Difference> getDifferences() override;

   protected:
    virtual void preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual void preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual void processLine(std::wstring& line);
    virtual bool checkStopConditionFirstStream(int lineNumber, const std::wstring& line);
    virtual bool checkStopConditionSecondStream(int lineNumber, const std::wstring& line);
    std::unique_ptr<kdiff::algorithm::IDiffStategy> createDiffStrategy() const override;
};

}  // namespace differ
}  // namespace kdiff