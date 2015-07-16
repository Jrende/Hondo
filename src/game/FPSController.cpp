#include "FPSController.hpp"
#include <iostream>
#include <math.h>

float acc = 0.5;
FPSController::FPSController():
  camera(std::make_shared<Camera>())
{

  Input::on(Actions::Forward, [&]() {
      current_speed.z = fmax(current_speed.z + step/acc, step);
  });

  Input::on(Actions::Backward, [&]() {
      current_speed.z = fmin(current_speed.z - step/acc, -step);
  });

  Input::on(Actions::Left, [&]() {
      current_speed.x = fmax(current_speed.x + step/acc, step);
  });

  Input::on(Actions::Right, [&]() {
      current_speed.x = fmin(current_speed.x - step/acc, -step);
  });

  Input::on(Actions::Up, [&]() {
    current_speed.y = fmax(current_speed.y + step/acc, step);
  });
  Input::on(Actions::Down, [&]() {
    current_speed.y = fmin(current_speed.y - step/acc, -step);
  });

  Input::on_scroll([&](double x_offset, double y_offset) {
      step = fmax(0.001f, fmin(step * pow(1.5, y_offset), 5));
  });

  Input::on(GLFW_KEY_Q, [&] {
      step = fmax(0.001f, fmin(step * pow(1.5, -1), 5));
  }, false);

  Input::on(GLFW_KEY_E, [&] {
      step = fmax(0.001f, fmin(step * pow(1.5, 1), 5));
  }, false);
}

void FPSController::handle_mouse() {
  if(Input::is_mouse_locked()) {
    const auto x = Input::get_mouse_dx() / MOUSE_X_SENSITIVITY;
    const auto y = Input::get_mouse_dy() / MOUSE_Y_SENSITIVITY;
    target_x += x;
    target_y += y;
    auto dx = (target_x - current_x) / PANNING_SPEED;
    auto dy = (target_y - current_y) / PANNING_SPEED;
    if(fabs(dx) < 0.001 && fabs(dy) < 0.001) {
      return;
    }
    current_x += dx + copysign(0.01, dx);
    current_y += dy + copysign(0.01, dy);
    camera->rotate(-dx, camera->up);
    camera->rotate(dy, glm::cross(camera->up, camera->dir));
  } else {
    target_x = current_x;
    target_y = current_y;
  }
}

void FPSController::handle_movement() {
  camera->move_forward(current_speed.z);
  camera->move_right(-current_speed.x);
  camera->translate(glm::vec3({0, 1, 0}) * current_speed.y);
  current_speed /= 1.2;
  if(glm::length(current_speed) < 0.01)
      current_speed = {0, 0, 0};
}


std::shared_ptr<Camera> FPSController::get_camera() {
  return camera;
}
