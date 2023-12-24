#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Misc/DateTime.h"
#include "DiscordRpcBlueprint.generated.h"

// unreal's header tool hates clang-format
// clang-format offS

/**
 * Ask to join callback data
 */
USTRUCT(BlueprintType)
struct FDiscordUserData {
  GENERATED_USTRUCT_BODY();

  UPROPERTY(BlueprintReadOnly, Category = "DiscordRPC");
  FString userId;
  UPROPERTY(BlueprintReadOnly, Category = "DiscordRPC");
  FString username;
  UPROPERTY(BlueprintReadOnly, Category = "DiscordRPC");
  FString discriminator;
  UPROPERTY(BlueprintReadOnly, Category = "DiscordRPC");
  FString avatar;
};

/**
 * Valid response codes for Respond function
 */
UENUM(BlueprintType)
enum class EDiscordJoinResponseCodes : uint8 {
  DISCORD_REPLY_NO UMETA(DisplayName = "No"),
  DISCORD_REPLY_YES UMETA(DisplayName = "Yes"),
  DISCORD_REPLY_IGNORE UMETA(DisplayName = "Ignore")
};

DECLARE_LOG_CATEGORY_EXTERN(Discord, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordConnected,
                                            const FDiscordUserData &,
                                            joinRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiscordDisconnected, int,
                                             errorCode, const FString &,
                                             errorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiscordErrored, int, errorCode,
                                             const FString &, errorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordJoin, const FString &,
                                            joinSecret);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordSpectate, const FString &,
                                            spectateSecret);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordJoinRequest,
                                            const FDiscordUserData &,
                                            joinRequest);

// clang-format on

/**
 * Rich presence data
 */
USTRUCT(BlueprintType)
struct FDiscordRichPresence {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString state;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString details;
  // todo, timestamps are 64bit, does that even matter?
  // ^ yes, it does.. ints have a max value of 2,147,483,647
  // 64bit ints have a max value of 9,223,372,036,854,775,807
  // so we need to use int64, not int or we'll get overflow errors
  // resulting in the timestamps breaking rich presence - Lewis/Basic
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  int64 startTimestamp = 0;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  int64 endTimestamp = 0;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString largeImageKey;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString largeImageText;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString smallImageKey;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString smallImageText;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString partyId;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  int partySize = 0;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  int partyMax = 0;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString matchSecret;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString joinSecret;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  FString spectateSecret;
  UPROPERTY(BlueprintReadWrite, Category = "DiscordRPC")
  bool instance = false;
};

/**
 *
 */
UCLASS(BlueprintType, meta = (DisplayName = "DiscordRPC"),
       Category = "DiscordRPC")
class DISCORDRPC_API UDiscordRpc : public UObject {
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintPure, Category = "DiscordRPC")
  int64 GetStartTimeStamp() const { return FDateTime::Now().ToUnixTimestamp(); }

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Initialize connection",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void Initialize(const FString &applicationId, bool autoRegister,
                  const FString &optionalSteamId);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Shut down connection",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void Shutdown();

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Check for callbacks",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void RunCallbacks();

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Send presence", Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void UpdatePresence();

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Clear presence", Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void ClearPresence();

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "Respond to join request",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  void Respond(const FString &userId, int reply);

  UPROPERTY(BlueprintReadOnly,
            meta = (DisplayName = "Is Discord connected",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  bool IsConnected;

  UPROPERTY(BlueprintAssignable,
            meta = (DisplayName = "On connection", Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordConnected OnConnected;

  UPROPERTY(BlueprintAssignable,
            meta = (DisplayName = "On disconnection", Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordDisconnected OnDisconnected;

  UPROPERTY(BlueprintAssignable,
            meta = (DisplayName = "On error message", Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordErrored OnErrored;

  UPROPERTY(BlueprintAssignable,
            meta = (DisplayName = "When Discord user presses join",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordJoin OnJoin;

  UPROPERTY(BlueprintAssignable,
            meta = (DisplayName = "When Discord user presses spectate",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordSpectate OnSpectate;

  UPROPERTY(
      BlueprintAssignable,
      meta = (DisplayName = "When Discord another user sends a join request",
              Keywords = "DiscordRPC"),
      Category = "DiscordRPC")
  FDiscordJoinRequest OnJoinRequest;

  UPROPERTY(BlueprintReadWrite,
            meta = (DisplayName = "Rich presence info",
                    Keywords = "DiscordRPC"),
            Category = "DiscordRPC")
  FDiscordRichPresence RichPresence;
};
