CC := clang++
C  := clang
CLANGD := .clangd

CCSTD := c++20

# Recursive wildcard pattern for all files
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXEC := touhou.exe

SRCDIR := source
BLDDIR := build
OBJDIR := obj
EXTDIR := $(SRCDIR)/external

SOURCES := 	$(call rwildcard,$(SRCDIR),*.cpp) \
			$(call rwildcard,$(SRCDIR),*.c)

OBJECTS := 	$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
OBJECTS := 	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(OBJECTS))

BUILD := $(BLDDIR)/$(EXEC)

INCLUDES := -I$(EXTDIR) \
			-I$(EXTDIR)/bigngine/ \
			$(patsubst %,-I%,$(sort $(call rwildcard,$(EXTDIR),*/include/))) \
			$(patsubst %,-I%,$(sort $(dir $(call rwildcard,$(EXTDIR),*.h)))) \
			$(patsubst %,-I%../,$(sort $(dir $(call rwildcard,$(EXTDIR),*.h))))

LIBS := $(call rwildcard,$(EXTDIR),*.lib)

FLAGS := -Wall
CFLAGS := $(FLAGS)
CCFLAGS := $(FLAGS) --std=$(CCSTD)

LDFLAGS := $(foreach LIB,$(LIBS),-l$(patsubst %.lib,%,$(notdir $(LIB)))) $(foreach LIB,$(LIBS),-L$(dir $(LIB)))

# Rule for linking the .obj files
$(BUILD): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

# Rule for compiling the .cpp files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CCFLAGS) -c -o $@ $< $(INCLUDES)

# Rule for compiling the .c files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(C) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Rule for generating the .clangd file
clangd:
	echo CompileFlags:> $(CLANGD) \
	&& echo     Add:>> $(CLANGD) \
	&& echo $(foreach FLAG,$(CCFLAGS),        - $(FLAG)>> $(CLANGD) && echo) \
	&& echo $(foreach INCLUDE,$(INCLUDES),        - $(INCLUDE)>> $(CLANGD) && echo) \

# Rule for running the built executable
run:
	cd $(BLDDIR) && $(EXEC)

# Rule for cleaning the obj and the build directory
clean:
	del $(subst /,\,$(patsubst %,"%",$(OBJECTS)))