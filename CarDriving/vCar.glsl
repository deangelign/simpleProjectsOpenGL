attribute vec3 coord3d;
attribute vec2 vtexcoords;
uniform vec3 Kd;
uniform mat4 mv;
uniform mat4 projection;
varying vec3 f_color;
varying vec2 texCoords;

void main(void) {
  gl_Position = projection* mv * vec4(coord3d, 1.0);
  texCoords=vtexcoords;
  f_color = Kd;
}
