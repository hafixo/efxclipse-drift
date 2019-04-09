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



#include "PrismBridge.h"

using namespace driftfx;
using namespace driftfx::gl;

using namespace driftfx::internal;
using namespace driftfx::internal::prism;

PrismBridge* PrismBridge::bridge = nullptr;

PrismBridge* PrismBridge::Get() {
	return bridge;
}

PrismBridge::PrismBridge(Context* fxContext) :
	defaultContext(nullptr),
	fxContext(fxContext),
	shareManager(nullptr) {

}

PrismBridge::~PrismBridge() {

}

ShareManager * PrismBridge::GetShareManager()
{
	return shareManager;
}

void PrismBridge::Destroy() {
	delete bridge;
	bridge = nullptr;
}


GLContext* PrismBridge::GetDefaultContext() {
	return defaultContext;
}

Context* PrismBridge::GetFxContext() {
	return fxContext;
}
