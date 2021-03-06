// © Ajit D'Monte


#include "ExtendedPathFollowingComponent.h"
#include "NavMesh/RecastNavMesh.h"

#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(ExtendedPathFollowing);

void UExtendedPathFollowingComponent::FollowPathSegment(float DeltaTime)
{
	//Pointer Safety Checks
	if (MovementComp == NULL || !Path.IsValid())
	{
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Use Jump/Fall Pathing?
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (Path->IsPartial()) //AI could not reach player, try using jump pathing!
	{
		/*FNavLocation OutLocation;
		FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->ProjectPointToNavigation(Path->GetEndLocation(), OutLocation);
		DrawDebugSphere(
			GetWorld(),
			Path->GetEndLocation(),
			24,
			32,
			FColor(255, 0, 0),
			false,
			5.
		);*/
		//UE_LOG(ExtendedPathFollowing, Warning, TEXT("Partial path!,  %s"), *Path->GetEndLocation().ToString());
		//return;
	
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Proceed normally (no jump pathing)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Super::FollowPathSegment(DeltaTime);
}

//Rama's UE4 Nav code to get all the nav polys!
bool UExtendedPathFollowingComponent::NavPoly_GetAllPolys(TArray<NavNodeRef>& Polys)
{
	if (!MovementComp) return false;
	//~~~~~~~~~~~~~~~~~~

	//Get Nav Data
	const ANavigationData* NavData = GetNavData();

	const ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>(NavData);
	if (!NavMesh)
	{
		return false;
	}

	TArray<FNavPoly> EachPolys;
	for (int32 v = 0; v < NavMesh->GetNavMeshTilesCount(); v++)
	{

		//CHECK IS VALID FIRST OR WILL CRASH!!! 
	   //     256 entries but only few are valid!
		// use continue in case the valid polys are not stored sequentially
		if (!TileIsValid(NavMesh, v))
		{
			continue;
		}

		NavMesh->GetPolysInTile(v, EachPolys);
	}


	//Add them all!
	for (int32 v = 0; v < EachPolys.Num(); v++)
	{
		Polys.Add(EachPolys[v].Ref);
	}
	return true;
}