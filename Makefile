CXX      = clang++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -fmodules

BUILD_DIR = build
MOD_CACHE = $(BUILD_DIR)/modules

INCLUDES = -Iapps/tokenizer

MODULE_SRCS = $(shell find apps/tokenizer -name "*.cppm")

MODULE_PCMS = $(patsubst apps/tokenizer/%,$(MOD_CACHE)/%,$(MODULE_SRCS:.cppm=.pcm))

TOKENIZER_SRC = apps/tokenizer/main.cpp
TOKENIZER_BIN = $(BUILD_DIR)/tokenizer

MODULE_FLAGS = $(foreach pcm,$(MODULE_PCMS),-fmodule-file=$(basename $(notdir $(pcm)))=$(pcm))

$(TOKENIZER_BIN): $(MODULE_PCMS) $(TOKENIZER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(MODULE_FLAGS) $(MODULE_PCMS) $(TOKENIZER_SRC) -o $(TOKENIZER_BIN)

$(MOD_CACHE)/%.pcm: apps/tokenizer/%.cppm
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) --precompile -x c++-module $< -o $@

run-tokenizer: $(TOKENIZER_BIN)
	./$(TOKENIZER_BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: run-tokenizer clean
