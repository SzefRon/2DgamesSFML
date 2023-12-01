uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel1 = texture2D(tex1, gl_TexCoord[0].xy);
    vec4 pixel2 = texture2D(tex2, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = mix(pixel1, pixel2, 0.5f);
}