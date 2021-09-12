// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/WJ_GameObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWJ_GameObject() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_AWJ_GameObject_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_AWJ_GameObject();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
	DEVOLYMPIC_API UEnum* Z_Construct_UEnum_DevOlympic_EGameType();
// End Cross Module References
	void AWJ_GameObject::StaticRegisterNativesAWJ_GameObject()
	{
	}
	UClass* Z_Construct_UClass_AWJ_GameObject_NoRegister()
	{
		return AWJ_GameObject::StaticClass();
	}
	struct Z_Construct_UClass_AWJ_GameObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_gameType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_gameType_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_gameType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWJ_GameObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWJ_GameObject_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "WJ_GameObject.h" },
		{ "ModuleRelativePath", "public/WJ_GameObject.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType_MetaData[] = {
		{ "Category", "GameType" },
		{ "ModuleRelativePath", "public/WJ_GameObject.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType = { "gameType", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWJ_GameObject, gameType), Z_Construct_UEnum_DevOlympic_EGameType, METADATA_PARAMS(Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWJ_GameObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWJ_GameObject_Statics::NewProp_gameType,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWJ_GameObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWJ_GameObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AWJ_GameObject_Statics::ClassParams = {
		&AWJ_GameObject::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWJ_GameObject_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWJ_GameObject_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AWJ_GameObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AWJ_GameObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AWJ_GameObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AWJ_GameObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AWJ_GameObject, 471145834);
	template<> DEVOLYMPIC_API UClass* StaticClass<AWJ_GameObject>()
	{
		return AWJ_GameObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AWJ_GameObject(Z_Construct_UClass_AWJ_GameObject, &AWJ_GameObject::StaticClass, TEXT("/Script/DevOlympic"), TEXT("AWJ_GameObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWJ_GameObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
