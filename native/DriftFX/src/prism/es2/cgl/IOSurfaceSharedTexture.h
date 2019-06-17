/*
 * Copyright (c) 2019 BestSolution.at and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     Christoph Caks <ccaks@bestsolution.at> - initial API and implementation
 */
#ifndef PRISM_ES2_CGL_IOSURFACESHAREDTEXTURE_H_
#define PRISM_ES2_CGL_IOSURFACESHAREDTEXTURE_H_

#include "../../../SharedTexture.h"
#include <IOSurface/IOSurface.h>
#include <DriftFX/math/Vec2.h>

namespace driftfx {
namespace internal {
namespace prism {
namespace es2 {
namespace cgl {

class IOSurfaceSharedTexture : public SharedTexture {

private:
	IOSurfaceRef ioSurface;

public:

	IOSurfaceSharedTexture(gl::GLContext* context, SurfaceData surfaceData, math::Vec2ui textureSize);
	virtual ~IOSurfaceSharedTexture();

	virtual bool Connect();
	virtual bool Disconnect();

	virtual bool Lock();
	virtual bool Unlock();

	virtual FrameData* CreateFrameData();

};

}
}
}
}
}

#endif /* PRISM_ES2_CGL_IOSURFACESHAREDTEXTURE_H_ */