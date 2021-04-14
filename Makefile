CXX = g++
CXXFLAGS = -Wall
LIBS = -lGLEW -lglfw -lGL -Isrc/include/glm
DEFINES = #-DWIREFRAME_MODE
SOURCES = src/application/Application.cpp \
	src/window/Events.cpp \
	src/window/EventsManager.cpp \
	src/window/Window.cpp \
	src/graphics/Camera.cpp \
	src/graphics/Shader.cpp \
	src/graphics/Texture.cpp \
	src/graphics/Mesh.cpp \
	src/xstdlib/xstdlib.cpp \
	src/game/CelestialObject.cpp \
	src/game/objects.cpp \
	src/game/space-simulator.cpp
OBJECTS = ${SOURCES:.cpp=.o}
EXECUTABLE = space-simulator

.PHONY: all clean

all: clean $(EXECUTABLE)

clean:
	@rm -rf $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(LIBS) $(DEFINES) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(LIBS) $(DEFINES) -c $< -o $@
