set(SRC_FILES Reader.cpp Statistics.cpp PrefixTree.cpp Encoder.cpp Writer.cpp Decoder.cpp DecodeTree.cpp HeapTree.cpp)

add_library(archiver_library ${SRC_FILES})
target_include_directories(archiver_library PUBLIC ./)