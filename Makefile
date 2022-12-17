CXX                ?= g++
CXX_OPTS           ?= -Wall -Werror -Wextra -g -fPIC -I./inc
SRC                 = $(wildcard src/*_app.cc)
LIBSRC              = $(wildcard src/*_lib.cc)
BIN                 = $(patsubst src/%.cc, bin/%.o, $(SRC))
BIN_LIB             = $(patsubst src/%.cc, bin/%.o, $(LIBSRC))
TARGET             ?= /usr
VERSION             = 1
OUT                 = target/tnb-cli
OUT_LIB             = target/libtnb.so
all: build
bin/%.o: src/%.cc
	@echo "Compiling $^ into $@"
	@$(CXX) $(CXX_OPTS) -c -o $@ $^
build: $(BIN) $(BIN_LIB)
	@echo "Linking $(BIN_LIB) into $(OUT_LIB)"
	@$(CXX) $(CXX_OPTS) -o $(OUT_LIB) $(BIN_LIB) -shared
	@echo "Linking $(BIN) into $(OUT)"
	@$(CXX) $(CXX_OPTS) -ltnb -L./target -o $(OUT) $(BIN)
install: build
	cp $(OUT) $(TARGET)/bin
	cp $(OUT_LIB) $(TARGET)/lib
	mkdir -p $(TARGET)/include/TNB
	cp inc/* $(TARGET)/include/TNB
clean:
	@echo "Removing $(BIN) $(BIN_LIB) $(OUT) $(OUT_LIB)"
	@rm -rf $(BIN) $(BIN_LIB) $(OUT) $(OUT_LIB)