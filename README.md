# HypeRate Unreal Engine 5 Plugin
## V 1.0

### Installation

#### Github

Download latest version from [Releases](https://github.com/HypeRate/UnrealEngine5/releases) tab.  
Unzip it into your `{project_dir}/Plugins` (Create if needed.) folder.  
Restart Unreal Engine and click `Update` on the `Project out of date` prompt.
![update](https://github.com/HypeRate/UnrealEngine5/blob/main/gfx/update.png?raw=true)  
The plugin should be enabled by default. If not, go to `Plugins` (`Edit` -> `Plugins`) and enable it. It's listed under `Hype Rate`.

#### UE Marketplace

Coming soon.

### Usage

To connect to hyperate use `Connect` from `Hype Rate` Action.  
Give provided Topic & Websocket Key.  
Recommended from `Event BeginPlay`  
![connect](https://github.com/HypeRate/UnrealEngine5/blob/main/gfx/connect.png?raw=true)  

To disconnect to hyperate use `Disconnect` from `Hype Rate` Action.  
Recommended from `Event End Play`  
![disconnect](https://github.com/HypeRate/UnrealEngine5/blob/main/gfx/disconnect.png?raw=true)  

To recieve heartbeat use `Get Heart Beat`.   
Recommended from `Event Tick` - you should cache variable as shown.  
![log](https://github.com/HypeRate/UnrealEngine5/blob/main/gfx/log.png?raw=true)  
  
For more information visit [https://www.hyperate.io/](https://www.hyperate.io/) or [Discord](https://discord.gg/75jcqvuHAH)
