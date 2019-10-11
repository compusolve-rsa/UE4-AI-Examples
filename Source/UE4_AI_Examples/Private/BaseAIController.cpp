// © Ajit D'Monte


#include "BaseAIController.h"

#include "ExtendedPathFollowingComponent.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UExtendedPathFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
