//in
attribute vec3 aPos;
attribute vec4 aColor;
//out
varying vec4 fColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    fColor = aColor;
}
