package org.eclipse.fx.drift.internal;

import com.sun.prism.Texture;

@SuppressWarnings("restriction")
public class D3DBatch {

	public static native void uploadTexture(Texture fxTexture, long pPixels, int width, int height, int size);
	
}
