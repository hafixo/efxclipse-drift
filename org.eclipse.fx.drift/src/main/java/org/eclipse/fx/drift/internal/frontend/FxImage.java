package org.eclipse.fx.drift.internal.frontend;

import org.eclipse.fx.drift.internal.common.ImageData;

import com.sun.prism.ResourceFactory;
import com.sun.prism.Texture;

@SuppressWarnings("restriction")
public interface FxImage<D extends ImageData> {
	
	D getData();

	void allocate(ResourceFactory rf) throws Exception;
	void release();
	
	/** is called by the quantum renderer before the texture is rendered */
	void update();

	Texture getTexture();
	
}
