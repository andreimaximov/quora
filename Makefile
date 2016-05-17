CXX := clang++
CXXFLAGS := -std=c++11 -stdlib=libc++ -O3 -Wall

SRCS := $(wildcard src/*.cpp)
HDRS := $(wildcard src/*.hpp)
OBJS := $(SRCS:.cpp=.o)

TESTSRCS := $(wildcard tests/*.cpp)
TESTOBJS := $(TESTSRCS:.cpp=.o)
TESTOBJS += $(filter-out src/main.o,$(OBJS))

TARGET := typeahead_search

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

test: $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTOBJS) -o run_tests
	./run_tests

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	cpplint $(SRCS) $(HDRS)

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) run_tests

-include $(OBS:.o=.d)
-include $(TESTOBJS:.o=.d)
