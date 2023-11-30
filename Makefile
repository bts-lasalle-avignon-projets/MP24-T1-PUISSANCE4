CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = puissance4.out

CLANG_FORMAT = clang-format
CLANG_FORMAT_STYLE = -style=file
CLANG_FORMAT_FILES = $(SOURCES) $(wildcard $(SRCDIR)/*.h)

# Couleurs
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m

all: format $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "$(YELLOW)Linking...$(NC)"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "$(GREEN)Build complete: $(EXECUTABLE)$(NC)"

%.o: %.cpp
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: format clean

format:
	@echo "$(YELLOW)Running Clang Format...$(NC)"
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)
	@echo "$(GREEN)Clang Format done.$(NC)"

clean:
	@echo "$(YELLOW)Cleaning...$(NC)"
	@rm -rf *.o $(EXECUTABLE)
	@echo "$(GREEN)Clean complete.$(NC)"
