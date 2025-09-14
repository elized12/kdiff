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

}  // namespace line
}  // namespace differ
}  // namespace kdiff