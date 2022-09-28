using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SDK_API;

public class HapticTest : MonoBehaviour
{
    void Start()
    {

        TestLeftStartHaptic();
    }


    /********************************/
    public void init()
    {
        SDKAPI.Instance.InitHaptic();

    }
    //≤‚ ‘◊Û ÷∆’Õ®’∂Ø
    public void TestLeftStartHaptic()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_LEFT);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_LEFT);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_LEFT);
        Debug.Log("Bxr TestLeftStartHaptic have done");
    }
    public void TestRightStartHaptic()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_RIGHT);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_RIGHT);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_RIGHT);
        Debug.Log("TestRightStartHaptic have done");
    }
    //≤‚ ‘getDuration
    public void testGetDuration()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);

    }
    //≤‚ ‘isPlaying
    public void testIsPlaying()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_RIGHT);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_RIGHT);

    }
    //≤‚ ‘pause/sesume again
    public void testPauseHaptic()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PauseHaptic((int)HandShankID.HANDSHANK_BOTH);
        Debug.Log("testPauseHaptic have done");

    }

    public void testResumeHaptic()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_BOTH);
        Debug.Log("testResumeHaptic have done");


    }
    //≤‚ ‘stop
    public void testStop()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_BOTH);

        SDKAPI.Instance.StopHaptic((int)HandShankID.HANDSHANK_BOTH);
        Debug.Log("testStop have done");
    }
    //≤‚ ‘SeekTo
    public void testSeekTo()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.SeekTo(100, (int)HandShankID.HANDSHANK_BOTH);
        Debug.Log("testSeekTo have done");
    }
    //≤‚ ‘UpdateHaptic
    public void testUpdateHaptic()
    {
        SDKAPI.Instance.SetDataSource(getblastHeString(), 255, 0, 4, 0, (int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.PrepareHaptic((int)HandShankID.HANDSHANK_BOTH);
        SDKAPI.Instance.StartHaptic((int)HandShankID.HANDSHANK_BOTH);

        SDKAPI.Instance.UpdateHaptic(10, 0, 0, (int)HandShankID.HANDSHANK_BOTH);
    }
    //≤‚ ‘OnBxrPlayerEventListener

    //≤‚ ‘releaseHaptic
    public void testRelease()
    {
        SDKAPI.Instance.InitHaptic();
        SDKAPI.Instance.ReleaseHaptic();
        Debug.Log("testRelease have done");
    }
    //“‘String∏Ò Ω√Ë ˆµƒHE–ßπ˚
    public string getblastHeString()
    {
        string result = new string("{\n" +
                "  \"Metadata\": {\n" +
                "    \"Created\": \"2021-02-23\",\n" +
                "    \"Description\": \"Haptic editor design\",\n" +
                "    \"Version\": 1\n" +
                "  },\n" +
                "  \"Pattern\": [\n" +
                "    {\n" +
                "      \"Event\": {\n" +
                "        \"Duration\": 260,\n" +
                "        \"Parameters\": {\n" +
                "          \"Curve\": [\n" +
                "            {\n" +
                "              \"Frequency\": -33,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 0\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": 63,\n" +
                "              \"Intensity\": 1.0,\n" +
                "              \"Time\": 44\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -5,\n" +
                "              \"Intensity\": 1.0,\n" +
                "              \"Time\": 79\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -14,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 260\n" +
                "            }\n" +
                "          ],\n" +
                "          \"Frequency\": 30,\n" +
                "          \"Intensity\": 100\n" +
                "        },\n" +
                "        \"Type\": \"continuous\",\n" +
                "        \"RelativeTime\": 0\n" +
                "      }\n" +
                "    },\n" +
                "    {\n" +
                "      \"Event\": {\n" +
                "        \"Duration\": 597,\n" +
                "        \"Parameters\": {\n" +
                "          \"Curve\": [\n" +
                "            {\n" +
                "              \"Frequency\": 0,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 0\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -45,\n" +
                "              \"Intensity\": 1.0,\n" +
                "              \"Time\": 81\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -45,\n" +
                "              \"Intensity\": 0.64,\n" +
                "              \"Time\": 534\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -14,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 597\n" +
                "            }\n" +
                "          ],\n" +
                "          \"Frequency\": 30,\n" +
                "          \"Intensity\": 81\n" +
                "        },\n" +
                "        \"Type\": \"continuous\",\n" +
                "        \"RelativeTime\": 265\n" +
                "      }\n" +
                "    },\n" +
                "    {\n" +
                "      \"Event\": {\n" +
                "        \"Duration\": 597,\n" +
                "        \"Parameters\": {\n" +
                "          \"Curve\": [\n" +
                "            {\n" +
                "              \"Frequency\": 0,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 0\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -45,\n" +
                "              \"Intensity\": 1.0,\n" +
                "              \"Time\": 81\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -45,\n" +
                "              \"Intensity\": 0.31,\n" +
                "              \"Time\": 423\n" +
                "            },\n" +
                "            {\n" +
                "              \"Frequency\": -14,\n" +
                "              \"Intensity\": 0.0,\n" +
                "              \"Time\": 597\n" +
                "            }\n" +
                "          ],\n" +
                "          \"Frequency\": 30,\n" +
                "          \"Intensity\": 63\n" +
                "        },\n" +
                "        \"Type\": \"continuous\",\n" +
                "        \"RelativeTime\": 867\n" +
                "      }\n" +
                "    }\n" +
                "  ]\n" +
                "}");
        return result;
    }
}
