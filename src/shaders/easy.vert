#version 330 core
layout(location = 0) in vec3 aPos;   // 頂點座標
layout(location = 1) in vec3 aColor; // 頂點顏色

out vec3 FragColor;  // 傳遞給 Fragment Shader

uniform mat4 view;
uniform mat4 projection;

void main() {
    FragColor = aColor;  // 直接傳顏色
    gl_Position = projection * view * vec4(aPos, 1.0);
}