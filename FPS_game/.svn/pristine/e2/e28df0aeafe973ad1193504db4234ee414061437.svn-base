/**
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * Contributors: Martin Kraus, Sylvain Beucler
 */
 
 //I have modifeid the file a little bit. For this reason, I didnt put it in folder "external_files" 
 
varying vec4 position;  // position of the vertex (and fragment) in world space
varying vec3 varyingNormalDirection;  // surface normal vector in world space
uniform mat4 v_inv;
uniform sampler2D mytexture;
uniform float alpha;
varying vec4 texCoords;
uniform vec3 overrideColor;


struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};
const int numberOfLights = 2;
lightSource lights[numberOfLights];
lightSource light0 = lightSource(
  vec4(0.0,  10.0,  0.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  0.0, 2.0, 0.0,
  180.0, 0.0,
  vec3(0.0, 0.0, 0.0)
);
lightSource light1 = lightSource(
    vec4(-50.0, 19.0,  50.0, 1.0),
    vec4(1.0,  1.0,  1.0, 1.0),
    vec4(0.1,  0.1,  0.1, 1.0),
    0.0, 0.05, 0.001,
    120.0, 10.0,
    vec3(0.0, 1.0, 0.0)
);



vec4 scene_ambient = vec4(0.05, 0.05, 0.05, 1.0);

struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};
material frontMaterial = material(
  vec4(0.2, 0.2, 0.2, 1.0),
  vec4(1.0, 0.8, 0.8, 1.0),
  vec4(1.0, 1.0, 1.0, 1.0),
  5.0
);

void main()
{
  lights[0] = light0;
  lights[1] = light1;
  //lights[2] = light2;
  

  vec3 normalDirection = normalize(varyingNormalDirection);
  vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - position));
  vec3 lightDirection;
  float attenuation;
  
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                (asin(texCoords.z) / 3.1415926 + 0.5));

  
  vec4 textureColor =  vec4(overrideColor,1.0)*texture2D(mytexture, longitudeLatitude);
  
  // initialize total lighting with ambient lighting
  vec3 totalLighting = vec3(scene_ambient) * vec3(textureColor);
  
  for (int index = 0; index < numberOfLights; index++) // for all light sources
    {
      if (0.0 == lights[index].position.w) // directional light?
	{
	  attenuation = 1.0; // no attenuation
	  lightDirection = normalize(vec3(lights[index].position));
	} 
      else // point light or spotlight (or other kind of light) 
	{
	  vec3 positionToLightSource = vec3(lights[index].position - position);
	  float distance = length(positionToLightSource);
	  lightDirection = normalize(positionToLightSource);
	  
	  
	  attenuation = 1.0 / (lights[index].constantAttenuation
			       + lights[index].linearAttenuation * distance
			       + lights[index].quadraticAttenuation * distance * distance);
	 
	  if (lights[index].spotCutoff <= 90.0) // spotlight?
	    {
	      float clampedCosine = max(0.0, dot(-lightDirection, normalize(lights[index].spotDirection)));
	      if (clampedCosine < cos(radians(lights[index].spotCutoff))) // outside of spotlight cone?
		{
		  attenuation = 1.0;
		}
	      else
		{
		  attenuation = attenuation * pow(clampedCosine, lights[index].spotExponent);   
		}
	    }
	}
      
      vec3 diffuseReflection = attenuation 
	* vec3(lights[index].diffuse) * vec3(textureColor)
	* max(1.0, dot(normalDirection, lightDirection));
      
      vec3 specularReflection;
      if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
	{
	  specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
	}
      else // light source on the right side
	{
	  specularReflection = attenuation * vec3(lights[index].specular) * vec3(frontMaterial.specular)
	    * pow(max(1.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
	 
	}

      totalLighting = totalLighting + diffuseReflection + specularReflection;
    }
  
  gl_FragColor = vec4(totalLighting, alpha);
}
