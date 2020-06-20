//Siempre tenerlas excepto si es un gbuffer 
Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );



cbuffer cbNeverChanges : register(b0)
{
  matrix mView;
};

cbuffer cbChangeOnResize : register(b1)
{
   matrix mProjection;
};

cbuffer cbChangesEveryFrame : register(b2)
{
	matrix mWorld;
	
	float4 vMeshColor;
};

cbuffer CBLight : register(b3)
{
	float4 lightDir;
};

/**
*Input layout
*/
struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 wsNormal : NORMAL0;
	float2 Tex : TEXCOORD0;
};
/**
*Output layout
*/

//struct VS_OUTPUT
//{
//    
//    float4 psPos: SV_POSITION0;
//	float3 wsNormal : NORMAL0;
//};

/**
*Output layout
*/
//struct PS_OUTPUT
//{
//    
//};

/**
*Input layout
*/
struct PS_INPUT
{
	float4 Pos :SV_POSITION;
    float3 wsNormal : NORMAL0;
	float2 Tex : TEXCOORD0;
};

PS_INPUT vs_main(VS_INPUT Input)
{
	PS_INPUT Output;

	Output.Pos = mul(Input.Pos, mWorld);

	Output.Pos = mul(Output.Pos, mView);

	Output.Pos = mul(Output.Pos, mProjection);

	Output.Tex = Input.Tex;

	Output.wsNormal = mul(Input.wsNormal, mWorld);

    return Output;

}


float4 ps_main(PS_INPUT Input):SV_Target
{
	float4 color;

    float3 light = normalize(-lightDir.xyz);

    float NdL = dot(Input.wsNormal.xyz, light);

    color = ((txDiffuse.Sample(samLinear, Input.Tex) * vMeshColor) * NdL) ;
	
    return  color;
}








