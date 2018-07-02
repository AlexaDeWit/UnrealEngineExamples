
#include "CatSandbox.h"
#include "AAbstractCollisionTrigger.h"
#include "Character/AbstractCreature.h"
#include "WaterTrigger.h"


//Functions in the cpp file must provide the class for which they are members, ie... ClassName::FunctionName(Function Parameters)
void AWaterTrigger::TriggerEffect(AActor* Other){
	auto otherCreature = Cast<AAbstractCreature>(Other); //Ensure that only abstract creatures, the base type for all "creatures", including players, is affected
	if (otherCreature) { //check that the cast was successful.
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Creature just overlapped watertrigger and should now be swimming");
		otherCreature->ChangeMovementMode(MOVE_Swimming);
	}
}