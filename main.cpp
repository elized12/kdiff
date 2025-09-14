#include <algorithm>
#include <codecvt>
#include <exception>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <unordered_map>
#include <vector>

#include "kdiff/Parser.hpp"
#include "kdiff/ParserException.hpp"
#include "kdiff/differ/LineDiffer.hpp"
#include "kdiff/ui/DiffRender.hpp"

int main(int argc, char* argv[]) {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    std::vector<std::wstring> args;
    args.reserve(argc);

    for (size_t i = 0; i < argc; i++) {
        try {
            args.push_back(converter.from_bytes(argv[i]));
        } catch (...) {
            args.emplace_back(L"");
        }
    }

    try {
        kdiff::Parser parser;
        kdiff::Config config = parser.parseArgs(args);

        std::filesystem::path filePath1 = config.getFilePath1();
        std::filesystem::path filePath2 = config.getFilePath2();

        std::unique_ptr<std::wfstream> file1 = std::make_unique<std::wfstream>(filePath1);
        std::unique_ptr<std::wfstream> file2 = std::make_unique<std::wfstream>(filePath2);

        std::unique_ptr<kdiff::differ::LineDiffer> lineDiffer = std::make_unique<kdiff::differ::LineDiffer>(config, std::move(file1), std::move(file2));

        std::vector<kdiff::Difference> differences = lineDiffer->getDifferences();

        kdiff::ui::DiffRender render;
        render.render(differences);

    } catch (const kdiff::ParserException& ex) {
        std::cout << "\033[31mError : " << ex.what() << std::endl;
        std::cout << std::endl
                  << std::endl;
        std::wcerr << L"\033[39mUsage: " << L"kdiff" << L" [OPTIONS] <file1> <file2>" << std::endl;
        std::wcerr << L"Compare two files and show differences" << std::endl;
        std::wcerr << std::endl;
        std::wcerr << L"Options:" << std::endl;
        std::wcerr << L"  --case-sensitive          Enable case-sensitive comparison" << std::endl;
        std::wcerr << L"  --ranges=START1:END1,START2:END2" << std::endl;
        std::wcerr << L"                            Compare specific line ranges" << std::endl;
        std::wcerr << L"  --count-diff=N            Return only first N differences" << std::endl;
        std::wcerr << L"  --ignore-symbol=CHARS     Ignore specified symbols during comparison" << std::endl;
        std::wcerr << std::endl;
        std::wcerr << L"Examples:" << std::endl;
        std::wcerr << L"  " << L"kdiff" << L" file1.txt file2.txt" << std::endl;
        std::wcerr << L"  " << L"kdiff" << L" --case-sensitive file1.txt file2.txt" << std::endl;
        std::wcerr << L"  " << L"kdiff" << L" --ranges=1:10,1:10 file1.txt file2.txt" << std::endl;
        std::wcerr << L"  " << L"kdiff" << L" --count-diff=5 file1.txt file2.txt" << std::endl;
    } catch (const kdiff::ui::RenderException& ex) {
        std::wcerr << L"Error render differences";
    } catch (const std::exception& ex) {
        std::wcerr << L"Error: " << ex.what() << std::endl;
    }

    return 0;
}