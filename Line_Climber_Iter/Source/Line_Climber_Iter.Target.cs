// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Line_Climber_IterTarget : TargetRules
{
	public Line_Climber_IterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Line_Climber_Iter" } );
	}
}
