#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
// in vec4 FragPosLightSpace;

uniform sampler2D ourTexture;
uniform sampler2D dirShadowMap;
uniform samplerCube pointShadowMap;

uniform vec3 ViewPos;
uniform float farPlane;

struct light_t
{
  vec3 position;
  vec3 direction;
  int mode;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform light_t light;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 norm, vec3 lightDir)
{
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5 + 0.5; // [0, 1] range
  float closestDepth = texture(dirShadowMap, projCoords.xy).r; 
  float currentDepth = projCoords.z;
  float bias = max(0.001 * (1.0 - dot(norm, lightDir)), 0.0005);
  float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;  
  return shadow;
}  

float PointShadowCalculation(vec3 FragPos, vec3 lightPos) {
    vec3 fragToLight = FragPos - lightPos;
    float closestDepth = texture(pointShadowMap, fragToLight).r;
    closestDepth *= farPlane;
    float currentDepth = length(fragToLight);
    float bias = 0.05; 
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}


void main()
{
  // TODO: change to uniform
  float gloss = 2.0; 
  // uniform: light to frag
  // what we want: frag to light
  vec3 lightDir = -light.direction;

  if (light.mode == 1) // point light
  {
    lightDir = normalize(light.position - FragPos);
  }
  float ambientStrength = 0.2;
  vec3 ambient = ambientStrength * light.ambient;
  
  vec3 norm = normalize(Normal);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * light.diffuse;


  float specularStrength = 0.7;
  vec3 viewDir = normalize(ViewPos - FragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(norm, halfwayDir), 0.0), gloss);
  vec3 specular = specularStrength * spec * light.specular;

  // float shadow = ShadowCalculation(FragPosLightSpace, norm, lightDir);
  float shadow = PointShadowCalculation(FragPos, light.position);
  vec4 lighting = vec4(((1.0 - shadow) * (diffuse + specular)) + ambient, 1.0);

  vec4 ObjectColor = texture(ourTexture, TexCoord);

  vec4 result = lighting * ObjectColor;
  // vec4 result = (ambient + diffuse + specular) * ObjectColor;
  FragColor = result;
}
