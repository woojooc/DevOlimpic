// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/VRGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVRGameModeBase() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_AVRGameModeBase_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_AVRGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_GameStateMgr_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_UWJ_PingPongMgr_NoRegister();
// End Cross Module References
	void AVRGameModeBase::StaticRegisterNativesAVRGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AVRGameModeBase_NoRegister()
	{
		return AVRGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AVRGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_gameStateMgr_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_gameStateMgr;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_pingpongStateMgr_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_pingpongStateMgr;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AVRGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "VRGameModeBase.h" },
		{ "ModuleRelativePath", "public/VRGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_gameStateMgr_MetaData[] = {
		{ "Category", "Components" },
		{ "Comment", "// # ???? ??????\xc6\xae\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/VRGameModeBase.h" },
		{ "ToolTip", "# ???? ??????\xc6\xae" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_gameStateMgr = { "gameStateMgr", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AVRGameModeBase, gameStateMgr), Z_Construct_UClass_UWJ_GameStateMgr_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_gameStateMgr_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_gameStateMgr_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_pingpongStateMgr_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/VRGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_pingpongStateMgr = { "pingpongStateMgr", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AVRGameModeBase, pingpongStateMgr), Z_Construct_UClass_UWJ_PingPongMgr_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_pingpongStateMgr_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_pingpongStateMgr_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AVRGameModeBase_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_gameStateMgr,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRGameModeBase_Statics::NewProp_pingpongStateMgr,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AVRGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AVRGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AVRGameModeBase_Statics::ClassParams = {
		&AVRGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AVRGameModeBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AVRGameModeBase_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AVRGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AVRGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AVRGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AVRGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AVRGameModeBase, 3371932439);
	template<> DEVOLYMPIC_API UClass* StaticClass<AVRGameModeBase>()
	{
		return AVRGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AVRGameModeBase(Z_Construct_UClass_AVRGameModeBase, &AVRGameModeBase::StaticClass, TEXT("/Script/DevOlympic"), TEXT("AVRGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AVRGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
