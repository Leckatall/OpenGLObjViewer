#version 450 core
out vec4 FragColor;

in vec3 Normal;   // world-space
in vec3 FragPos;  // world-space

uniform vec3 lightPos;    // world-space
uniform vec3 lightColor;
uniform vec3 objectColor;

// Shared camera data via UBO at binding = 0
layout(std140, binding = 0) uniform CameraUBO {
    mat4 uView;
    mat4 uProj;
    vec4 uEye; // world-space camera position (xyz used)
};

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.7;
    vec3 viewDir = normalize(uEye.xyz - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}