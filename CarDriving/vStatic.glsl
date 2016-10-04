attribute vec3 coord3d;
attribute vec2 texcoord;
varying vec2 f_texcoord;
uniform mat4 mv;
uniform mat4 projection;


void main(void) {
  gl_Position = projection * mv * vec4(coord3d, 1.0);
  f_texcoord = texcoord;
}
