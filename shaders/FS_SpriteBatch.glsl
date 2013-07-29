#version 130

uniform sampler2D texture;

in vec2 v_texcoord;
in vec4 v_color;

void main()
{
    gl_FragColor = v_color * texture2D(texture, v_texcoord);
}
