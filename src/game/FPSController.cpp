#include "FPSController.hpp"

FPSController::FPSController():
  camera(std::make_shared<Camera>())
{
  Input::on(Actions::Forward, [&]() {
    camera->move_forward(step);
  });

  Input::on(Actions::Backward, [&]() {
    camera->move_forward(-step);
  });

  Input::on(Actions::Left, [&]() {
    camera->move_right(-step);
  });

  Input::on(Actions::Right, [&]() {
    camera->move_right(step);
  });

  Input::on(Actions::Up, [&]() {
    camera->translate({0, step, 0});
  });

  Input::on(Actions::Down, [&]() {
    camera->translate({0, -step, 0});
  });

  Input::on_scroll([&](double x_offset, double y_offset) {
      step = fmax(0.01f, fmin(step * pow(1.5, y_offset), 5));
  });

  Input::on(GLFW_KEY_Q, [&] {
      step = fmax(0.01f, fmin(step * pow(1.5, -1), 5));
  }, false);

  Input::on(GLFW_KEY_E, [&] {
      step = fmax(0.01f, fmin(step * pow(1.5, 1), 5));
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

}


std::shared_ptr<Camera> FPSController::get_camera() {
  return camera;
}
