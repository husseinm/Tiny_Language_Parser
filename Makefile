IDIR =../include
CPPC=g++
CFLAGS=-I$(IDIR) -std=c++11 -lstdc++ -Wall

LIBS=-lm

_DEPS = nodes.h TinyLexicalAnalyzer.h TinyParser.h tokens.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = main.cpp TinyLexicalAnalyzer.cpp TinyParser.cpp


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

subc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 