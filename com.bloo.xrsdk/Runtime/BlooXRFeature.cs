using System.Collections.Generic;
using UnityEditor;

#if UNITY_EDITOR
using UnityEditor.XR.OpenXR.Features;
using UnityEngine.XR.OpenXR.Features.Interactions;
#endif

namespace UnityEngine.XR.OpenXR.Features.BlooXRSupport
{
    /// <summary>
    /// Enables the BlooXR mobile OpenXR Loader for Android, and modifies the AndroidManifest to be compatible with Quest.
    /// </summary>
#if UNITY_EDITOR
    [OpenXRFeature(UiName = "BlooXR Support",
        Desc="Necessary to deploy an BlooXR compatible app.",
        Company = "Unity",
        DocumentationLink = "https://developer.blooxr.com/downloads/package/blooxr-openxr-mobile-sdk/",
        OpenxrExtensionStrings = "",
        Version = "1.0.0",
        BuildTargetGroups = new []{BuildTargetGroup.Android},
        CustomRuntimeLoaderBuildTargets = new []{BuildTarget.Android},
        FeatureId = featureId
    )]
#endif
    public class BlooXRFeature : OpenXRFeature
    {
        /// <summary>
        /// The feature id string. This is used to give the feature a well known id for reference.
        /// </summary>
        public const string featureId = "com.unity.openxr.feature.blooxr";

#if UNITY_EDITOR
        protected override void GetValidationChecks(List<ValidationRule> rules, BuildTargetGroup targetGroup)
        {
            rules.Add(new ValidationRule(this)
            {
                message = "Only the BlooXR Touch Interaction Profile is supported right now.",
                checkPredicate = () =>
                {
                    var settings = OpenXRSettings.GetSettingsForBuildTargetGroup(targetGroup);
                    if (null == settings)
                        return false;

                    bool touchFeatureEnabled = false;
                    bool otherInteractionFeatureEnabled = false;
                    foreach (var feature in settings.GetFeatures<OpenXRInteractionFeature>())
                    {
                        if (feature.enabled)
                        {
                            if (feature is BlooXRTouchControllerProfile)
                                touchFeatureEnabled = true;
                            else
                                otherInteractionFeatureEnabled = true;
                        }
                    }
                    return touchFeatureEnabled && !otherInteractionFeatureEnabled;
                },
                fixIt = () =>
                {
                    var settings = OpenXRSettings.GetSettingsForBuildTargetGroup(targetGroup);
                    if (null == settings)
                        return;

                    foreach (var feature in settings.GetFeatures<OpenXRInteractionFeature>())
                    {
                        feature.enabled = (feature is BlooXRTouchControllerProfile);
                    }
                },
                error = true,
            });
        }
#endif
    }
}
