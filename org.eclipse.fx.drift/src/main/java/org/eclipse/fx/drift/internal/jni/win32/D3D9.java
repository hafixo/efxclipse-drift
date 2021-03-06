package org.eclipse.fx.drift.internal.jni.win32;

public final class D3D9 {

	private D3D9() {}
	
	public static Win32.IDirect3DDevice9Ex CreateOffscreenDevice() {
		long address = doCreateOffscreenDevice();
		return new Win32.IDirect3DDevice9Ex(address);
	}
	
	public static native long doCreateOffscreenDevice();
	
	public static final int D3DADAPTER_DEFAULT = 0;
    public static final int D3DDEVTYPE_HAL = 1;
    

	private static native long CreateDeviceEx(long _d3d9Ex, 
		    int _Adapter, 
		    int _DeviceType, 
		    long _hFocusWindow, 
		    int _BehaviorFlags, 
		    long _pPresentationParameters, 
		    long _pFullscreenDisplayMode, 
		    long _d3d9DeviceEx);
}
