#ifndef __HONDO_OBJLOADER_H__
#define __HONDO_OBJLOADER_H__
class ObjLoader;
#include <string>
#include <vector>
#include <array>
class ObjLoader {
  private:
    std::vector<std::array<float, 3>> posList;
    std::vector<std::array<float, 2>> uvList;
    std::vector<std::array<float, 3>> normalList;
    std::vector<float> vertexBuffer;
    void createFace(const std::vector<std::string>& face);
  public:
    ObjLoader(std::string path);
    unsigned int vertexCount;
    const std::vector<float>& getVertices();
    void handleTokens(std::vector<std::string> tokens);
};
#endif
