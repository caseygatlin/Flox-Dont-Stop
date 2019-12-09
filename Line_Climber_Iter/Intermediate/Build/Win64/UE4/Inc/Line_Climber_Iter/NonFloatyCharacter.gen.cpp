// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Line_Climber_Iter/NonFloatyCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNonFloatyCharacter() {}
// Cross Module References
	LINE_CLIMBER_ITER_API UClass* Z_Construct_UClass_ANonFloatyCharacter_NoRegister();
	LINE_CLIMBER_ITER_API UClass* Z_Construct_UClass_ANonFloatyCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Line_Climber_Iter();
// End Cross Module References
	void ANonFloatyCharacter::StaticRegisterNativesANonFloatyCharacter()
	{
	}
	UClass* Z_Construct_UClass_ANonFloatyCharacter_NoRegister()
	{
		return ANonFloatyCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ANonFloatyCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANonFloatyCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Line_Climber_Iter,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANonFloatyCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "NonFloatyCharacter.h" },
		{ "ModuleRelativePath", "NonFloatyCharacter.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANonFloatyCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANonFloatyCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ANonFloatyCharacter_Statics::ClassParams = {
		&ANonFloatyCharacter::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ANonFloatyCharacter_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ANonFloatyCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ANonFloatyCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ANonFloatyCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ANonFloatyCharacter, 866900886);
	template<> LINE_CLIMBER_ITER_API UClass* StaticClass<ANonFloatyCharacter>()
	{
		return ANonFloatyCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ANonFloatyCharacter(Z_Construct_UClass_ANonFloatyCharacter, &ANonFloatyCharacter::StaticClass, TEXT("/Script/Line_Climber_Iter"), TEXT("ANonFloatyCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANonFloatyCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
