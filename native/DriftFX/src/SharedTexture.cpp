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

#include "SharedTexture.h"
#include <DriftFX/DriftFXSurface.h>

#include "Common.h"

using namespace driftfx;
using namespace driftfx::gl;
using namespace driftfx::internal;


SharedTexture::SharedTexture(DriftFXSurface* surface, GLContext* glContext, unsigned int width, unsigned int height) :
		surface(surface),
		width(width), height(height),
		glContext(glContext),
		glTexture(nullptr) {
}

SharedTexture::~SharedTexture() {
}

DriftFXSurface* SharedTexture::GetSurface() {
	return surface;
}

GLTexture* SharedTexture::GetTexture() {
	return glTexture;
}

unsigned int SharedTexture::GetGLTexture() {
	return glTexture->Name();
}

unsigned int SharedTexture::GetWidth() {
	return width;
}

unsigned int SharedTexture::GetHeight() {
	return height;
}
