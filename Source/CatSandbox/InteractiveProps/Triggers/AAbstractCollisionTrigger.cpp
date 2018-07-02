
#include "CatSandbox.h"
#include "AAbstractCollisionTrigger.h"

AAbstractCollisionTrigger::AAbstractCollisionTrigger()
{
	//Setups up root box/cube
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetupAttachment(RootComponent);
	BoxTrigger->InitBoxExtent(FVector(250.0f, 250.0f, 250.0f));
	BoxTrigger->SetCollisionProfileName(TEXT("Pawn"));
	//Bind the overlap event of the component
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAbstractCollisionTrigger::OnBeginTriggerOverlap);
}

void AAbstractCollisionTrigger::OnBeginTriggerOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Because this function does not take the form of ClassName::Function, it will call the function on the current instance of the class.
	//So the actor that owns the function will call its own implementation.
	//And overrides will also be in effect, meaning the function call will be the last override in the inheritance chain
	TriggerEffect(OtherActor);
}

void AAbstractCollisionTrigger::TriggerEffect(AActor* Other) {

}