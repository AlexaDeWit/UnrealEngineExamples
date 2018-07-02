#pragma once
#include "GameFramework/Actor.h"
#include "AAbstractCollisionTrigger.h"
#include "WaterTrigger.generated.h" //Needs to be last


UCLASS(Blueprintable)
class CATSANDBOX_API AWaterTrigger : public AAbstractCollisionTrigger
{
		GENERATED_BODY()

protected:
	//Functions inside the header, do not need to provide the class they are members of when defined lik this, as they are inside the brackets of the class definition itself.
	virtual void TriggerEffect(AActor* Other) override;

};