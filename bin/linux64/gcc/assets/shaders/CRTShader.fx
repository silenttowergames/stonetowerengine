// This is largely an original shader, but with a bit of inspiration from the following:
// https://bit-hack.net/2014/07/17/retro-crt-shader/

int Width, Height;
float tmod;

Texture2D SpriteTexture;

sampler2D SpriteTextureSampler = sampler_state
{
	Texture = <SpriteTexture>;
};

struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR0;
	float2 TextureCoordinates : TEXCOORD0;
};

float4 MainPS(VertexShaderOutput input) : COLOR
{
	float xmod = 0;
    float2
		coords = input.TextureCoordinates,
		rc = float2(coords.x * Width, coords.y * Height)
	;
	
	if(rc.y % 1 >= 0.5)
	{
		coords.x += (0.5 / Width);
	}
	
	float4 c = tex2D(SpriteTextureSampler, coords) * input.Color * tmod;
	
	float Mult = 1.4;
	
	if(rc.y % 2 >= 1)
	{
		Mult = 0.7;
	}
	
	if(rc.x % 3 >= 2)
	{
		return float4(c.r * Mult, c.g * 0.5, c.b * 0.5, c.a);
	}
	
	if(rc.x % 3 >= 1)
	{
		return float4(c.r * 0.5, c.g * Mult, c.b * 0.5, c.a);
	}
	
	return float4(c.r * 0.5, c.g * 0.5, c.b * Mult, c.a);
}

technique SpriteDrawing
{
	pass P0
	{
		PixelShader = compile ps_3_0 MainPS();
	}
};
