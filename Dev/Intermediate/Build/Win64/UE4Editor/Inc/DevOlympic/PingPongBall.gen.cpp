// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/PingPongBall.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePingPongBall() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_APingPongBall_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_APingPongBall();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void APingPongBall::StaticRegisterNativesAPingPongBall()
	{
	}
	UClass* Z_Construct_UClass_APingPongBall_NoRegister()
	{
		return APingPongBall::StaticClass();
	}
	struct Z_Construct_UClass_APingPongBall_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_meshComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_meshComp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APingPongBall_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongBall_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "PingPongBall.h" },
		{ "ModuleRelativePath", "public/PingPongBall.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongBall_Statics::NewProp_meshComp_MetaData[] = {
		{ "Category", "PingPongBall" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongBall.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongBall_Statics::NewProp_meshComp = { "meshComp", nullptr, (EPropertyFlags)0x001000000008000d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongBall, meshComp), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongBall_Statics::NewProp_meshComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongBall_Statics::NewProp_meshComp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APingPongBall_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongBall_Statics::NewProp_meshComp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_APingPongBall_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APingPongBall>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APingPongBall_Statics::ClassParams = {
		&APingPongBall::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_APingPongBall_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_APingPongBall_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_APingPongBall_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongBall_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APingPongBall()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APingPongBall_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APingPongBall, 2984610189);
	template<> DEVOLYMPIC_API UClass* StaticClass<APingPongBall>()
	{
		return APingPongBall::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APingPongBall(Z_Construct_UClass_APingPongBall, &APingPongBall::StaticClass, TEXT("/Script/DevOlympic"), TEXT("APingPongBall"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APingPongBall);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
