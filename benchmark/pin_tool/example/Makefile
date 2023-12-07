# Makefile for the trace Pintool

ifdef PIN_ROOT
PIN_ROOT := $(PIN_ROOT)
else
PIN_ROOT:=/opt/pin
endif
# Set up the pin root directory and tool C++ flags

CXXFLAGS := -Wall -Werror -Wno-unknown-pragmas $(PIN_CXXFLAGS)
TOOL_ROOTS := trace

# Include Pin tool build configuration
CONFIG_ROOT := $(PIN_ROOT)/source/tools/Config
include $(CONFIG_ROOT)/makefile.config
include $(TOOLS_ROOT)/Config/makefile.default.rules

# Specify the tool name
TOOL = trace 

# Source files
SOURCES = trace.cpp

# Build target for the Pin tool
$(TOOL).so: $(SOURCES:%.cpp=%.o)
	$(CXX) $(PIN_LDFLAGS) $(LINK_DEBUG) $(SOURCES:%.cpp=%.o) $(PIN_LIBS) $(DBG) -o $@

# Clean target
clean:
	rm -f $(TOOL).so $(SOURCES:%.cpp=%.o)

# Rule to compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PIN_CXXFLAGS) -c $< -o $@

