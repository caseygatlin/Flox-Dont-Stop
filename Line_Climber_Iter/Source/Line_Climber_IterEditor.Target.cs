// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Line_Climber_IterEditorTarget : TargetRules
{
	public Line_Climber_IterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Line_Climber_Iter" } );
	}
}
