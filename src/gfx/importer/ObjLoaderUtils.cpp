#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include "ObjLoaderUtils.hpp"

namespace ObjLoaderUtils {

  std::string popFirstToken(std::vector<std::string>& vec) {
    std::string first = vec[0];
    vec.erase(vec.begin(), vec.begin() + 1);
    return first;
  }

  void printVec(glm::vec2 v) {
    std::cout << v.x << ", " << v.y << std::endl;
  }

  void printVec(glm::vec3 v) {
    std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
  }

  void calcTangent(Face& face) {
    glm::vec3 v1({
      face.verts[0].pos[0],
      face.verts[0].pos[1],
      face.verts[0].pos[2]
    });

    glm::vec3 v2({
      face.verts[1].pos[0],
      face.verts[1].pos[1],
      face.verts[1].pos[2]
    });

    glm::vec3 v3({
      face.verts[2].pos[0],
      face.verts[2].pos[1],
      face.verts[2].pos[2]
    });

    glm::vec2 w1({
      face.verts[0].uv[0],
      face.verts[0].uv[1]
    });

    glm::vec2 w2({
      face.verts[1].uv[0],
      face.verts[1].uv[1]
    });

    glm::vec2 w3({
      face.verts[2].uv[0],
      face.verts[2].uv[1]
    });



    float x1 = v2.x - v1.x;
    float x2 = v3.x - v1.x;
    float y1 = v2.y - v1.y;
    float y2 = v3.y - v1.y;
    float z1 = v2.z - v1.z;
    float z2 = v3.z - v1.z;

    float s1 = w2.x - w1.x;
    float s2 = w3.x - w1.x;
    float t1 = w2.y - w1.y;
    float t2 = w3.y - w1.y;

    float r = 1.0F / (s1 * t2 - s2 * t1);
    //Might be wrong, but it looks okay, so whatever.
    r = std::max(0.0f, std::min(r, 1.0f));
    
    glm::vec3 sdir({
      (t2 * x1 - t1 * x2) * r,
      (t2 * y1 - t1 * y2) * r,
      (t2 * z1 - t1 * z2) * r
    });
    glm::vec3 tdir({
      (s1 * x2 - s2 * x1) * r,
      (s1 * y2 - s2 * y1) * r,
      (s1 * z2 - s2 * z1) * r
    });

    for(Vertex& v: face.verts) {
      // Gram-Schmidt orthogonalize
      glm::vec3 t = sdir;
      glm::vec3 n = glm::vec3{
	v.normal[0],
	v.normal[1],
	v.normal[2]
      };
      const auto& bt = glm::vec3{(t - n * glm::dot(n, t))};
      v.tangent[0] = bt.x;
      v.tangent[1] = bt.y;
      v.tangent[2] = bt.z;

      const auto& bt2 = glm::cross(n, bt);
      v.bitangent[0] = bt2.x;
      v.bitangent[1] = bt2.y;
      v.bitangent[2] = bt2.z;
    }
    /*
    for(auto& vertex: face.verts) {
      const glm::vec3& n({vertex.normal.x, vertex.normal.y, vertex.normal.z}_
      const glm::vec3& n({vertex.normal.x, vertex.normal.y, vertex.normal.z}_
    }

    face.verts[0].tangent = {sdir.x, sdir.y, sdir.z}
    face.verts[0].bitangent = {tdir.x, tdir.y, tdir.z};
    face.verts[1].tangent = {sdir.x, sdir.y, sdir.z};
    face.verts[1].bitangent = {tdir.x, tdir.y, tdir.z};
    face.verts[2].tangent = {sdir.x, sdir.y, sdir.z};
    face.verts[2].bitangent = {tdir.x, tdir.y, tdir.z};
    */
  }
}
