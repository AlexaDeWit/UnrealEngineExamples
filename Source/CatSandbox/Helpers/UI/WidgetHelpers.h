#pragma once

#include "Object.h"
#include "WidgetHelpers.generated.h"

UCLASS(BlueprintType)
class CATSANDBOX_API UWidgetHelpers : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpers")
	static UTexture2D* ForceResolveAsset(TAssetPtr<UTexture2D> AssetPointer)
	{
		if (AssetPointer.IsValid())
		{
			return AssetPointer.Get();
		}
		else
		{
			return AssetPointer.LoadSynchronous();
		}
	}
};
