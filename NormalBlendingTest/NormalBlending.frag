uniform sampler2D normals1;
uniform sampler2D normals2;

void main()
{
	vec2 pixelPos = gl_TexCoord[0].xy;
    vec4 n1 = 2.0f * texture2D(normals1, pixelPos) - vec4(1.0f);
	vec4 n2 = 2.0f * texture2D(normals2, pixelPos) - vec4(1.0f);

	vec3 N1 = n1.z > 0.001f ? n1.xyz / n1.z : vec3(0.0f, 0.0f, 1.0f);
	vec3 N2 = n2.z > 0.001f ? n2.xyz / n2.z : vec3(0.0f, 0.0f, 1.0f);

	vec3 N = N1 + N2 - vec3(0,0,1);
	N = normalize(N);
	N = N / 2.0f + vec3(0.5f);

	gl_FragColor = vec4(N, 1);
}