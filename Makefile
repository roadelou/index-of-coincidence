################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-04-16
# Language: Makefile

################################### ALIASES ####################################

# Source files.
SRC = $(wildcard $(CURDIR)/src/*.c)
# Header files.
HEAD = $(wildcard $(CURDIR)/include/*.h)

# Include compile flag.
INCLUDE_FLAG = -I $(CURDIR)/include
# Warning flags.
WARN_FLAGS = -Wall -pedantic
# Compiler C flags.
C_FLAGS = $(INCLUDE_FLAG) $(WARN_FLAGS)

# Build folder.
BUILDDIR = $(CURDIR)/build
# Built executable.
EXEC = $(BUILDDIR)/index-of-coincidence.elf

# Installation directory.
INSTALLDIR = $(DESTDIR)/usr/bin/
# Installed executable.
INSTALLED = $(INSTALLDIR)/index-of-coincidence

################################### SPECIAL ####################################

.PHONY: all clean install uninstall

#################################### RULES #####################################

all: $(EXEC)

$(EXEC): $(BUILDDIR) $(SRC) $(HEAD)
	$(CC) $(C_FLAGS) $(SRC) -o $(EXEC)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(INSTALLED): $(EXEC) $(INSTALLDIR)
	install -m 755 $(EXEC) $(INSTALLED)

$(INSTALLDIR):
	mkdir -p $(INSTALLDIR)

clean:
	rm -f $(EXEC)

install: $(INSTALLED)

uninstall:
	rm -f $(INSTALLED)

##################################### EOF ######################################
