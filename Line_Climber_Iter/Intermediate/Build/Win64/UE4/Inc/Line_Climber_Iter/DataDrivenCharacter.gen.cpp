// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Line_Climber_Iter/DataDrivenCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDataDrivenCharacter() {}
// Cross Module References
	LINE_CLIMBER_ITER_API UClass* Z_Construct_UClass_ADataDrivenCharacter_NoRegister();
	LINE_CLIMBER_ITER_API UClass* Z_Construct_UClass_ADataDrivenCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Line_Climber_Iter();
// End Cross Module References
	void ADataDrivenCharacter::StaticRegisterNativesADataDrivenCharacter()
	{
	}
	UClass* Z_Construct_UClass_ADataDrivenCharacter_NoRegister()
	{
		return ADataDrivenCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ADataDrivenCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADataDrivenCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Line_Climber_Iter,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADataDrivenCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "DataDrivenCharacter.h" },
		{ "ModuleRelativePath", "DataDrivenCharacter.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADataDrivenCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADataDrivenCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADataDrivenCharacter_Statics::ClassParams = {
		&ADataDrivenCharacter::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ADataDrivenCharacter_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADataDrivenCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADataDrivenCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADataDrivenCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADataDrivenCharacter, 2229830516);
	template<> LINE_CLIMBER_ITER_API UClass* StaticClass<ADataDrivenCharacter>()
	{
		return ADataDrivenCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADataDrivenCharacter(Z_Construct_UClass_ADataDrivenCharacter, &ADataDrivenCharacter::StaticClass, TEXT("/Script/Line_Climber_Iter"), TEXT("ADataDrivenCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADataDrivenCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
