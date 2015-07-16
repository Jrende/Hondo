#pragma once
#include "../input/Input.hpp"
#include "../gfx/Camera.hpp"
#include <memory>
class FPSController {
  private:
    std::shared_ptr<Camera> camera;
    double target_x, target_y, current_x, current_y;
    double MOUSE_X_SENSITIVITY = 20;
    double MOUSE_Y_SENSITIVITY = 20;
    double PANNING_SPEED = 15;
    float step = 0.01f;
  public:
    FPSController();
    void handle_mouse();
    void handle_movement();
    std::shared_ptr<Camera> get_camera();
};
