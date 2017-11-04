#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "absl/strings/str_join.h"
#include "edlib.h"

#include <gflags/gflags.h>

DEFINE_string(input_filepath, "", "input filepath.");
DEFINE_string(output_filepath, "", "input filepath.");
DEFINE_int32(threshold, 4,
             "only pairs with edit distance equal to or less than this will "
             "be output.");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::vector<std::string> words;
  std::ifstream input(FLAGS_input_filepath);
  for (std::string line; getline(input, line);) {
    words.emplace_back(line);
  }
  input.close();

  std::cout << "Calculating edit distance for " << words.size() << " words."
            << std::endl;

  std::ofstream output;
  int output_num = 0;
  for (int i = 0; i < words.size(); i++) {
    std::cout << "Word: " << i << std::endl;
    for (int j = i; j < words.size(); j++) {
      EdlibAlignResult result =
          edlibAlign(words[i].c_str(), words[i].size(), words[j].c_str(),
                     words[j].size(), edlibDefaultAlignConfig());
      if (result.editDistance <= FLAGS_threshold) {
        output << result.editDistance << "," << words[i] << "," << words[j];
        output_num++;
      }
    }
  }
  output.close();

  std::cout << "Output " << output_num << " words." << std::endl;

  return (0);
}
