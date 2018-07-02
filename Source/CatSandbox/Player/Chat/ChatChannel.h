#pragma once

#include "ChatChannel.generated.h"

UENUM(BlueprintType)
enum class EChatChannel : uint8
{
	ECC_Global				UMETA(DisplayName = "World"),
	ECC_Say					UMETA(DisplayName = "Say"),
	ECC_Yell				UMETA(DisplayName = "Yell"),
	ECC_NPCSay				UMETA(DisplayName = "NPC Say")
};
