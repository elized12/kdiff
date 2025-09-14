#pragma once

#include <fstream>
#include <memory>
#include <unordered_map>

#include "kdiff/Config.hpp"
#include "kdiff/algorithm/line/Mayer.hpp"
#include "kdiff/differ/IDiffer.hpp"
#include "kdiff/differ/line/LineDifferDecorator.hpp"

namespace kdiff {
namespace differ {

class LineDiffer : public IDiffer {
   public:
    friend class kdiff::differ::line::LineDifferDecorator;

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
    virtual void preprocessingFileStream(const std::unique_ptr<std::wfstream>& fileStream, int streamNumber);
    virtual std::wstring processLine(const std::wstring& line);
    virtual bool checkStopConditionFirstStream(int lineNumber, const std::wstring& line);
    virtual bool checkStopConditionSecondStream(int lineNumber, const std::wstring& line);
    std::unique_ptr<kdiff::algorithm::IDiffStategy> createDiffStrategy() const override;
};

}  // namespace differ
}  // namespace kdiff