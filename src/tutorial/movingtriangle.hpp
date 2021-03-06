#ifndef MOVINGTRIANGLE_HPP
#define MOVINGTRIANGLE_HPP

#include "tutorial.hpp"
#include "system.hpp"
#include <glad/glad.h>

class MovingTriangle : public Tutorial
{
public:
  MovingTriangle(Window* win);

  void update(ogl::seconds delta) override;

  void renderInternal() override;

private:
  GLuint mProgram;
  GLuint mBuffer;
  GLuint mVao;
  GLint mOffsetUniform;
  ogl::seconds mTime;
};

#endif // MOVINGTRIANGLE_HPP
