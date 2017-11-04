cc_binary(
  name = "calculate_edit_distance",
  deps = ["@com_google_absl//absl/strings","//external:gflags", ":edlib"],
  srcs = ["calculate_edit_distance.cc"],
)

cc_library(
  name = "edlib",
  srcs = ["edlib.cc"],
  hdrs = ["edlib.h"],
)

py_binary(
  name = "generate_test_words",
  srcs = ["generate_test_words.py"],
)
