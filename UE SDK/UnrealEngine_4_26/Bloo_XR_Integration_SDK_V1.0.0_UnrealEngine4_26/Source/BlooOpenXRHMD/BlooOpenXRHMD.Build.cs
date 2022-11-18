// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class BlooOpenXRHMD : ModuleRules
    {
        public BlooOpenXRHMD(ReadOnlyTargetRules Target) : base(Target)
        {
			PrivateIncludePaths.AddRange(
				new string[] {
					EngineDirectory + "/Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private",
					EngineDirectory + "/Source/Runtime/Renderer/Private",
					EngineDirectory + "/Source/Runtime/OpenGLDrv/Private",
					EngineDirectory + "/Source/Runtime/VulkanRHI/Private",
					EngineDirectory + "/Source/Runtime/Engine/Classes/Components",
					EngineDirectory + "/Source/Runtime/Engine/Classes/Kismet",
					EngineDirectory + "/Source/Runtime/VulkanRHI/Private/Android",
					EngineDirectory + "/Source/ThirdParty/OpenXR/include",
					"BlooOpenXRHMD/Private",
					//EngineDirectory + "/Plugins/Runtime/BlooOpenXR/Source/BlooOpenXRHMD/Private",
				});

			PublicIncludePathModuleNames.AddRange(
				new string[] {
					"Launch",
					"OpenXRHMD",
					"HeadMountedDisplay",
					"AugmentedReality",
				});


			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"RHI",
					"RenderCore",
					"Renderer",
					"Slate",
					"SlateCore",
					"ImageWrapper",
					"MediaAssets",
					"Analytics",
					"OpenGLDrv",
					"VulkanRHI",
					"HeadMountedDisplay",
					"Projects",
					"OpenXRHMD",
                    "Json",
                    "JsonUtilities",
                });


			if (Target.bBuildEditor == true)
			{
				PrivateDependencyModuleNames.Add("UnrealEd");
			}

			AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");
			AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenXR");

			if (Target.Platform == UnrealTargetPlatform.Android)
			{

				// Vulkan
				{
					AddEngineThirdPartyPrivateStaticDependencies(Target, "Vulkan");
				}
				// AndroidPlugin
				{
					string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
					AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "BlooOpenXRHMD_APL.xml"));
				}
			}
			//else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Windows))
   //         {
   //             PublicDependencyModuleNames.Add("D3D11RHI");
   //             PublicDependencyModuleNames.Add("D3D12RHI");

   //             //PublicSystemLibraries.AddRange(new string[] {
   //             //    "DXGI.lib",
   //             //    "d3d11.lib",
   //             //    "d3d12.lib"
   //             //});

   //             PrivateIncludePaths.Add(Path.Combine(EngineSourceDirectory, "Source/Runtime/VulkanRHI/Private/Windows"));
   //         }
        }
    }
}
