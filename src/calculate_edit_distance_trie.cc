#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "absl/strings/str_join.h"

#include <gflags/gflags.h>

DEFINE_string(input_filepath, "", "input filepath.");
DEFINE_string(output_filepath, "", "input filepath.");
DEFINE_int32(threshold, 4,
             "only pairs with edit distance equal to or less than this will "
             "be output.");

class TrieNode {
 public:
  std::string word_;
  std::unordered_map<char, TrieNode> children_;
  void insert(const std::string& word) {
    auto* node = this;
    for (int i = 0; i < word.size(); i++) {
      node = &children_[word[i]];
    }
    node->word_ = word;
  }

  std::ostream& operator<<(std::ostream& out, TrieNode const& data) {
    if (!word_.empty()) out << "word: " << word_;
    for (const auto& pair : children_) {
      out << "char: " << pair.first;
      out << pair.second;
      out << "\n";
    }
    return out;
  }
};

void search_recursive(const TrieNode* node, char letter,
                      const std::string& word,
                      const std::vector<int>& previousRow,
                      std::vector<std::pair<std::string, int>>* results) {
  std::vector<int> currentRow;
  currentRow.emplace_back(previousRow[0] + 1);
  for (int i = 1; i < word.size() + 1; i++) {
    int insertCost = currentRow[i - 1] + 1;
    int deleteCost = previousRow[i] + 1;
    int replaceCost;
    if (word[i - 1] != letter) {
      replaceCost = previousRow[i - 1] + 1;
    } else {
      replaceCost = previousRow[i - 1];
    }
    currentRow.emplace_back(std::min({insertCost, deleteCost, replaceCost}));
  }

  if (currentRow[currentRow.size() - 1] < FLAGS_threshold &&
      !node->word_.empty()) {
    results->emplace_back(
        std::make_pair(node->word_, currentRow[currentRow.size() - 1]));
  }
  if (*std::min_element(currentRow.begin(), currentRow.end()) <
      FLAGS_threshold) {
    for (const auto& pair : node->children_) {
      search_recursive(&pair.second, pair.first, word, currentRow, results);
    }
  }
}

std::vector<std::pair<std::string, int>> search(const std::string& word,
                                                const TrieNode* node) {
  std::vector<int> first_row;
  for (int i = 0; i < word.size(); i++) {
    first_row.emplace_back(i);
  }

  std::vector<std::pair<std::string, int>> results;

  for (const auto& pair : node->children_) {
    search_recursive(&pair.second, pair.first, word, first_row, &results);
  }
  return results;
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::vector<std::string> v = {"foo", "bar", "baz"};
  TrieNode t;
  t.insert("foo");
  t.insert("bar");
  t.insert("baz");

  // print trie
  std::cout << t;

  const auto& results = search("foo", &t);

  for (const auto& result : results) {
    std::cout << "word: " << result.first << " distance: " << result.second
              << "\n";
  }
  // std::string s = absl::StrJoin(v, "-");

  // std::cout << "Joined string: " << s << "\n";

  // std::cout << "languages: " << FLAGS_input_filepath << "\n";

  return (0);
}
