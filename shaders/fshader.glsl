#version 130


uniform sampler2D texture;
out vec4 FragColor;
in vec2 v_texcoord;


void main()
{
    gl_FragColor = texture2D(texture, v_texcoord);
}
