package org.eclipse.fx.drift.internal.jni.win32;

import org.eclipse.fx.drift.internal.Log;

public class NVDXInterop {

	public final static int WGL_ACCESS_READ_ONLY_NV = 0x0000;
	public final static int WGL_ACCESS_READ_WRITE_NV = 0x0001;
	public final static int WGL_ACCESS_WRITE_DISCARD_NV = 0x0002;
	
	public static Win32.HANDLE wglDXOpenDeviceNV(Win32.IDirect3DDevice9Ex dxDevice) throws WindowsError {
		long result = nWglDXOpenDeviceNV(dxDevice.address);
		if (result == 0) {
			WindowsError.checkLastError();
		}
		return new Win32.HANDLE(result);
	}
	private native static long nWglDXOpenDeviceNV(long dxDevice);
	
	
	public static boolean wglDXCloseDeviceNV(Win32.HANDLE hDevice) throws WindowsError {
		boolean result = nWglDXCloseDeviceNV(hDevice.address);
		if (!result) {
			WindowsError.checkLastError();
		}
		return result;
	}
	private native static boolean nWglDXCloseDeviceNV(long hDevice);
	
	
	public static boolean wglDXSetResourceShareHandleNV(Win32.IDirect3DResource9 dxResource, Win32.HANDLE shareHandle) throws WindowsError {
		boolean result = nWglDXSetResourceShareHandleNV(dxResource.address, shareHandle.address);
		Log.debug(result + " = wglDXSetResourceShareHandleNV(" + Long.toHexString(dxResource.address) + ", " + Long.toHexString(shareHandle.address) + ")");
		
		if (!result) {
			WindowsError.checkLastError();
		}
		return result;
	}
	private native static boolean nWglDXSetResourceShareHandleNV(long dxResource, long shareHandle);

	public static Win32.HANDLE wglDXRegisterObjectNV(Win32.HANDLE hDevice, Win32.IDirect3DResource9 dxResource, int name, int type, int access) throws WindowsError {
		long result = nWglDXRegisterObjectNV(hDevice.address, dxResource.address, name, type, access);
		Log.debug(Long.toHexString(result) + " = wglDXRegisterObjectNV(" + Long.toHexString(hDevice.address) + ", " + Long.toHexString(dxResource.address) + ", " + name + ", " + type + ", " + access + ")");
		if (result == 0) {
			WindowsError.checkLastError();
		}
		return new Win32.HANDLE(result);
	}
	private native static long nWglDXRegisterObjectNV(long hDevice, long dxResource, int name, int type, int access);

	public static boolean wglDXUnregisterObjectNV(Win32.HANDLE hDevice, Win32.HANDLE hObject) throws WindowsError {
		boolean result = nWglDXUnregisterObjectNV(hDevice.address, hObject.address);
		Log.debug("calling wglDXUnregisterObjectNV(" + Long.toHexString(hDevice.address) + ", " + Long.toHexString(hObject.address) + ")");
		if (!result) {
			WindowsError.checkLastError();
		}
		return result;
	}
	private native static boolean nWglDXUnregisterObjectNV(long hDevice, long hObject);
	
	public static boolean wglDXLockObjectsNV(Win32.HANDLE hDevice, Win32.HANDLE hObject) throws WindowsError {
		boolean result = nWglDXLockObjectsNV(hDevice.address, hObject.address);
		if (!result) {
			WindowsError.checkLastError();
		}
		return result;
	}
	private native static boolean nWglDXLockObjectsNV(long hDevice, long hObject);
	
	public static boolean wglDXUnlockObjectsNV(Win32.HANDLE hDevice, Win32.HANDLE hObject) throws WindowsError {
		boolean result = nWglDXUnlockObjectsNV(hDevice.address, hObject.address);
		if (!result) {
			WindowsError.checkLastError();
		}
		return result;
	}
	private native static boolean nWglDXUnlockObjectsNV(long hDevice, long hObject);
	
}
