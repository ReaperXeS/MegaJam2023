#include "ClanInterface.h"

TObjectPtr<UMaterialInstance> IClanInterface::GetMeshMaterialInstance()
{
	// Get the material instance from path
	switch (GetClan())
	{
		case EClan::Blue:
		{
			return  LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/TronRacing/Materials/MI_Tron_Blue.MI_Tron_Blue"));
		}
		case EClan::Green:
		{
			return LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/TronRacing/Materials/MI_Tron_Green.MI_Tron_Green"));
		}
		case EClan::Gold:
		{
			return LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/TronRacing/Materials/MI_Tron_Gold.MI_Tron_Gold"));
		}
		default:
			return LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/TronRacing/Materials/MI_Tron_Pink.MI_Tron_Pink"));
	}
}
