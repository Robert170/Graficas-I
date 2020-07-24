//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

#define MAX_BONES 100

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer CBNeverChanges : register(b0)
{
	matrix mView;
};


cbuffer CBChangeOnResize : register(b1)
{
	matrix mProjection;
};

cbuffer CBChangesEveryFrame : register(b2)
{
	matrix mWorld;
	float4 vMeshColor;
	float4 vViewPos;
};

cbuffer CBLight : register(b3)
{
	float4 lightDir;
	float3 lightPointPos;
	float4 lightPointAtt;
};

cbuffer CBBones : register(b4)
{
	matrix Bones_CB[MAX_BONES];
};

struct VS_INPUT
{
	float3 msPos	: POSITION0;
	float2 texcoord : TEXCOORD0;
	int4 IDBone		: BLENDINDICES0;
	float4 Weights	: BLENDWEIGHT0;
};

struct PS_INPUT
{
	float4 Pos	: SV_POSITION;
	float2 Tex : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color	: COLOR0;
	
};

//Vertex shader

PS_INPUT vs_main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	matrix BoneTransform = mul(input.Weights.x, Bones_CB[input.IDBone.x]);
	BoneTransform += mul(input.Weights.y, Bones_CB[input.IDBone.y]);
	BoneTransform += mul(input.Weights.z, Bones_CB[input.IDBone.z]);
	BoneTransform += mul(input.Weights.w, Bones_CB[input.IDBone.w]);

	output.Pos = mul(BoneTransform, float4(input.msPos.xyz, 1.0));
	output.Pos = mul(output.Pos, mWorld);
	output.Pos = mul(output.Pos, mView);
	output.Pos = mul(output.Pos, mProjection);
	output.Tex = input.texcoord;

	return output;
}

//Pixel shader

float4 ps_main(PS_INPUT input) : SV_Target
{
	float4 color = (txDiffuse.Sample(samLinear, input.Tex) * vMeshColor);
	return color;
}