"""
CC Compiler options to be used for all project files.
"""

CC_OPTS = select({
    "@bazel_tools//src/conditions:windows": ["/std:c++20"],
    "//conditions:default": ["-std=c++20"],
})
