// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DevOlympic/public/DevOlympic.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDevOlympic() {}
// Cross Module References
	DEVOLYMPIC_API UEnum* Z_Construct_UEnum_DevOlympic_EGameType();
	UPackage* Z_Construct_UPackage__Script_DevOlympic();
	DEVOLYMPIC_API UEnum* Z_Construct_UEnum_DevOlympic_EPingPongState();
	DEVOLYMPIC_API UEnum* Z_Construct_UEnum_DevOlympic_EGameState();
// End Cross Module References
	static UEnum* EGameType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DevOlympic_EGameType, Z_Construct_UPackage__Script_DevOlympic(), TEXT("EGameType"));
		}
		return Singleton;
	}
	template<> DEVOLYMPIC_API UEnum* StaticEnum<EGameType>()
	{
		return EGameType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EGameType(EGameType_StaticEnum, TEXT("/Script/DevOlympic"), TEXT("EGameType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DevOlympic_EGameType_Hash() { return 3509139876U; }
	UEnum* Z_Construct_UEnum_DevOlympic_EGameType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DevOlympic();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EGameType"), 0, Get_Z_Construct_UEnum_DevOlympic_EGameType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EGameType::PingPong", (int64)EGameType::PingPong },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "public/DevOlympic.h" },
				{ "PingPong.Name", "EGameType::PingPong" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DevOlympic,
				nullptr,
				"EGameType",
				"EGameType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EPingPongState_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DevOlympic_EPingPongState, Z_Construct_UPackage__Script_DevOlympic(), TEXT("EPingPongState"));
		}
		return Singleton;
	}
	template<> DEVOLYMPIC_API UEnum* StaticEnum<EPingPongState>()
	{
		return EPingPongState_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EPingPongState(EPingPongState_StaticEnum, TEXT("/Script/DevOlympic"), TEXT("EPingPongState"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DevOlympic_EPingPongState_Hash() { return 2958822632U; }
	UEnum* Z_Construct_UEnum_DevOlympic_EPingPongState()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DevOlympic();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EPingPongState"), 0, Get_Z_Construct_UEnum_DevOlympic_EPingPongState_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EPingPongState::Intro", (int64)EPingPongState::Intro },
				{ "EPingPongState::Serv", (int64)EPingPongState::Serv },
				{ "EPingPongState::Rally", (int64)EPingPongState::Rally },
				{ "EPingPongState::RallyOver", (int64)EPingPongState::RallyOver },
				{ "EPingPongState::SetOver", (int64)EPingPongState::SetOver },
				{ "EPingPongState::Deuce", (int64)EPingPongState::Deuce },
				{ "EPingPongState::MatchOver", (int64)EPingPongState::MatchOver },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Deuce.Comment", "// ?????? ?? ????\n// 11???? ???? ???? 1??\xc6\xae ????. 5?? 3????\n" },
				{ "Deuce.Name", "EPingPongState::Deuce" },
				{ "Deuce.ToolTip", "?????? ?? ????\n11???? ???? ???? 1??\xc6\xae ????. 5?? 3????" },
				{ "Intro.Name", "EPingPongState::Intro" },
				{ "MatchOver.Comment", "// 10:10 ??\xc8\xb2, 2?? ???\xcc\xb0? ???????? ???? ????\n" },
				{ "MatchOver.Name", "EPingPongState::MatchOver" },
				{ "MatchOver.ToolTip", "10:10 ??\xc8\xb2, 2?? ???\xcc\xb0? ???????? ???? ????" },
				{ "ModuleRelativePath", "public/DevOlympic.h" },
				{ "Rally.Name", "EPingPongState::Rally" },
				{ "RallyOver.Name", "EPingPongState::RallyOver" },
				{ "Serv.Name", "EPingPongState::Serv" },
				{ "SetOver.Comment", "// ?????? ?? ????\n" },
				{ "SetOver.Name", "EPingPongState::SetOver" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DevOlympic,
				nullptr,
				"EPingPongState",
				"EPingPongState",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EGameState_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DevOlympic_EGameState, Z_Construct_UPackage__Script_DevOlympic(), TEXT("EGameState"));
		}
		return Singleton;
	}
	template<> DEVOLYMPIC_API UEnum* StaticEnum<EGameState>()
	{
		return EGameState_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EGameState(EGameState_StaticEnum, TEXT("/Script/DevOlympic"), TEXT("EGameState"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DevOlympic_EGameState_Hash() { return 3811785898U; }
	UEnum* Z_Construct_UEnum_DevOlympic_EGameState()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DevOlympic();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EGameState"), 0, Get_Z_Construct_UEnum_DevOlympic_EGameState_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EGameState::Lobby", (int64)EGameState::Lobby },
				{ "EGameState::PingPong", (int64)EGameState::PingPong },
				{ "EGameState::GameOver", (int64)EGameState::GameOver },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "GameOver.Name", "EGameState::GameOver" },
				{ "Lobby.Name", "EGameState::Lobby" },
				{ "ModuleRelativePath", "public/DevOlympic.h" },
				{ "PingPong.Name", "EGameState::PingPong" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DevOlympic,
				nullptr,
				"EGameState",
				"EGameState",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
