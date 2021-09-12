// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/WJ_GameStateMgr.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWJ_GameStateMgr() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_GameStateMgr_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_GameStateMgr();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
// End Cross Module References
	void UWJ_GameStateMgr::StaticRegisterNativesUWJ_GameStateMgr()
	{
	}
	UClass* Z_Construct_UClass_UWJ_GameStateMgr_NoRegister()
	{
		return UWJ_GameStateMgr::StaticClass();
	}
	struct Z_Construct_UClass_UWJ_GameStateMgr_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UWJ_GameStateMgr_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UWJ_GameStateMgr_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "WJ_GameStateMgr.h" },
		{ "ModuleRelativePath", "public/WJ_GameStateMgr.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UWJ_GameStateMgr_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWJ_GameStateMgr>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UWJ_GameStateMgr_Statics::ClassParams = {
		&UWJ_GameStateMgr::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UWJ_GameStateMgr_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UWJ_GameStateMgr_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UWJ_GameStateMgr()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UWJ_GameStateMgr_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UWJ_GameStateMgr, 1208217971);
	template<> DEVOLYMPIC_API UClass* StaticClass<UWJ_GameStateMgr>()
	{
		return UWJ_GameStateMgr::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UWJ_GameStateMgr(Z_Construct_UClass_UWJ_GameStateMgr, &UWJ_GameStateMgr::StaticClass, TEXT("/Script/DevOlympic"), TEXT("UWJ_GameStateMgr"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UWJ_GameStateMgr);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
