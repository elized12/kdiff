#pragma once

#include <fstream>
#include <memory>
#include <unordered_map>

#include "kdiff/Config.hpp"
#include "kdiff/_detail/IDiffStategy.hpp"

namespace kdiff {
namespace _detail {
namespace algorithm {

class BaseDiff : public IDiffStategy {
   private:
    std::unique_ptr<std::wfstream> _fileStream1;
    std::unique_ptr<std::wfstream> _fileStream2;

   protected:
    kdiff::Config _config;

   public:
    BaseDiff(const kdiff::Config& config, std::unique_ptr<std::wfstream> fileStream1, std::unique_ptr<std::wfstream> fileStream2);
    virtual ~BaseDiff() = default;

   public:
    virtual std::vector<kdiff::Differance> getDifferances() override;

   protected:
    virtual void preprocessingFileStream(const std::unique_ptr<std::wfstream>& fileStream, int streamNumber);
    virtual std::wstring processLine(const std::wstring& line);
    virtual bool checkStopConditionFirstStream(int lineNumber, const std::wstring& line);
    virtual bool checkStopConditionSecondStream(int lineNumber, const std::wstring& line);
};

}  // namespace algorithm
}  // namespace _detail
}  // namespace kdiff