// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/WJ_PingPongMgr.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWJ_PingPongMgr() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_PingPongMgr_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_PingPongMgr();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
// End Cross Module References
	void UWJ_PingPongMgr::StaticRegisterNativesUWJ_PingPongMgr()
	{
	}
	UClass* Z_Construct_UClass_UWJ_PingPongMgr_NoRegister()
	{
		return UWJ_PingPongMgr::StaticClass();
	}
	struct Z_Construct_UClass_UWJ_PingPongMgr_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UWJ_PingPongMgr_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UWJ_PingPongMgr_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "WJ_PingPongMgr.h" },
		{ "ModuleRelativePath", "public/WJ_PingPongMgr.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UWJ_PingPongMgr_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWJ_PingPongMgr>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UWJ_PingPongMgr_Statics::ClassParams = {
		&UWJ_PingPongMgr::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UWJ_PingPongMgr_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UWJ_PingPongMgr_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UWJ_PingPongMgr()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UWJ_PingPongMgr_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UWJ_PingPongMgr, 1288102338);
	template<> DEVOLYMPIC_API UClass* StaticClass<UWJ_PingPongMgr>()
	{
		return UWJ_PingPongMgr::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UWJ_PingPongMgr(Z_Construct_UClass_UWJ_PingPongMgr, &UWJ_PingPongMgr::StaticClass, TEXT("/Script/DevOlympic"), TEXT("UWJ_PingPongMgr"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UWJ_PingPongMgr);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
