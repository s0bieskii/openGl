#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform sampler2D textureMap2;
uniform sampler2D textureMap3;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l;
in vec4 v;
in vec2 iTexCoord0;

vec2 parallaxTexCoords(vec4 v, vec2 t, float h, float s)
{
	vec2 ti = -h*v.xy/s;
	float hi = -1/s;

	vec2 tc = t;
	float hc = 1;

	float ht = texture(textureMap2, tc).r;

	if(v.z <= 0){
		discard;
	}
	while(hc > ht)
	{
		tc = tc + ti;

		if(tc.x < 0 || tc.x > 1 || tc.y < 0 || tc.y > 1)
		{
			discard;
		}
		hc = hc + hi;

		ht = texture(textureMap2, tc).r;
		
	}

	vec2 tOc = tc - ti;
	float hOc = hc - hi;

	float hOt = texture(textureMap2, tOc).r;

	float x = (hOc - hOt)/(hOc-hOt-(hc - ht));

	vec2 tnc = (1 - x)* tOc + x * tc;

	return tnc;
}

void main(void) {

	vec4 ml = normalize(l);
	vec4 mv = normalize(v);

	vec2 tc = parallaxTexCoords(mv, iTexCoord0, 0.1, 500);

	vec4 mn = normalize(vec4(2*texture(textureMap1, tc).xyz-1,0));

	vec4 mr = reflect(-ml, mn);

	vec4 kd = texture(textureMap0, tc);
	vec4 ks = texture(textureMap3, iTexCoord0);

	//Obliczenie modelu oświetlenia

	float nl = clamp(dot(mn, ml), 0, 1);
	float rv = pow(clamp(dot(mr, mv), 0, 1),25);
	pixelColor= vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb*rv, 0);
}
