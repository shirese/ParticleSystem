#version 410 core

layout(location = 0) in vec3 posAttr;
layout(location = 1) in vec3 colAttr;

out vec3 color;
uniform mat4 matrix;

void main() {
  color = colAttr;
  gl_Position = matrix * vec4(posAttr, 1.0);
}
