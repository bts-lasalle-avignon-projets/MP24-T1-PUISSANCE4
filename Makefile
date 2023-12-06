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

%.o: %.cpp
	@echo -n "Compilation de $< en $@ :"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "\r$(VERT)Compilation de $< en $@ : $(VIOLET)[OK]$(NC)"

.PHONY: format clean check

format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Format 🐉 :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)
	@echo "$(VERT)Clang Format terminé.$(NC)"

check:
	@echo "\n$(JAUNE)------------------------"
	@echo "Installation de Clang Tidy 🔎 :"
	@echo "------------------------$(NC)"
	@sudo apt-get update >/dev/null && sudo apt-get install -y --no-install-recommends clang-tidy >/dev/null
	@echo "$(VERT)Installation de Clang Tidy terminée.$(NC)"
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Tidy :"
	@echo "------------------------$(NC)"
	@clang-tidy *.cpp --quiet -header-filter='.*' -checks=-*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-* --format-style=none -- -std=c++11
	@echo "$(VERT)Clang Tidy terminé.$(NC)"

clean:
	@echo "\n$(JAUNE)------------------------"
	@echo "Nettoyage 🧹:"
	@echo "------------------------$(NC)"
	@rm -rf *.o $(EXECUTABLE)
	@echo "$(VERT)Nettoyage terminé.$(NC)"