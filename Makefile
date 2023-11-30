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
VERT = \033[0;32m
JAUNE = \033[1;33m
GRIS = \033[0;35m
NC = \033[0m

all: format $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "$(JAUNE)------------------------"
	@echo "Edition des liens :"
	@echo "------------------------$(NC)"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "$(VERT)Compilation réussie : $(EXECUTABLE)$(NC)"
	@echo "$(VERT)Fichiers compilés avec succès.$(NC)"

%.o: %.cpp
	@echo "Compilation de $< en $@ :"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(VERT)Fichier $< compilé avec succès en $@.$(NC)"

.PHONY: format clean

format:
	@echo "\n$(JAUNE)------------------------"
	@echo "Exécution de Clang Format :"
	@echo "------------------------$(NC)"
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)
	@echo "$(VERT)Clang Format terminé.$(NC)"

clean:
	@echo "\n$(JAUNE)------------------------"
	@echo "Nettoyage 🧹:"
	@echo "------------------------$(NC)"
	@rm -rf *.o $(EXECUTABLE)
	@echo "$(VERT)Nettoyage terminé.$(NC)"
