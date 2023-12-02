uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec2 diffVec;
uniform float a;

void main()
{
    vec4 pixel;
    
    if (diffVec.y >= 0) {
        if ((gl_TexCoord[0].x - 0.5f) * a <= (gl_TexCoord[0].y - 0.5f)) {
            vec2 pos = 0.5f * vec2(gl_TexCoord[0].x - diffVec.x, gl_TexCoord[0].y - diffVec.y) + 0.25f;
            pixel = texture2D(tex2, pos);
        }
        else {
            vec2 pos = 0.5f * vec2(gl_TexCoord[0].x + diffVec.x, gl_TexCoord[0].y + diffVec.y) + 0.25f;
            pixel = texture2D(tex1, pos);
        }
    }
    else {
        if ((gl_TexCoord[0].x - 0.5f) * a >= (gl_TexCoord[0].y - 0.5f)) {
            vec2 pos = 0.5f * vec2(gl_TexCoord[0].x - diffVec.x, gl_TexCoord[0].y - diffVec.y) + 0.25f;
            pixel = texture2D(tex2, pos);
        }
        else {
            vec2 pos = 0.5f * vec2(gl_TexCoord[0].x + diffVec.x, gl_TexCoord[0].y + diffVec.y) + 0.25f;
            pixel = texture2D(tex1, pos);
        }
    }
    // multiply it by the color
    gl_FragColor = pixel;
}