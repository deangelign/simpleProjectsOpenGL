varying vec3 f_color; 
uniform sampler2D mytexture; 
varying vec2 texCoords;

void main(void) { 
  gl_FragColor = texture2D(mytexture,texCoords); 
}
