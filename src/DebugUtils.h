#include <stdlib.h>
#include <string>
#include <sstream>
#include <GLFW/glfw3.h>
#include <iostream>

inline int checkForGlError() {
  GLenum error; 
  if((error = glGetError()) > 0) {
    std::cout << "GL error " << error << ": " << gluErrorString(error) << "!" << std::endl;
    exit (EXIT_FAILURE);
  }
  return error;
}

inline int checkForGlErrorNoShut() {
  GLenum error = glGetError();
  std::cout << "GL error " << error << ": " << gluErrorString(error) << "!" << std::endl;
  return error;
}

template<class T>
char* toChar(T t) {
  std::ostringstream oss;
  oss << t;
  return oss.str().c_str();
}

inline double calcFPS(GLFWwindow* window, double theTimeInterval = 1.0, std::string theWindowTitle = "NONE") {
  static double t0Value       = glfwGetTime(); // Set the initial time to now
  static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
  static double fps           = 0.0;           // Set the initial FPS value to 0.0

  // Get the current time in seconds since the program started (non-static, so executed every time)
  double currentTime = glfwGetTime();

  // Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
  // Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
  if (theTimeInterval < 0.1) {
    theTimeInterval = 0.1;
  }
  if (theTimeInterval > 10.0) {
    theTimeInterval = 10.0;
  }

  // Calculate and display the FPS every specified time interval
  if ((currentTime - t0Value) > theTimeInterval) {
    // Calculate the FPS as the number of frames divided by the interval in seconds
    fps = (double)fpsFrameCount / (currentTime - t0Value);

    // If the user specified a window title to append the FPS value to...
    if (theWindowTitle != "NONE") {
      // Convert the fps value into a string using an output stringstream
      std::ostringstream stream;
      stream << fps;
      std::string fpsString = stream.str();

      // Append the FPS value to the window title details
      theWindowTitle += " | FPS: " + fpsString;

      // Convert the new window title to a c_str and set it
      const char* pszConstString = theWindowTitle.c_str();
      glfwSetWindowTitle(window, pszConstString);
    } else {
      // If the user didn't specify a window to append the FPS to then output the FPS to the console
      std::cout << "FPS: " << fps << std::endl;
    }

    // Reset the FPS frame counter and set the initial time to be now
    fpsFrameCount = 0;
    t0Value = glfwGetTime();
  } else {
    // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
    fpsFrameCount++;
  }

  // Return the current FPS - doesn't have to be used if you don't want it!
  return fps;
}
