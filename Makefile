CC := clang++

NAME := touhou.exe

SRCDIR := src
OBJDIR := obj
BLDDIR := build
EXTDIR := $(SRCDIR)/external

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
GLAD := $(SRCDIR)/external/glad/glad.c
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
BUILD := $(BLDDIR)/$(NAME)
DLLS := $(wildcard $(BLDDIR)/*.dll)

CFLAGS := 	-std=c++20 \
			$(patsubst %,-I%,$(wildcard $(EXTDIR)/*/include)) \
			-I$(EXTDIR)/bigngine/include/external/FreeType/include \
			-Wall -v
LDFLAGS := $(patsubst %,-L%,$(wildcard $(EXTDIR)/*/lib)) $(patsubst $(BLDDIR)/%.dll,-l%,$(DLLS))

output: $(OBJECTS)
	$(CC) $(LDFLAGS) $< $(GLAD) -o $(BUILD)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(shell IF NOT EXIST $(OBJDIR) mkdir $(OBJDIR))
	$(CC) $(CFLAGS) -c $< -o "$@"

make run: $(BUILD)
	$(BUILD)

.PHONY: clean
clean:
	$(foreach OBJECT,$(OBJECTS),$(subst /,\,del "$(OBJECTS)"))
# del "$(patsubst %/%,%\%,$(OBJECTS))"
# $(foreach OBJECT,$(OBJECTS),$(shell del "$(OBJECTS)"))
# ifneq ("$(wildcard $(BUILD))","")
# 		del "$(BUILD)"
# endif