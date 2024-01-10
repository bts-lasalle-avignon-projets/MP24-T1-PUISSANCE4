SRCDIR = src/sources
INCDIR = src/headers
OBJDIR = src/sources

CXX = g++
CXXFLAGS = -std=c++11   -Wall -I$(INCDIR)

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = puissance4.out

CLANG_FORMAT = clang-format
CLANG_FORMAT_STYLE = -style=file
CLANG_FORMAT_FILES = $(SOURCES) $(wildcard $(INCDIR)/*.h)

CLANG_TIDY_INSTALLED := $(shell command -v clang-tidy 2> /dev/null)

# Couleurs
VERT=\033[1;92m
JAUNE=\033[1;93m
GRIS=\033[0;35m
VIOLET=\033[1;95m
NC =\033[0m

all: format $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "$(JAUNE)------------------------"
	@echo "Edition des liens 📝 :"
	@echo "------------------------$(NC)"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "$(VERT)Compilation réussie : $(EXECUTABLE)$(NC)"
	@echo "$(VERT)Fichiers compilés avec succès.$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo -n "Compilation de $< en $@ :"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "\r$(VERT)Compilation de $< en $@ : $(VIOLET)[OK]$(NC)"

.PHONY: format clean check test-clang-format install-clang-tidy

format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Format 🐉 :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)
	@echo "$(VERT)Clang Format terminé.$(NC)"

check: install-clang-tidy
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Tidy 🔎 :"
	@echo "------------------------$(NC)"
	@clang-tidy $(SOURCES) --quiet -header-filter='.*' -checks=-*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-* --format-style=none -- -std=c++11 -I$(INCDIR)
	@echo "$(VERT)Clang Tidy terminé.$(NC)"

test-clang-format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Vérification du format du code avec Clang Format 🧐 :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) --dry-run --Werror $(CLANG_FORMAT_STYLE) $(CLANG_FORMAT_FILES)
	@echo "$(VERT)La vérification du format avec Clang Format est terminée.$(NC)"

install-clang-tidy:
ifndef CLANG_TIDY_INSTALLED
	@echo "\n$(JAUNE)------------------------"
	@echo "Installation de Clang Tidy 🛠️ :"
	@echo "------------------------$(NC)"
	@sudo apt-get update >/dev/null && sudo apt-get install -y --no-install-recommends clang-tidy >/dev/null
	@echo "$(VERT)Installation de Clang Tidy terminée.$(NC)"
endif

clean:
	@echo "\n$(JAUNE)------------------------"
	@echo "Nettoyage 🧹:"
	@echo "------------------------$(NC)"
	@rm -rf $(OBJDIR)/*.o $(EXECUTABLE)
	@echo "$(VERT)Nettoyage terminé.$(NC)"
