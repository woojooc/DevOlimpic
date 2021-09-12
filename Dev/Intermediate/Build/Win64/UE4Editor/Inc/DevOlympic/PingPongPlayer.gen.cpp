// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/PingPongPlayer.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePingPongPlayer() {}
// Cross Module References
	DEVOLYMPIC_API UClass* Z_Construct_UClass_APingPongPlayer_NoRegister();
	DEVOLYMPIC_API UClass* Z_Construct_UClass_APingPongPlayer();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
	ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	HEADMOUNTEDDISPLAY_API UClass* Z_Construct_UClass_UMotionControllerComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void APingPongPlayer::StaticRegisterNativesAPingPongPlayer()
	{
	}
	UClass* Z_Construct_UClass_APingPongPlayer_NoRegister()
	{
		return APingPongPlayer::StaticClass();
	}
	struct Z_Construct_UClass_APingPongPlayer_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_capsuleComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_capsuleComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_cameraRoot_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_cameraRoot;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_playerCam_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_playerCam;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_leftController_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_leftController;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_leftHand_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_leftHand;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rightController_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_rightController;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_racket_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_racket;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APingPongPlayer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_DevOlympic,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "PingPongPlayer.h" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_capsuleComp_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?\xdd\xb6??\xcc\xb4?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?\xdd\xb6??\xcc\xb4?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_capsuleComp = { "capsuleComp", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, capsuleComp), Z_Construct_UClass_UCapsuleComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_capsuleComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_capsuleComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_cameraRoot_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// \xc4\xab?\xde\xb6?, ??\xc6\xae?\xd1\xb7? ???? ?\xd1\xb8? ??????\xc6\xae\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "\xc4\xab?\xde\xb6?, ??\xc6\xae?\xd1\xb7? ???? ?\xd1\xb8? ??????\xc6\xae" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_cameraRoot = { "cameraRoot", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, cameraRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_cameraRoot_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_cameraRoot_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_playerCam_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? \xc4\xab?\xde\xb6?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? \xc4\xab?\xde\xb6?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_playerCam = { "playerCam", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, playerCam), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_playerCam_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_playerCam_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftController_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?\xde\xbc? ??\xc6\xae?\xd1\xb7?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?\xde\xbc? ??\xc6\xae?\xd1\xb7?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftController = { "leftController", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, leftController), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftController_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftController_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftHand_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?\xde\xbc? ????(?\xe2\xba\xbb???? ?\xd5\xb8??? ????)\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?\xde\xbc? ????(?\xe2\xba\xbb???? ?\xd5\xb8??? ????)" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftHand = { "leftHand", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, leftHand), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftHand_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftHand_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_rightController_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?????? ??\xc6\xae?\xd1\xb7?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?????? ??\xc6\xae?\xd1\xb7?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_rightController = { "rightController", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, rightController), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_rightController_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_rightController_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APingPongPlayer_Statics::NewProp_racket_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?????? ????(????)\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "public/PingPongPlayer.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?????? ????(????)" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APingPongPlayer_Statics::NewProp_racket = { "racket", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(APingPongPlayer, racket), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_racket_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::NewProp_racket_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APingPongPlayer_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_capsuleComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_cameraRoot,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_playerCam,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftController,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_leftHand,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_rightController,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APingPongPlayer_Statics::NewProp_racket,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_APingPongPlayer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APingPongPlayer>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APingPongPlayer_Statics::ClassParams = {
		&APingPongPlayer::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_APingPongPlayer_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_APingPongPlayer_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APingPongPlayer_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APingPongPlayer()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APingPongPlayer_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APingPongPlayer, 1334562104);
	template<> DEVOLYMPIC_API UClass* StaticClass<APingPongPlayer>()
	{
		return APingPongPlayer::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APingPongPlayer(Z_Construct_UClass_APingPongPlayer, &APingPongPlayer::StaticClass, TEXT("/Script/DevOlympic"), TEXT("APingPongPlayer"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APingPongPlayer);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
