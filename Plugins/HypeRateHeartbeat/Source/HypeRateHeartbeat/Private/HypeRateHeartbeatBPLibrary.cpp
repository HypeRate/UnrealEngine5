// Copyright Epic Games, Inc. All Rights Reserved.

#include "HypeRateHeartbeatBPLibrary.h"
#include "HypeRateHeartbeat.h"

UHypeRateHeartbeatBPLibrary::UHypeRateHeartbeatBPLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}


bool UHypeRateHeartbeatBPLibrary::isConnected = false;
int UHypeRateHeartbeatBPLibrary::lastHeartBeat = 80;
TSharedPtr<IWebSocket> UHypeRateHeartbeatBPLibrary::Socket = nullptr;

class ExampleAutoDeleteAsyncTask : public FNonAbandonableTask {
    friend class FAutoDeleteAsyncTask<ExampleAutoDeleteAsyncTask>;

    int32 ExampleData;

    ExampleAutoDeleteAsyncTask(int32 InExampleData) : ExampleData(InExampleData) { }

    void DoWork() {
        while (UHypeRateHeartbeatBPLibrary::isConnected) {
            UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Ping?"));
            if (UHypeRateHeartbeatBPLibrary::Socket->IsConnected()) {
                UHypeRateHeartbeatBPLibrary::Socket->Send("{\"topic\": \"phoenix\",\"event\": \"heartbeat\",\"payload\": {},\"ref\": 0}");
                UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Ping"));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));
        }
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Thread died..."));
    }

    FORCEINLINE TStatId GetStatId() const {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ExampleAutoDeleteAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};

void UHypeRateHeartbeatBPLibrary::Connect(FString Topic, FString WebsocketKey)
{
    if (isConnected) return;
    isConnected = true;
    const FString ServerURL = TEXT("wss://app.hyperate.io/socket/websocket?token=" + WebsocketKey);
    const FString ServerProtocol = TEXT("ws");
    const TMap<FString, FString> Headers;

    UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] URI %s"), *ServerURL);


    Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol, Headers);
    Socket->OnConnected().AddLambda([&, Topic]() -> void {
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] OnConnected"));

        FString s = FString("{\"topic\": \"hr:" + Topic + "\", \"event\": \"phx_join\",\"payload\": {},\"ref\": 0}");
        Socket->Send(s);

        FAutoDeleteAsyncTask<ExampleAutoDeleteAsyncTask>* Task = new FAutoDeleteAsyncTask<ExampleAutoDeleteAsyncTask>(1);
        Task->StartBackgroundTask();
        });
    Socket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Connection to websocket server has been closed with status code: \"%d\" and reason: \"%s\"."), StatusCode, *Reason);
        });

    Socket->OnMessage().AddLambda([](const FString& Message) -> void {
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] OnMessage %s"), *Message);
        TSharedPtr<FJsonObject> JsonParsed;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(*Message);
        if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
            FString event = JsonParsed->GetStringField("event");
            if (event != "hr_update") return;
            TSharedPtr<FJsonObject> payload = JsonParsed->GetObjectField("payload");
            int hr = payload->GetIntegerField("hr");

            UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] OnMessage hr %s"), *FString::FromInt(hr));
            lastHeartBeat = hr;
        }
        });

    Socket->OnMessageSent().AddLambda([](const FString& MessageString) -> void {
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] OnMessageSent"));
        });

    Socket->OnConnectionError().AddLambda([](const FString& Error) -> void {
        UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] OnConnectionError %s"), *Error);
        });

    Socket->Connect();
}

int UHypeRateHeartbeatBPLibrary::GetHeartBeat()
{
    return lastHeartBeat;
}

void UHypeRateHeartbeatBPLibrary::Disconnect() {
    UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Closing"));
    if (!Socket->IsConnected()) return;
    isConnected = false;
    Socket->Close();
    UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Thread Joining..."));
    UE_LOG(LogTemp, Log, TEXT("[HYPERATE::DEV] Closed"));
}
