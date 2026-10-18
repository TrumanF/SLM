CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = slm.exe
SOURCES = src/slm.cpp src/GramFrequency.cpp src/TextGenerator.cpp
HEADERS = src/GramFrequency.h src/TextGenerator.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean