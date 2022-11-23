// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlooOpenXRBPWrapper.h"


//UBlooOpenXRBPWrapper::UBlooOpenXRBPWrapper(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//}

void UBlooOpenXRBPWrapper::SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->SetDataSource(he, amplitude, freq, loopCount, interval, handShank);
}

void UBlooOpenXRBPWrapper::SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->SetCustomDataSource(amplitude, freq, duration, loopCount, interval, handShank);
}

void UBlooOpenXRBPWrapper::PrepareHaptic(int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->PrepareHaptic(handShank);
}

void UBlooOpenXRBPWrapper::StartHaptic(int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->StartHaptic(handShank);
}

void UBlooOpenXRBPWrapper::PauseHaptic(int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->PauseHaptic(handShank);
}

void UBlooOpenXRBPWrapper::StopHaptic(int handShank) 
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->PrepareHaptic(handShank);
}

void UBlooOpenXRBPWrapper::UpdateHaptic(int intensity, int freq, int interval, int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->StopHaptic(handShank);
}

void UBlooOpenXRBPWrapper::SeekTo(int millSeconds, int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->SeekTo(millSeconds, handShank);
}

bool UBlooOpenXRBPWrapper::IsPlaying(int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->IsPlaying(handShank);
}

int32 UBlooOpenXRBPWrapper::GetDuration(int handShank)
{
	IBlooOpenXRHMDPlugin* Instance = IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance();
	if (Instance == nullptr)
	{
		return 0;
	}

	return Instance->GetDuration(handShank);
}