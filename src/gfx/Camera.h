#ifndef __HONDO_CAMERA_H__
#define __HONDO_CAMERA_H__
class Camera;
#include <string>
#include "RenderObject.h"
#include <stdlib.h>
class Camera {
  private:
    glm::vec3 up,pos,forward;
  public:
    glm::mat4 view_mat;
    void translate(glm::vec3 pos);
    void rotate(glm::vec4 axis_angle);
    Camera();
};
#endif
