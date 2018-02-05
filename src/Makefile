#g++ -std=c++14 -fpermissive -g -Iboost_1_64_0 -c main.cpp mycfg.cpp myUtil.cpp myWPDS.cpp
#g++ -std=c++14 -fpermissive -g -Iboost_1_64_0 -o myWPDS main.o mycfg.o myUtil.o myWPDS.o
# Cudd stuff:
BOOSTVER = boost_1_64_0

# Windows / Posix differences:
ifdef WIN32
  MALDET = STAMAD.exe
  CC = cl /MT /I$(BOOSTVER) /DWIN32
  LINK=link
  LIBS = -lpthread
  O = obj
else # POSIX
  MALDET = STAMAD
  CCINCLUDEDIR =
  CC = g++  -std=c++14 -fpermissive -g -O3 -Wall -I$(BOOSTVER) #-DYYDEBUG
  LIBS = -lpthread
  LINK=$(CC)
  O = o
endif



MODULES = main mycfg myUtil myWPDS

OBJECTS = $(MODULES:=.$(O))

$(MALDET): $(OBJECTS)
ifdef WIN32
	$(LINK) $(OBJECTS) /OUT:$@ $(LIBS)
else # POSIX
	$(LINK) $(OBJECTS) -o $@ $(LIBS)
endif

# Compiling:
%.$(O): %.cpp
	$(CC) -c $<

# clean

clean:
	rm -f $(MALDET) $(OBJECTS) $(TMPFILES) \
              frag_* core* *.$(O) *.output mon.out gmon.out *.d .deps
