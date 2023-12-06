// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscordRpcBlueprint.h"
#include "Engine/GameInstance.h"
#include "DiscordGameInstance.generated.h"

UENUM(BlueprintType)
enum EDiscordPresenceState
{
	Update UMETA(DisplayName = "Update"),
	Clear UMETA(DisplayName = "Clear")
};

/**
 * 
 */
UCLASS()
class DISCORDRPC_API UDiscordGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:	

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			UDiscordRpc* DiscordRpc;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString ApplicationId;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString OptionalSteamID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString State;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString Details;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString LargeImageKey;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString LargeImageText;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString SmallImageKey;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString SmallImageText;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString PartyId;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString MatchSecret;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString JoinSecret;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			FString SpectateSecret;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			int PartySize;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			int PartyMax;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			bool Instance;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DiscordRPC")
			int64 StampRef;
private:
	virtual void Shutdown() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Discord RPC Settings")
		void SetDiscordPresence(EDiscordPresenceState PresenceState);
	UFUNCTION(BlueprintCallable, Category = "Discord RPC Settings")
		void SetBasicPresence(FString instate, FString indetails, FString inlargeimagekey, FString inlargeimagetext);
	UFUNCTION(BlueprintCallable, Category = "Discord RPC Settings")
		void SetAllPresence(FString instate, FString indetails, FString inlargeimagekey, FString inlargeimagetext, FString insmallimagekey, FString insmallimagetext, FString inpartyid, FString inmatchsecret, FString injoinsecret, FString inspectatesecret, int inpartysize, int inpartymax, bool ininstance);
	UFUNCTION(BlueprintCallable, Category = "Discord RPC Settings")
		void SetAppIDs(FString inapplicationid, FString inoptionalsteamid);
};
