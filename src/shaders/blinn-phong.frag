#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 ViewPos;

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


void main()
{
  // TODO: change to uniform
  float gloss = 5.0; 
  vec3 lightDir = light.direction;

  if (light.mode == 1) // point light
  {
    lightDir = normalize(light.position - FragPos);
  }
  float ambientStrength = 0.3;
  vec4 ambient = vec4(ambientStrength * light.ambient , 1.0);
  
  vec3 norm = normalize(Normal);
  float diff = max(dot(norm, lightDir), 0.0);
  vec4 diffuse = vec4(diff * light.diffuse, 1.0);

  float specularStrength = 0.8;
  vec3 viewDir = normalize(ViewPos - FragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(norm, halfwayDir), 0.0), gloss);
  vec4 specular = vec4(specularStrength * spec * light.specular, 1.0);

  vec4 ObjectColor = texture(ourTexture, TexCoord);

  vec4 result = (ambient + diffuse + specular) * ObjectColor;
  FragColor = result;
}
