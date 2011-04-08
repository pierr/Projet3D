# Toggle the following line/comment under windows
LIBS =  -lglut -lGLU -lGL -lGLEW -lm
#LIBS =  -lglut32 -lGLU32 -lopengl32 -lglew32 -lm

CFLAGS = -Wall -O3 -mfpmath=sse -msse2 #-march=native -mtune=native
CXXFLAGS = -Wall -O3 -mfpmath=sse -msse2 #-march=native -mtune=native
CPPFLAGS = -I$(INCDIR) -I/include -I.
LDFLAGS = -L/usr/X11R6/lib -L/lib
LDLIBS = $(LIBS)  
CC = g++
CPP = g++

CIBLE = raymini
SRCS =  BoundingBox.cpp Camera.cpp Light.cpp Material.cpp Mesh.cpp Object.cpp Ray.cpp raymini.cpp RayTracer.cpp Scene.cpp Triangle.cpp Vertex.cpp

OBJS = $(SRCS:.cpp=.o)   


$(CIBLE): $(OBJS)
	g++ $(LDFLAGS) $(LIBS) -o $(CIBLE) $(OBJS)
clean:
	rm -f  *~ $(OBJS)

veryclean: clean
	rm -f $(CIBLE)

dep:
	gcc $(CPPFLAGS) -MM $(SRCS)

# Dependencies
BoundingBox.o: BoundingBox.cpp BoundingBox.h Vec3D.h
Camera.o: Camera.cpp Camera.h Vec3D.h
Light.o: Light.cpp Light.h Vec3D.h
Material.o: Material.cpp Material.h Vec3D.h
Mesh.o: Mesh.cpp Mesh.h Vertex.h Vec3D.h Triangle.h Edge.h
Object.o: Object.cpp Object.h Mesh.h Vertex.h Vec3D.h Triangle.h Edge.h \
 Material.h BoundingBox.h
Ray.o: Ray.cpp Ray.h Vec3D.h BoundingBox.h
raymini.o: raymini.cpp Camera.h Vec3D.h Scene.h Object.h Mesh.h Vertex.h \
 Triangle.h Edge.h Material.h BoundingBox.h Light.h Image.h
RayTracer.o: RayTracer.cpp RayTracer.h Vec3D.h Ray.h BoundingBox.h \
 Scene.h Object.h Mesh.h Vertex.h Triangle.h Edge.h Material.h Light.h Image.h
Scene.o: Scene.cpp Scene.h Object.h Mesh.h Vertex.h Vec3D.h Triangle.h \
 Edge.h Material.h BoundingBox.h Light.h
Triangle.o: Triangle.cpp Triangle.h
Vertex.o: Vertex.cpp Vertex.h Vec3D.h
