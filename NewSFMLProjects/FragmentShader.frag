
uniform float x;
uniform float y;
uniform float s;

void main()
{
	vec2 pos = (gl_TexCoord[0].xy - 0.5f) * s - vec2(x, y);

	float cr = pos.x;
	float  ci = pos.y;

	float zr = 0.0f, zi = 0.0f;

	int nIter = 0;
	int iterations = 500;

	while (zr * zr + zi * zi < 4.0f && nIter <= iterations) {
		float tr = zr * zr - zi * zi + cr;
		zi = 2.0f * zr *zi + ci;
		zr = tr;
		nIter++;
	}

	float r;
	if (nIter <= iterations) {
		r = float(nIter) / float(iterations);
	} 
	else {
		r = 0.0f;
	}

	gl_FragColor = vec4(1.0f - pow(r, 0.1f), pow(1.0f - abs(r - 0.5f), 4.0f), pow(r, 0.2f), 1.0f);
}