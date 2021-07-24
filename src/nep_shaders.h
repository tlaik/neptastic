#pragma once

// Blur code adopted from here: https://www.shadertoy.com/view/XdfGDH
const char* nep_new_bloom_no_fxaa = "\
//#pragma	argument( O3 ; fastmath ; fastprecision )\n\
uniform	sampler2D s_TextureGlare : TEXUNIT0;\n\
uniform	sampler2D s_TextureBase0 : TEXUNIT1;\n\
uniform	float ContrastParam0;\n\
uniform	float ContrastParam1;\n\
uniform	float ContrastParam2;\n\
uniform	float ContrastParam3;\n\
uniform	float ContrastParam4;\n\
struct	InInfo { half2	Texcoord0	: TEXCOORD0; };\n\
float remap(float value, float inputMin, float inputMax, float outputMin, float outputMax) {\n\
	return (value - inputMin) * ((outputMax - outputMin) / (inputMax - inputMin)) + outputMin;}\n\
float normpdf(float x, float sigma) {\n\
	return 0.39894 * exp(-0.5 * x * x / (sigma * sigma)) / sigma;}\n\
half4	main( InInfo In ) : Color0\n\
{\n\
	float4 Col = tex2D(s_TextureBase0, In.Texcoord0);\n\
	float4 GlareCol = float4(0.5, 0.5, 0.5, 1);\n\
	int2 res = int2(1920, 1080); // Shouldn't be changed, it's only used as an aspect ratio\n\
	float blurScale = 3.0f;\n\
	int mSize = %d;\n\
	int kSize = (mSize-1)/2;\n\
	float kernel[11];\n\
	float3 final_colour = float3(0, 0, 0);\n\
	float sigma = %f;\n\
	float Z = 0.0;\n\
	for (int j = 0; j <= kSize; ++j) {\n\
		kernel[kSize + j] = kernel[kSize - j] = normpdf(j, sigma);}\n\
	for (int j = 0; j < mSize; ++j) {\n\
		Z += kernel[j];}\n\
	for (int i=-kSize; i <= kSize; ++i) {\n\
		for (int j = -kSize; j <= kSize; ++j) {\n\
			final_colour += kernel[kSize + j] * kernel[kSize + i] * tex2D(s_TextureBase0, In.Texcoord0.xy + (float2(i, j) / res.xy) * blurScale).rgb;}}\n\
	GlareCol.rgb = final_colour / (Z*Z);\n\
	GlareCol.rgb = pow(GlareCol.rgb, %f);\n\
	GlareCol.rgb *= %f;\n\
	Col = (Col + GlareCol) - (Col * GlareCol);\n\
	float pixelAvg = (Col.r+Col.g+Col.b)/3;\n\
	float pixles = 1-pixelAvg;\n\
	float contrast = remap(pixles, ContrastParam1, ContrastParam2, ContrastParam3/*min*/, ContrastParam4/*max*/);\n\
	if( 0<ContrastParam4 ){\n\
		Col.rgb -= ContrastParam0;\n\
		Col.rgb *= contrast;	\n\
		Col.rgb += ContrastParam0;\n\
		Col.g *= 1.02;\n\
		Col.b *= 1.01;\n\
	}\n\
	//return tex2D(s_TextureGlare, In.Texcoord0);\n\
	return float4( Col.rgb, 1.0 );}";

const char* nep_new_bloom_no_fxaa_rb1 = "\
//#pragma	argument( O3 ; fastmath ; fastprecision )\n\
uniform	sampler2D s_TextureGlare : TEXUNIT0;\n\
uniform	sampler2D s_TextureBase0 : TEXUNIT1;\n\
uniform	float ContrastParam0;\n\
uniform	float ContrastParam1;\n\
uniform	float ContrastParam2;\n\
uniform	float ContrastParam3;\n\
uniform	float ContrastParam4;\n\
struct	InInfo { half2	Texcoord0	: TEXCOORD0; };\n\
float remap(float value, float inputMin, float inputMax, float outputMin, float outputMax) {\n\
	return (value - inputMin) * ((outputMax - outputMin) / (inputMax - inputMin)) + outputMin;}\n\
float normpdf(float x, float sigma) {\n\
	return 0.39894 * exp(-0.5 * x * x / (sigma * sigma)) / sigma;}\n\
half4	main( InInfo In ) : Color0\n\
{\n\
	float4 Col = tex2D(s_TextureBase0, In.Texcoord0);\n\
	float4 GlareCol = float4(0.5, 0.5, 0.5, 1);\n\
	int2 res = int2(1920, 1080); // Shouldn't be changed, it's only used as an aspect ratio\n\
	float blurScale = 3.0f;\n\
	int mSize = %d;\n\
	int kSize = (mSize-1)/2;\n\
	float kernel[11];\n\
	float3 final_colour = float3(0, 0, 0);\n\
	float sigma = %f;\n\
	float Z = 0.0;\n\
	for (int j = 0; j <= kSize; ++j) {\n\
		kernel[kSize + j] = kernel[kSize - j] = normpdf(j, sigma);}\n\
	for (int j = 0; j < mSize; ++j) {\n\
		Z += kernel[j];}\n\
	for (int i=-kSize; i <= kSize; ++i) {\n\
		for (int j = -kSize; j <= kSize; ++j) {\n\
			final_colour += kernel[kSize + j] * kernel[kSize + i] * tex2D(s_TextureBase0, In.Texcoord0.xy + (float2(i, j) / res.xy) * blurScale).rgb;}}\n\
	GlareCol.rgb = final_colour / (Z*Z);\n\
	GlareCol.rgb = pow(GlareCol.rgb, %f);\n\
	GlareCol.rgb *= %f * 0.5f;\n\
	Col = (Col + GlareCol) - (Col * GlareCol);\n\
	float contrast = remap(ContrastParam0, ContrastParam1, ContrastParam2, ContrastParam3/*min*/, ContrastParam4/*max*/);\n\
	if( 0<ContrastParam4 ){\n\
		float pixelPow = (Col.r+Col.g+Col.b);\n\
		float pixelAvg = (Col.r + Col.g + Col.b) / 3;\n\
		Col.rgb -= 0.5;\n\
		Col.rgb *= contrast;\n\
		Col.rgb += 0.5;\n\
	}\n\
	//return float4(tex2D(s_TextureBase0, In.Texcoord0.xy).rgb, 1.0);\n\
	return float4( Col.r, Col.g, Col.b, 1.0 );}";

