uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec2 diffVec;

void main()
{
    // lookup the pixel in the texture
    vec2 pos1 = vec2(gl_TexCoord[0].x + diffVec.x, gl_TexCoord[0].y + diffVec.y);
    vec2 pos2 = vec2(gl_TexCoord[0].x - diffVec.x, gl_TexCoord[0].y - diffVec.y);
    vec4 pixel1 = texture2D(tex1, pos1);
    vec4 pixel2 = texture2D(tex2, pos2);

    // multiply it by the color
    gl_FragColor = mix(pixel1, pixel2, 0.5f);
}