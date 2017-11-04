git_repository(
    name   = "com_google_absl",
    commit = "da336a84e9c1f86409b21996164ae9602b37f9ca",
    remote = "https://github.com/abseil/abseil-cpp.git",
)

git_repository(
    name   = "com_github_gflags_gflags",
    commit = "77592648e3f3be87d6c7123eb81cbad75f9aef5a",
    remote = "https://github.com/gflags/gflags.git",
)


bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

bind(
    name = "gflags_nothreads",
    actual = "@com_github_gflags_gflags//:gflags_nothreads",
)
