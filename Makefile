CC := clang++

NAME := touhou.exe

SRCDIR := src
OBJDIR := obj
BLDDIR := build
EXTDIR := $(SRCDIR)/external

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
BUILD := $(BLDDIR)/$(NAME)
DLLS := $(wildcard $(BLDDIR)/*.dll)

CFLAGS := 	-std=c++20 \
			$(patsubst %,-I%,$(wildcard $(EXTDIR)/*/include)) \
			-I$(EXTDIR)/bigngine/include/external/FreeType/include \
			-Wall
LDFLAGS := $(patsubst %,-L%,$(wildcard $(EXTDIR)/*/lib)) $(patsubst $(BLDDIR)/%.dll,-l%,$(DLLS))

output: $(OBJECTS)
	$(CC) $(LDFLAGS) $< -o $(BUILD)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	del "$(OBJECTS)"
	ifneq ("$(wildcard $(BUILD))","")
		del "$(BUILD)"
	endif