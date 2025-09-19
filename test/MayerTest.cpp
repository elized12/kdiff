#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "kdiff/algorithm/line/Mayer.hpp"

class MayerTest : public ::testing::Test {
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

TEST(MayerTest, getDifferences) {
    kdiff::algorithm::line::Mayer mayer;
    kdiff::Config config(L"file1.txt", L"file2.txt", {}, {}, true, -1);

    std::vector<std::wstring> fileLines1 = {L"test", L"line1", L"line2"};
    std::vector<std::wstring> fileLines2 = {L"tes2", L"line1", L"line2"};

    std::vector<kdiff::Difference> differences = mayer.getDifferences(config, fileLines1, fileLines2);
    ASSERT_FALSE(differences.empty());

    ASSERT_EQ(differences[0].getValue(), L"test");
    ASSERT_EQ(static_cast<int>(differences[0].getType()),
              static_cast<int>(kdiff::Difference::DiffType::DELETED));

    ASSERT_EQ(differences[1].getValue(), L"tes2");
    ASSERT_EQ(static_cast<int>(differences[1].getType()),
              static_cast<int>(kdiff::Difference::DiffType::ADDED));
}

TEST(MayerTest, getDifferences_emptyFile) {
    kdiff::algorithm::line::Mayer mayer;
    kdiff::Config config(L"file1.txt", L"file2.txt", {}, {}, true, -1);

    std::vector<std::wstring> fileLines1 = {L"test", L"line1", L"line2"};
    std::vector<std::wstring> fileLines2 = {};

    std::vector<kdiff::Difference> differences = mayer.getDifferences(config, fileLines1, fileLines2);
    ASSERT_FALSE(differences.empty());

    ASSERT_EQ(differences[0].getValue(), L"test");
    ASSERT_EQ(static_cast<int>(differences[0].getType()),
              static_cast<int>(kdiff::Difference::DiffType::DELETED));

    ASSERT_EQ(differences[1].getValue(), L"line1");
    ASSERT_EQ(static_cast<int>(differences[1].getType()),
              static_cast<int>(kdiff::Difference::DiffType::DELETED));

    ASSERT_EQ(differences[1].getValue(), L"line2");
    ASSERT_EQ(static_cast<int>(differences[1].getType()),
              static_cast<int>(kdiff::Difference::DiffType::DELETED));
}

TEST(MayerTest, getDifferences_addedFile) {
    kdiff::algorithm::line::Mayer mayer;
    kdiff::Config config(L"file1.txt", L"file2.txt", {}, {}, true, -1);

    std::vector<std::wstring> fileLines1 = {};
    std::vector<std::wstring> fileLines2 = {L"test", L"line1", L"line2"};

    std::vector<kdiff::Difference> differences = mayer.getDifferences(config, fileLines1, fileLines2);
    ASSERT_FALSE(differences.empty());

    ASSERT_EQ(differences[0].getValue(), L"test");
    ASSERT_EQ(static_cast<int>(differences[0].getType()),
              static_cast<int>(kdiff::Difference::DiffType::ADDED));

    ASSERT_EQ(differences[1].getValue(), L"line1");
    ASSERT_EQ(static_cast<int>(differences[1].getType()),
              static_cast<int>(kdiff::Difference::DiffType::ADDED));

    ASSERT_EQ(differences[1].getValue(), L"line2");
    ASSERT_EQ(static_cast<int>(differences[1].getType()),
              static_cast<int>(kdiff::Difference::DiffType::ADDED));
}
