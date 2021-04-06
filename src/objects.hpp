#ifndef ENGINE_OBJECTS_H
#define ENGINE_OBJECTS_H

class Mesh;

Mesh *form_cube();
Mesh *form_sphere(int longitude_count, int latitude_count);
Mesh *form_circle(int angle_count);

#endif /* ENGINE_OBJECTS_H */
