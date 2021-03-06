#ifndef MANUALPERSPECTIVE_HPP
#define MANUALPERSPECTIVE_HPP

#include "tutorial.hpp"
#include <glad/glad.h>

class ManualPerspective : public Tutorial
{
public:
  ManualPerspective(Window* win);

  void renderInternal() override;

private:
  GLuint mProgram;
  GLuint mBuffer;
  GLuint mVao;
};

#endif // MANUALPERSPECTIVE_HPP
