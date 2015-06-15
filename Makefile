# Specify extensions of files to delete when cleaning
CLEANEXTS		= o a 
CPP_COMPILER	= clang++
CPP_FLAGS		= -Wall -g -std=c++11 -I./
DEFINES			= -DPREFIX_SHADER_GL_VERSION
# Specify the target file and the install directory
OUTPUTFILE 		= libdatgui.a
BUILD_DIR 		= Build
LIB_DIR			= $(BUILD_DIR)/lib
OBJ_DIR			= $(BUILD_DIR)/obj
INCLUDE_DIR		= $(BUILD_DIR)/include/datgui
CPP_SOURCES		= FontTexture.cpp Shader.cpp ShaderProgram.cpp OpenGLRenderer.cpp DatGui.cpp Gui.cpp MemoryFileReader.cpp Text.cpp Row.cpp RowContainer.cpp ActionRow.cpp FolderRow.cpp CloseRow.cpp CheckboxRow.cpp Control.cpp TextField.cpp TextRow.cpp
CPP_OBJECTS		= $(CPP_SOURCES:%.cpp=$(OBJ_DIR)/%.o)
# Default target
all: dirs $(OUTPUTFILE)
	cd Example && make

clean:
	$(RM) -fR $(BUILD_DIR)

dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp Source/DatGui.hpp $(INCLUDE_DIR)/DatGui.hpp
	cp Source/Key.hpp $(INCLUDE_DIR)/Key.hpp

# Build sources
$(OUTPUTFILE): $(CPP_OBJECTS)
	ar ru $(LIB_DIR)/$@ $^
	ranlib $(LIB_DIR)/$@

$(OBJ_DIR)/%.o: Source/%.cpp
	$(CPP_COMPILER) $(CPP_FLAGS) $(DEFINES) -c $< -o $@