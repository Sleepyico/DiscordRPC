#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "Engine.h"
#include "DiscordRpcBlueprint.generated.h"

// unreal's header tool hates clang-format
// clang-format off

/**
* Ask to join callback data
*/
USTRUCT(BlueprintType)
struct FDiscordUserData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Discord")
    FString userId;
    UPROPERTY(BlueprintReadOnly, Category = "Discord")
    FString username;
    UPROPERTY(BlueprintReadOnly, Category = "Discord")
    FString discriminator;
    UPROPERTY(BlueprintReadOnly, Category = "Discord")
    FString avatar;
};

/**
* Valid response codes for Respond function
*/
UENUM(BlueprintType)
enum class EDiscordJoinResponseCodes : uint8
{
	DISCORD_REPLY_NO		UMETA(DisplayName="No"),
	DISCORD_REPLY_YES		UMETA(DisplayName="Yes"),
	DISCORD_REPLY_IGNORE	UMETA(DisplayName="Ignore")
};

DECLARE_LOG_CATEGORY_EXTERN(Discord, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordConnected, const FDiscordUserData&, joinRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiscordDisconnected, int, errorCode, const FString&, errorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiscordErrored, int, errorCode, const FString&, errorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordJoin, const FString&, joinSecret);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordSpectate, const FString&, spectateSecret);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscordJoinRequest, const FDiscordUserData&, joinRequest);

// clang-format on

/**
 * Rich presence data
 */
USTRUCT(BlueprintType)
struct FDiscordRichPresence {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString state;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString details;
    // todo, timestamps are 64bit, does that even matter?
    // ^ yes, it does.. ints have a max value of 2,147,483,647
    // 64bit ints have a max value of 9,223,372,036,854,775,807
    // so we need to use int64, not int or we'll get overflow errors
    // resulting in the timestamps breaking rich presence - Lewis/Basic
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    int64 startTimestamp = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    int64 endTimestamp = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString largeImageKey;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString largeImageText;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString smallImageKey;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString smallImageText;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString partyId;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    int partySize = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    int partyMax = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString matchSecret;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString joinSecret;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    FString spectateSecret;
    UPROPERTY(BlueprintReadWrite, Category = "Discord")
    bool instance = false;
};

/**
 *
 */
UCLASS(BlueprintType, meta = (DisplayName = "Discord RPC"), Category = "Discord")
class DISCORDRPC_API UDiscordRpc : public UObject {
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure)
        int64 GetStartTimeStamp() const {return FDateTime::Now().ToUnixTimestamp();}

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Initialize connection", Keywords = "Discord rpc"),
              Category = "Discord")
    void Initialize(const FString& applicationId,
                    bool autoRegister,
                    const FString& optionalSteamId);

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Shut down connection", Keywords = "Discord rpc"),
              Category = "Discord")
    void Shutdown();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Check for callbacks", Keywords = "Discord rpc"),
              Category = "Discord")
    void RunCallbacks();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Send presence", Keywords = "Discord rpc"),
              Category = "Discord")
    void UpdatePresence();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Clear presence", Keywords = "Discord rpc"),
              Category = "Discord")
    void ClearPresence();

    UFUNCTION(BlueprintCallable,
              meta = (DisplayName = "Respond to join request", Keywords = "Discord rpc"),
              Category = "Discord")
    void Respond(const FString& userId, int reply);

    UPROPERTY(BlueprintReadOnly,
              meta = (DisplayName = "Is Discord connected", Keywords = "Discord rpc"),
              Category = "Discord")
    bool IsConnected;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "On connection", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordConnected OnConnected;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "On disconnection", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordDisconnected OnDisconnected;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "On error message", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordErrored OnErrored;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "When Discord user presses join", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordJoin OnJoin;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "When Discord user presses spectate", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordSpectate OnSpectate;

    UPROPERTY(BlueprintAssignable,
              meta = (DisplayName = "When Discord another user sends a join request",
                      Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordJoinRequest OnJoinRequest;

    UPROPERTY(BlueprintReadWrite,
              meta = (DisplayName = "Rich presence info", Keywords = "Discord rpc"),
              Category = "Discord")
    FDiscordRichPresence RichPresence;
};
