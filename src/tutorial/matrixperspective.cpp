#include "matrixperspective.hpp"
#include "primitives.hpp"
#include "shader.hpp"
#include "util.hpp"
#include "transform.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>


MatrixPerspective::MatrixPerspective(Window* win) :
  Tutorial(win),
  mProgram(0),
  mBuffer(0),
  mVao(0),
  mProjMatUniform(-1)
{
  glGenBuffers(1, &mBuffer);

  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ogl::perspectivePrism), ogl::perspectivePrism, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  mProgram = ogl::makePorgram({
                                ogl::Shader(GL_VERTEX_SHADER, "shaders/matrixperspective.vert"),
                                ogl::Shader(GL_FRAGMENT_SHADER, "shaders/colored-triangle.frag")
                              });

  GLint offsetUniform = glGetUniformLocation(mProgram, "offset");
  mProjMatUniform = glGetUniformLocation(mProgram, "projectionMatrix");

  glUseProgram(mProgram);

  glUniform2f(offsetUniform, 0.5f, 0.5f);

  OGL_CHECK_ERROR();
  glUseProgram(0);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  glGenVertexArrays(1, &mVao);
}

void MatrixPerspective::renderInternal()
{
  glUseProgram(mProgram);

  glBindVertexArray(mVao);

  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  // Geometry
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  // Colors
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(ogl::perspectivePrism) / 2));
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

void MatrixPerspective::framebufferSizeChanged(int w, int h)
{
  glUseProgram(mProgram);
  glUniformMatrix4fv(mProjMatUniform, 1, GL_FALSE, glm::value_ptr(ogl::makeProjectionMat(-1.0f, -3.0f, 1.0, static_cast<float>(w)/h)));
  glUseProgram(0);

  glViewport(0, 0, w, h);
}
