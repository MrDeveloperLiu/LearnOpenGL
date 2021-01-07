//入参
attribute vec3 aPos;//位置
attribute vec3 aNormal;//法线
//出参
varying vec3 Normal;
varying vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
