#ifndef __HONDO_LINESHADER_H__
#define __HONDO_LINESHADER_H__
class LineShader;
#include "../ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class LineShader {
  private:
    ShaderProgram shader_program;
    const GLuint from_id, to_id, color_id, mvp_mat_id;
  public:
    LineShader(); 
    void operator()();
    void stop();
    void set_from(const glm::vec3& from);
    void set_to(const glm::vec3& to);
    void set_color(const glm::vec3& color);
    void set_MVP(const glm::mat4& mvpMat);
};
#endif

