#include "CatSandbox.h"
#include "ThreatTable.h"

void UThreatTable::ContributeThreat(AActor* FromWho, float ThreatValue)
{
	auto ThreatLevel = FindThreatLevel(FromWho);
	if (!ThreatLevel)
	{
		ThreatLevel = NewObject<UThreatLevel>();
		ThreatLevels.Add(ThreatLevel);
	}
	ThreatLevel->ThreatAmount += ThreatValue;
}

UThreatLevel * UThreatTable::FindThreatLevel(AActor * ForWhom)
{
	for (UThreatLevel* ThreatLevel : ThreatLevels)
	{
		if (ThreatLevel->FromWho == ForWhom)
		{
			return ThreatLevel;
		}
	}
	return nullptr;
}

UThreatLevel * UThreatTable::FindTopThreat()
{
	UThreatLevel* Top = nullptr;
	for (UThreatLevel* ThreatLevel : ThreatLevels)
	{
		if (!Top) { Top = ThreatLevel; }
		if (Top->ThreatAmount < ThreatLevel->ThreatAmount)
		{
			Top = ThreatLevel;
		}
	}
	return Top;
}

bool UThreatTable::HasThreatTargets()
{
	return ThreatLevels.Num() > 0;
}

void UThreatTable::ClearThreatTable()
{
	ThreatLevels.Empty();
}
