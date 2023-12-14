CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = .
INCDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCDIR)/*.h)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = puissance4.out



CLANG_FORMAT = clang-format
CLANG_FORMAT_STYLE = -style=file
CLANG_FORMAT_FILES = $(SOURCES) $(HEADERS)

CLANG_TIDY = clang-tidy
CLANG_TIDY_CHECKS = -*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-*

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

%.o: %.cpp $(HEADERS)
	@echo -n "Compilation de $< en $@ :"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "\r$(VERT)Compilation de $< en $@ : $(VIOLET)[OK]$(NC)"

.PHONY: format clean check test-clang-format

format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Format 🐉 :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)
	@echo "$(VERT)Clang Format terminé.$(NC)"

check:
	@echo "\n$(JAUNE)------------------------"
	@echo "Vérification de l'installation de Clang Tidy 🔎 :"
	@echo "------------------------$(NC)"
	@(which $(CLANG_TIDY) > /dev/null || (echo "$(JAUNE)Installation de Clang Tidy 🔎 :$(NC)" && sudo apt-get update >/dev/null && sudo apt-get install -y --no-install-recommends clang-tidy >/dev/null))
	@echo "$(VERT)Clang Tidy est installé ou a été installé avec succès.$(NC)"
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Tidy :"
	@echo "------------------------$(NC)"
	@$(CLANG_TIDY) $(SOURCES) $(HEADERS) --quiet -header-filter='.*' -checks=$(CLANG_TIDY_CHECKS) --format-style=none -- -std=c++11
	@echo "$(VERT)Clang Tidy terminé.$(NC)"

test-clang-format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Vérification du format du code avec Clang Format 🧐 :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) --dry-run --Werror $(CLANG_FORMAT_STYLE) $(CLANG_FORMAT_FILES)
	@echo "$(VERT)La vérification du format avec Clang Format est terminée.$(NC)"

clean:
	@echo "\n$(JAUNE)------------------------"
	@echo "Nettoyage 🧹:"
	@echo "------------------------$(NC)"
	@rm -rf *.o $(EXECUTABLE)
	@echo "$(VERT)Nettoyage terminé.$(NC)"