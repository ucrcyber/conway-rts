CC_OPTS = select({
    "//config:compiler_gcc": [], # gets set in .bazelrc
    "//config:compiler_cl": ["/std:c++17"],
    "//conditions:default": [],
})
