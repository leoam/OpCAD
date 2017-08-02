#----------------------------------------------------------------
# project ....: LTI Digital Image/Signal Processing Library
# file .......: Template Makefile for Examples
# authors ....: Pablo Alvarado, Jochen Wickel
# organization: LTI, RWTH Aachen
# creation ...: 09.02.2003
# revisions ..: $Id: Makefile.in,v 1.3 2012-01-03 03:23:09 alvarado Exp $
#----------------------------------------------------------------

#Base Directory
LTIBASE:=../..
LTICMD:=$(LTIBASE)/linux/lti-local-config

#Example name
PACKAGE:=$(shell basename $$PWD)

# If you want to generate a debug version, uncomment the next line
BUILDRELEASE=yes

# Compiler to be used
CXX:=g++

# Run the prepare script, which links some source files
FOOCHECK := $(shell if [ -e ./prepare.sh ]; then ./prepare.sh; fi)

# For new versions of gcc, <limits> already exists, but in older
# versions a replacement is needed
CXX_MAJOR:=$(shell echo `$(CXX) --version | sed -e 's/\..*//;'`)

ifeq "$(CXX_MAJOR)" "2"
  VPATHADDON=:g++
  CPUARCH = -march=i686 -ftemplate-depth-35
  CPUARCHD = -march=i686 -ftemplate-depth-35
else
  ifeq "$(CXX_MAJOR)" "3"
  VPATHADDON=
  CPUARCH = -march=pentium4
  CPUARCHD = -march=pentium4
  else
  VPATHADDON=
  CPUARCH = -march=native
  CPUARCHD = 
  endif
endif

# Directories with source file code (.h and .cpp)
VPATH:=$(VPATHADDON)

# Destination directories for the debug and release versions of the code

OBJDIR  = ./

# Extra include directories and library directories for hardware specific stuff

EXTRAINCLUDEPATH =
EXTRALIBPATH =
EXTRALIBS    =

#EXTRAINCLUDEPATH = -I/usr/src/menable/include
#EXTRALIBPATH = -L/usr/src/menable/lib
#EXTRALIBS =  -lpulnixchanneltmc6700 -lmenable


# PROFILE = -p
PROFILE=

# compiler flags
CXXINCLUDE:=$(EXTRAINCLUDEPATH) $(patsubst %,-I%,$(subst :, ,$(VPATH)))

LINKDIR:=-L$(LTIBASE)/lib
CPPFILES=$(wildcard ./*.cpp)
OBJFILES=$(patsubst %.cpp,$(OBJDIR)%.o,$(notdir $(CPPFILES)))

# set the compiler/linker flags depending on the debug/release flag
ifeq "$(BUILDRELEASE)" "yes"
  LTICXXFLAGS:=$(shell $(LTICMD) --cxxflags)
  CXXFLAGSREL:=-c -O3 $(CPUARCH) -Wall -ansi $(LTICXXFLAGS) $(CXXINCLUDE)
  GCC:=$(CXX) $(CXXFLAGSREL) $(PROFILE)
  LIBS:=$(shell $(LTICMD) --libs) $(EXTRALIBPATH) $(EXTRALIBS)
else
  LTICXXFLAGS:=$(shell $(LTICMD) --cxxflags debug)
  CXXFLAGSDEB:=-c -g $(CPUARCH) -Wall -ansi $(LTICXXFLAGS) $(CXXINCLUDE)
  GCC:=$(CXX) $(CXXFLAGSDEB) $(PROFILE)
  LIBS:=$(shell $(LTICMD) --libs debug) $(EXTRALIBPATH) $(EXTRALIBS)
endif

LNALL = $(CXX) $(PROFILE) 

# implicit rules 
$(OBJDIR)%.o : %.cpp
	@echo "Compiling $<..."
	@$(GCC) $< -o $@

all: $(PACKAGE) 

# example
$(PACKAGE): $(OBJFILES)
	@echo "Linking $(PACKAGE)..."
	@$(LNALL) -o $(PACKAGE) $(OBJFILES) $(LIBS)

clean:
	@echo "Removing *.o files..."
	@rm -f *.o
	@echo "Ready."

clean-all:
	@echo "Removing files..."
	@echo "  removing obj, core and binary files..."  
	@rm -f ./core* $(PACKAGE) $(OBJDIR)*.o 
	@echo "  removing emacs backup files..."  
	@find $$PWD \( -name '*\~' -or -name '\#*' \) -exec rm -f {} \;
	@echo "  removing other automatic created backup files..."  
	@find $$PWD \( -name '\.\#*' -or -name '\#*' \) -exec rm -f {} \;
	@rm -fv nohup.out
	@if [ -e ./prepare.sh ]; then ./prepare.sh --clean ; fi
	@echo "Ready."

debug:
	@echo "Package: $(PACKAGE)"
	@echo "LTICXXFLAGS: $(LTICXXFLAGS)"
	@echo "CXXFLAGSDEB: $(CXXFLAGSDEB)"
	@echo "GCC: $(GCC)"
	@echo "LIBS: $(LIBS)"

