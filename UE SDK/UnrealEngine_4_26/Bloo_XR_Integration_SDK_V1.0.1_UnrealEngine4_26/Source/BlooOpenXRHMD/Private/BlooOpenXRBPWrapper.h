// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "IBlooOpenXRHMDPlugin.h"
#include "BlooOpenXRBPWrapper.generated.h"



UCLASS()
class BLOOOPENXRHMD_API UBlooOpenXRBPWrapper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//GENERATED_UCLASS_BODY()
	//UBlooOpenXRBPWrapper(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void PrepareHaptic(int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void StartHaptic(int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void PauseHaptic(int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void StopHaptic(int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void UpdateHaptic(int intensity, int freq, int interval, int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static void SeekTo(int millSeconds, int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static bool IsPlaying(int handShank);

	UFUNCTION(BlueprintCallable, Category = "BlooOpenXR")
	static int32 GetDuration(int handShank);
};