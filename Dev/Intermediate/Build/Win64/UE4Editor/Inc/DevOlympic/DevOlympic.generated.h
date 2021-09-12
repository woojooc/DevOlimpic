// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DEVOLYMPIC_DevOlympic_generated_h
#error "DevOlympic.generated.h already included, missing '#pragma once' in DevOlympic.h"
#endif
#define DEVOLYMPIC_DevOlympic_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Dev_Source_DevOlympic_public_DevOlympic_h


#define FOREACH_ENUM_EGAMETYPE(op) \
	op(EGameType::PingPong) 

enum class EGameType : uint8;
template<> DEVOLYMPIC_API UEnum* StaticEnum<EGameType>();

#define FOREACH_ENUM_EPINGPONGSTATE(op) \
	op(EPingPongState::Intro) \
	op(EPingPongState::Serv) \
	op(EPingPongState::Rally) \
	op(EPingPongState::RallyOver) \
	op(EPingPongState::SetOver) \
	op(EPingPongState::Deuce) \
	op(EPingPongState::MatchOver) 

enum class EPingPongState : uint8;
template<> DEVOLYMPIC_API UEnum* StaticEnum<EPingPongState>();

#define FOREACH_ENUM_EGAMESTATE(op) \
	op(EGameState::Lobby) \
	op(EGameState::PingPong) \
	op(EGameState::GameOver) 

enum class EGameState : uint8;
template<> DEVOLYMPIC_API UEnum* StaticEnum<EGameState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
