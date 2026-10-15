CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = slm
SOURCES = main.cpp GramFrequency.cpp TextGenerator.cpp
HEADERS = GramFrequency.h TextGenerator.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
rm -f $(TARGET)

.PHONY: all clean