const char* nep_outlines_items = "\
	uniform sampler2D albedoTex1:TEXUNIT0;\
	struct TEFIn{float4 Color:COLOR0;float4 TexCoord:TEXCOORD0;};\
	float4 main(TEFIn fin):COLOR0{return float4(0, 0, 0, %f);}";

const char* nep_outlines_girls = "\
	uniform sampler2D at1:TEXUNIT0;\
	uniform sampler2D tst:TEXUNIT4;\
	uniform float2 ofs;\
	struct TEFIn{float4 Color:COLOR0;float4 TexCoord:TEXCOORD0;};\
	float4 main(TEFIn fin):COLOR0{float4 col=tex2D(tst, ofs);col.a=fin.Color.a*%f*2.5f;return col;}";

const char* nep_outlines_flat_girls = "\
	uniform sampler2D at1:TEXUNIT0;\
	uniform sampler2D tst:TEXUNIT4;\
	uniform float2 ofs;\
	struct TEFIn{float4 Color:COLOR0;float4 TexCoord:TEXCOORD0;};\
	float4 main(TEFIn fin):COLOR0{return float4(0, 0, 0, %f);}";

const char* nep_shadow = "\
#pragma	argument( O3 ; fastmath ; fastprecision )\n\
uniform	float2	TexcoordOffset;\n\
struct	InInfo {\n\
	float2	Position : POSITION;\n\
	float2	Texcoord : TEXCOORD0;};\n\
struct	OutInfo {\n\
	float4	Position : POSITION0;\n\
	float2	Texcoord0 : TEXCOORD0;\n\
	float2	Texcoord1 : TEXCOORD1;\n\
	float2	Texcoord2 : TEXCOORD2;\n\
	float2	Texcoord3 : TEXCOORD3;\n\
	float2	Texcoord4 : TEXCOORD4;};\n\
OutInfo main(InInfo In) {\n\
	float ofsScale = %f;\n\
	float2 TexCoordOffset1 = TexcoordOffset * ofsScale;\n\
	float2 TexCoordOffset2 = TexcoordOffset * 2.0f * ofsScale;\n\
	OutInfo	Out;\n\
	Out.Position = float4(In.Position.xy, 1.0f, 1.0f);\n\
	Out.Texcoord0 = In.Texcoord - TexCoordOffset2;\n\
	Out.Texcoord1 = In.Texcoord - TexCoordOffset1;\n\
	Out.Texcoord2 = In.Texcoord;\n\
	Out.Texcoord3 = In.Texcoord + TexCoordOffset1;\n\
	Out.Texcoord4 = In.Texcoord + TexCoordOffset2;\n\
	return	Out;}";

const char* nep_shadow_rb1 = "\
	#pragma	argument( O3 ; fastmath ; fastprecision )\n\
	uniform	float2	TexcoordOffset;\n\
	struct	InInfo {\n\
		float2	Position	: POSITION;\n\
		float2	Texcoord	: TEXCOORD0;\n\
	};\n\
	struct	OutInfo {\n\
		float4	Position	: POSITION0;\n\
		float2	Texcoord0	: TEXCOORD0;	//	- 3\n\
		float2	Texcoord1	: TEXCOORD1;	//	- 2\n\
		float2	Texcoord2	: TEXCOORD2;	//	- 1\n\
		float2	Texcoord3	: TEXCOORD3;	//	  0\n\
		float2	Texcoord4	: TEXCOORD4;	//	+ 1\n\
		float2	Texcoord5	: TEXCOORD5;	//	+ 2\n\
		float2	Texcoord6	: TEXCOORD6;  	//	+ 3\n\
	};\n\
	OutInfo main( InInfo In ) {\n\
	float ofsScale = %f;\n\
	float2 TexCoordOffset1 = TexcoordOffset * ofsScale;\n\
	float2 TexCoordOffset2 = TexcoordOffset * 2.0f * ofsScale;\n\
	OutInfo	Out;\n\
	Out.Position  = float4( In.Position.xy, 1.0f, 1.0f );\n\
	Out.Texcoord0 = In.Texcoord - TexCoordOffset2;\n\
	Out.Texcoord1 = In.Texcoord - TexCoordOffset1;\n\
	Out.Texcoord2 = In.Texcoord;\n\
	Out.Texcoord3 = In.Texcoord + TexCoordOffset1;\n\
	Out.Texcoord4 = In.Texcoord + TexCoordOffset2;\n\
	return	Out;}";