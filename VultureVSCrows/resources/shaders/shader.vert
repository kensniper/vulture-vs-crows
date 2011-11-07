varying vec4 verpos;

void main()
{
    gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
	verpos=gl_Position;
}
