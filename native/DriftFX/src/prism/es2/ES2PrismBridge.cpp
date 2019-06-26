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


#include <jni.h>
#include <iomanip>

#include "ES2PrismBridge.h"
#include "ES2NativeSurface.h"

#include <DriftFX/GL/GLContext.h>
#include <DriftFX/GL/GLDebug.h>
#include <utils/Logger.h>

#include <gl/GLLog.h>

using namespace driftfx::gl;

using namespace driftfx::internal;
using namespace driftfx::internal::prism;
using namespace driftfx::internal::prism::es2;

ES2PrismBridge::ES2PrismBridge(GLContext* fxContext) :
	PrismBridge(fxContext),
	fxGLContext(fxContext) {

	LogDebug("Constructed PrismBridge with fxContext = " << fxContext);

	fxSharedGLContext = fxContext->CreateSharedContext();
}

ES2PrismBridge::~ES2PrismBridge() {
	delete fxSharedGLContext;
}


int ES2PrismBridge::CopyTexture(int sourceTex, int targetTex, int width, int height) {
	// COPY OVER
	GLuint fbos[2];

	GLCALL( glGenFramebuffers(2, &fbos[0]) );

	GLCALL( glBindFramebuffer(GL_READ_FRAMEBUFFER, fbos[0]) );
	GLCALL( glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sourceTex, 0) );

	GLCALL( glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbos[1]); );
	GLCALL( glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, targetTex, 0) );

	GLCALL( glClearColor(0, 0, 0, 0) );
	GLCALL( glClear(GL_COLOR_BUFFER_BIT) );

	GLCALL( glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR) );

	// We need to wait here for the blit operation to finish to prevent copying an empty texture in FX context
	GLCALL( glFinish() );

	GLCALL( glDeleteFramebuffers(2, &fbos[0]) );

	return 0;
}

NativeSurface* ES2PrismBridge::CreateNativeSurface(long surfaceId, JNINativeSurface* api) {
	return new ES2NativeSurface(surfaceId, api);
}


