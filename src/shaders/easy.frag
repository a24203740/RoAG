#version 330 core
in vec3 FragColor;
out vec4 color;

void main() {
    color = vec4(FragColor, 1.0); // 直接使用頂點顏色
}