# Compiler
CC := clang++
# Compiler flags
CFLAGS := -std=c++11 -stdlib=libc++ -Wall
# Include directories
INCLUDES := -I./include
# Libraries
LIBS := -lSDL2

# Source files directory
SRCDIR := ./src
# Object files directory
OBJDIR := ./obj
# Executable name
EXEC := perspective_projection

# List of all source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# Generate names of object files from source files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Default target
all: $(EXEC)

# Linking step
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

# Compiling step for each source file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean target to remove generated files
clean:
	rm -rf $(OBJDIR) $(EXEC)

