#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout(location=2) in vec2 aUV;

out vec3 FragPos;
out vec3 Normal;
out vec2 vUV;

uniform mat4 model;
uniform mat3 normalMatrix;

// TODO: Have this UBO in a separate file and include it in both shaders
layout(std140, binding = 0) uniform CameraUBO {
    mat4 uView;
    mat4 uProj;
    vec4 uEye;
};

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;

    Normal = normalize(normalMatrix * aNormal);
    vUV = aUV;

    gl_Position = uProj * uView * worldPos;
}