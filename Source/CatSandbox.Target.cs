// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CatSandboxTarget : TargetRules
{
	public CatSandboxTarget(TargetInfo Target) : base(Target)
	{
    //Not: the file built for linux is libUE4Editor-CatSandbox.so
		bForceEnableExceptions = true;
		bForceEnableRTTI = true;
		Type = TargetType.Game;
		ExtraModuleNames.Add("CatSandbox");
	}
}
