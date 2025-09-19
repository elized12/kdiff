#include <gtest/gtest.h>

#include <fstream>

#include "kdiff/Parser.hpp"

class ParserTest : public ::testing::Test {
   protected:
    std::filesystem::path file1 = "file1.txt";
    std::filesystem::path file2 = "file2.txt";

    void SetUp() override {
        std::ofstream(file1).close();
        std::ofstream(file2).close();
    }

    void TearDown() override {
        std::filesystem::remove(file1);
        std::filesystem::remove(file2);
    }
};

TEST_F(ParserTest, parserArgs_parseCaseSensitiveTrue) {
    kdiff::Parser parser;
    kdiff::Config config = parser.parseArgs({L"program", L"--case-sensitive", L"file1.txt", L"file2.txt"});

    ASSERT_TRUE(config.getCaseSensitive());
}

TEST_F(ParserTest, parserArgs_parseCaseSensitiveException) {
    kdiff::Parser parser;

    EXPECT_THROW(parser.parseArgs({L"program", L"--case-sens", L"file1.txt", L"file2.txt"});, kdiff::ParserException);
}

TEST_F(ParserTest, parserArgs_parseRangesTwoRanges) {
    kdiff::Parser parser;
    kdiff::Config config = parser.parseArgs({L"program", L"file1.txt", L"file2.txt", L"--ranges1:3,4:5"});

    ASSERT_EQ(2, config.getRanges().size());

    ASSERT_EQ(config.getRanges()[0].first, 1);
    ASSERT_EQ(config.getRanges()[0].second, 3);

    ASSERT_EQ(config.getRanges()[1].first, 4);
    ASSERT_EQ(config.getRanges()[1].second, 5);
}

TEST_F(ParserTest, parserArgs_parseRangesOneRange) {
    kdiff::Parser parser;
    kdiff::Config config = parser.parseArgs({L"program", L"--ranges1:3", L"file1.txt", L"file2.txt"});

    ASSERT_EQ(1, config.getRanges().size());

    ASSERT_EQ(config.getRanges()[0].first, 1);
    ASSERT_EQ(config.getRanges()[0].second, 3);
}

TEST_F(ParserTest, parserArgs_parseRangesException) {
    kdiff::Parser parser;
    EXPECT_THROW(kdiff::Config config = parser.parseArgs({L"program", L"--ranges1:", L"file1.txt", L"file2.txt"});, kdiff::ParserException);
}

TEST_F(ParserTest, parserArgs_parseCountDiff) {
    kdiff::Parser parser;
    kdiff::Config config = parser.parseArgs({L"program", L"--count-diff=5", L"file1.txt", L"file2.txt"});

    ASSERT_EQ(5, config.getReturnCountDiff());
}

TEST_F(ParserTest, parserArgs_parseCountDiffException) {
    kdiff::Parser parser;
    EXPECT_THROW(kdiff::Config config = parser.parseArgs({L"program", L"--count-diff3", L"file1.txt", L"file2.txt"});, kdiff::ParserException);
}

TEST_F(ParserTest, parserArgs_parseIgnoringSymbols) {
    kdiff::Parser parser;
    kdiff::Config config = parser.parseArgs({L"program", L"--ignore-symbol=1234", L"file1.txt", L"file2.txt"});

    ASSERT_EQ(4, config.getIgnoringSymbols().size());

    ASSERT_EQ(L'1', config.getIgnoringSymbols()[0]);
    ASSERT_EQ(L'2', config.getIgnoringSymbols()[1]);
    ASSERT_EQ(L'3', config.getIgnoringSymbols()[2]);
    ASSERT_EQ(L'4', config.getIgnoringSymbols()[3]);
}

TEST_F(ParserTest, parserArgs_parseIgnoringSymbolsException) {
    kdiff::Parser parser;
    EXPECT_THROW(kdiff::Config config = parser.parseArgs({L"program", L"--ignore-symbol1234", L"file1.txt", L"file2.txt"});, kdiff::ParserException);
}
