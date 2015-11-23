CXX := clang++
CXXFLAGS := -std=c++11 -stdlib=libc++ -Wall

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

TESTSRCS := $(wildcard tests/*.cpp)
TESTOBJS := $(TESTSRCS:.cpp=.o)
TESTOBJS += $(filter-out src/main.o,$(OBJS))

TARGET := typeahead_search

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

test: $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTOBJS) -o run_tests
	./run_tests

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	cpplint $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) run_tests

-include $(OBS:.o=.d)
-include $(TESTOBJS:.o=.d)