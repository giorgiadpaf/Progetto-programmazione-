#file per compilare tutto il progetto in un solo comando, basta lanciare make nel terminale
CXX = g++
LDFLAGS = -lncursesw
# Elenchi qui tutti i file oggetto che ti servono, se create altri file aggiungete alla lista NOMEFILE.o
OBJS = Entita.o Giocatore.o main_test.o  Nemico.o NemicoSparante.o Map.o Bomba.o Bombe.o

bomberman: $(OBJS)
	$(CXX) $(OBJS) -o bomberman $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f *.o bomberman
