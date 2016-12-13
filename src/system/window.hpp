#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "log.hpp"
#include <utility>

class Tutorial;

class Window
{
public:
  virtual ~Window() = 0;

  virtual void setCloseCallback(void (*callback)(Window*)) = 0;

  virtual void setFramebufferResizeCallback(void (*callback)(Window*, int w, int h)) = 0;

  virtual void makeContextCurrent() = 0;

  virtual void setSwapInterval(int interval) = 0;

  virtual void swapBuffers() = 0;

  virtual std::pair<int, int> getSize() = 0;

  virtual std::pair<int, int> getFramebufferSize() = 0;

  void setTutorial(Tutorial* tutorial)
  {
    if (mTutorial) {
      Log::error("Window: Tutorial can be set only once.");
    }
    else {
      mTutorial = tutorial;
    }
  }

  Tutorial* getTutorial() { return mTutorial; }

private:
  Tutorial* mTutorial = nullptr;
};

inline Window::~Window() {}

#endif // WINDOW_HPP
