SOURCE_FILE = ./usr/main2.cpp
BYTECODE_SOURCE_FILE = ./usr/main1.cpp
TEST_SOURCE_FILE = ./usr/main3.cpp

TARGET = ./usr/bin/mer
BYTECODE_TARGET = ./usr/bin/merc
TEST_TARGET = ./usr/bin/mer3
CXX = g++

all:
	@printf "mer.exe building... "
	@/usr/bin/time -f "Time: %E" $(CXX) $(SOURCE_FILE) -o $(TARGET) > /dev/null 2>&1 && printf "\033[1;32mPassed!\033[0m\n" || { printf "\033[1;31mBuild failed!\033[0m\n"; exit 0; }

	@printf "merc.exe building... "
	@/usr/bin/time -f "Time: %E" $(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > /dev/null 2>&1 && printf "\033[1;32mPassed!\033[0m\n" || { printf "\033[1;31mBuild failed!\033[0m\n"; exit 0; }
	
	@printf "mer3.exe building... "
	@/usr/bin/time -f "Time: %E" $(CXX) $(TEST_SOURCE_FILE) -o $(TEST_TARGET) > /dev/null 2>&1 && printf "\033[1;32mPassed!\033[0m\n" || { printf "\033[1;31mBuild failed!\033[0m\n"; exit 0; }

clean:
	@rm -f $(TARGET) $(BYTECODE_TARGET) > /dev/null 2>&1
	@printf "\033[1;32mCleaned!\033[0m\n"
