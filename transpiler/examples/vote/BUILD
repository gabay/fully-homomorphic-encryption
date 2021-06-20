load("//transpiler:fhe.bzl", "fhe_cc_library")
load("@bazel_skylib//:bzl_library.bzl", "bzl_library")

licenses(["notice"])

cc_library(
    name = "vote_api",
    srcs = ["vote_api.cc"],
    hdrs = ["vote_api.h"],
    deps = [],
)

cc_binary(
    name = "vote",
    srcs = [
        "vote_api.h",
        "vote_main.cc",
    ],
    deps = [
        ":vote_api_tfhe",
        "//transpiler/data:fhe_data",
        "@com_google_absl//absl/base",
        "@com_google_xls//xls/common/logging",
        "@com_google_xls//xls/common/status:status_macros",
        "@tfhe//:libtfhe",
    ],
)

cc_binary(
    name = "vote_bool",
    srcs = [
        "vote_api.h",
        "vote_main_bool.cc",
    ],
    deps = [
        ":vote_api_bool",
        "//transpiler/data:fhe_data",
        "@com_google_absl//absl/base",
        "@com_google_xls//xls/common/logging",
        "@com_google_xls//xls/common/status:status_macros",
        "@tfhe//:libtfhe",
    ],
)

fhe_cc_library(
    name = "vote_api_tfhe",
    src = "vote_api.cc",
    hdrs = ["vote_api.h"],
    num_opt_passes = 2,
)

fhe_cc_library(
    name = "vote_api_bool",
    src = "vote_api.cc",
    hdrs = ["vote_api.h"],
    num_opt_passes = 2,
    transpiler_type = "bool",
)
