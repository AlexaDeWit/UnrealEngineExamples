// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class CatSandbox : ModuleRules
{
	public CatSandbox(ReadOnlyTargetRules Target) : base(Target)
	{

    PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "HTTP", "AIModule", "HeadMountedDisplay", "Networking",  "Sockets" });
    PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "HTTP", "Json", "JsonUtilities"});

  }
}
