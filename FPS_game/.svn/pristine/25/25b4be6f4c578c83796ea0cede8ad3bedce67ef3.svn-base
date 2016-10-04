attribute vec4 v_coord;
attribute vec3 v_normal;
attribute vec2 v_textCoord;

varying vec4 position;  // position of the vertex (and fragment) in world space
varying vec3 varyingNormalDirection;  // surface normal vector in world space
varying vec4 texCoords; // the texture coordinates
uniform mat4 m, v, p;
uniform mat3 m_3x3_inv_transp;

//varying vec2 texCoords01;
varying vec3 f_normal;
varying vec2 f_texcoord;

void main(){
	gl_Position = p * v *  m* v_coord;
	f_normal = v_normal;
	//f_texcoord = v_textCoord;
	varyingNormalDirection = normalize(m_3x3_inv_transp * v_normal);
	position = m * v_coord;
	texCoords = v_coord;
	f_texcoord = v_textCoord;
}
