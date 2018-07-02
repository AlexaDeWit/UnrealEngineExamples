#pragma once

#include "GameFramework/Actor.h"
#include "AAbstractCollisionTrigger.generated.h" //Needs to be last

UCLASS(abstract)
class CATSANDBOX_API AAbstractCollisionTrigger : public AActor
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxTrigger;

public:

	AAbstractCollisionTrigger();

	UFUNCTION(BlueprintCallable, Category = "Delegates")
		void OnBeginTriggerOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//protected functions are only accessible by the class that contains them, or derived classes(subclasses, such as the watertrigger)
protected:
	//virtual functions are possible to override in a derived class, meaning that the derived class will Replace the behaviour completely.
	//if you want both functions' effects to apply, that is possible too, but it's a bit weird in c++, so better explained in person.
	virtual void TriggerEffect(AActor* Other);
};