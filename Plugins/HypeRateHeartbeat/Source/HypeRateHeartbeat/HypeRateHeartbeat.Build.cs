// Some copyright should be here...

using UnrealBuildTool;

public class HypeRateHeartbeat : ModuleRules
{
	public HypeRateHeartbeat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Core",
			"WebSockets",
			"Json",
			"JsonUtilities"
			// ... add other public dependencies that you statically link with here ...
		});
			
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			// ... add private dependencies that you statically link with here ...	
		});
	}
}
