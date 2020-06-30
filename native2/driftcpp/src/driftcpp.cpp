
#include <jni.h>
#include <DriftFX/driftcpp.h>

#include <iostream>
#include <string>

#include "driftcppint.h"


jclass driftfx::JNI::cVec2i;
jmethodID driftfx::JNI::mVec2iConstructor;
jfieldID driftfx::JNI::fVec2iX;
jfieldID driftfx::JNI::fVec2iY;

jclass driftfx::JNI::cSwapchainConfig;
jmethodID driftfx::JNI::mSwapchainConfigConstructor;

jmethodID driftfx::JNI::mRenderTargetGetGLTexture;

jmethodID driftfx::JNI::mSwapchainAcquire;
jmethodID driftfx::JNI::mSwapchainTryAcquire;
jmethodID driftfx::JNI::mSwapchainPresent;
jmethodID driftfx::JNI::mSwapchainDispose;

jmethodID driftfx::JNI::mRendererGetSize;
jmethodID driftfx::JNI::mRendererCreateSwapchain;


void driftfx::JNI::init(JNIEnv* env) {
	// Vec2i
	cVec2i = env->FindClass("org/eclipse/fx/drift/Vec2i");
	cVec2i = (jclass)env->NewGlobalRef(cVec2i);
	mVec2iConstructor = env->GetMethodID(cVec2i, "<init>", "(II)V");
	fVec2iX = env->GetFieldID(cVec2i, "x", "I");
	fVec2iY = env->GetFieldID(cVec2i, "y", "I");
	// SwapchainConfig
	cSwapchainConfig = env->FindClass("org/eclipse/fx/drift/SwapchainConfig");
	cSwapchainConfig = (jclass)env->NewGlobalRef(cSwapchainConfig);
	mSwapchainConfigConstructor = env->GetMethodID(cSwapchainConfig, "<init>", "(Lorg/eclipse/fx/drift/Vec2i;ILorg/eclipse/fx/drift/PresentationMode;Lorg/eclipse/fx/drift/TransferType;)V");
	// RenderTarget
	jclass cRenderTarget = env->FindClass("org/eclipse/fx/drift/RenderTarget");
	mRenderTargetGetGLTexture = env->GetMethodID(cRenderTarget, "getGLTexture", "()I");
	// Swapchain
	jclass cSwapchain = env->FindClass("org/eclipse/fx/drift/Swapchain");
	mSwapchainAcquire = env->GetMethodID(cSwapchain, "acquire", "()Lorg/eclipse/fx/drift/RenderTarget;");
	// mSwapchainTryAcquire // TODO generics!?
	mSwapchainPresent = env->GetMethodID(cSwapchain, "present", "(Lorg/eclipse/fx/drift/RenderTarget;)V");
	mSwapchainDispose = env->GetMethodID(cSwapchain, "dispose", "()V");
	// Renderer
	jclass cRenderer = env->FindClass("org/eclipse/fx/drift/Renderer");
	mRendererGetSize = env->GetMethodID(cRenderer, "getSize", "()Lorg/eclipse/fx/drift/Vec2i;");
	mRendererCreateSwapchain = env->GetMethodID(cRenderer, "createSwapchain", "(Lorg/eclipse/fx/drift/SwapchainConfig;)Lorg/eclipse/fx/drift/Swapchain;");
}
void driftfx::JNI::dispose(JNIEnv* env) {
	// Vec2i
	env->DeleteGlobalRef(cVec2i);
	// SwapchainConfig
	env->DeleteGlobalRef(cSwapchainConfig);
	// RenderTarget
	// (nothing to dispose)
	// Swapchain
	// (nothing to dispose)
	// Renderer
	// (nothing to dispose)
}


driftfx::Vec2i driftfx::JNI::convertVec2i(JNIEnv* env, jobject vec2i) {
	jint x = env->GetIntField(vec2i, fVec2iX);
	jint y = env->GetIntField(vec2i, fVec2iY);
	Vec2i result;
	result.x = x;
	result.y = y;
	return result;
}

jobject driftfx::JNI::convertVec2i(JNIEnv* env, Vec2i vec2i) {
	jint x = vec2i.x;
	jint y = vec2i.y;
	return env->NewObject(cVec2i, mVec2iConstructor, x, y);
}

jobject driftfx::JNI::convertSwapchainConfig(JNIEnv* env, SwapchainConfig swapchainConfig) {
	jobject size = convertVec2i(env, swapchainConfig.size);
	jint imageCount = swapchainConfig.imageCount;
	jobject presentationMode = nullptr; // TODO setup presentation mode
	TransferTypeImpl* impl = (TransferTypeImpl*) swapchainConfig.transferType;
	jobject transferType = impl->getJavaInstance();
	return env->NewObject(cSwapchainConfig, mSwapchainConfigConstructor, size, imageCount, presentationMode, transferType);
}

jint driftfx::JNI::callRenderTargetGetGLTexture(JNIEnv* env, jobject renderTarget) {
	return env->CallIntMethod(renderTarget, mRenderTargetGetGLTexture);
}

jobject driftfx::JNI::callSwapchainAcquire(JNIEnv* env, jobject swapchain) {
	return env->CallObjectMethod(swapchain, mSwapchainAcquire);
}

jobject driftfx::JNI::callSwapchainTryAcquire(JNIEnv* env, jobject swapchain) {
	// TODO
	return nullptr;
}

void driftfx::JNI::callSwapchainPresent(JNIEnv* env, jobject swapchain, jobject renderTarget) {
	env->CallVoidMethod(swapchain, mSwapchainPresent, renderTarget);
}

void driftfx::JNI::callSwapchainDispose(JNIEnv* env, jobject swapchain) {
	env->CallVoidMethod(swapchain, mSwapchainDispose);
}

jobject driftfx::JNI::callRendererGetSize(JNIEnv* env, jobject renderer) {

	


	std::cout << "calling getSize on " << renderer << " with methodID " << mRendererGetSize << std::endl;
	std::cout << " btw env = " << env << std::endl;
	jobject result = env->CallObjectMethod(renderer, mRendererGetSize);
	std::cout << " -> returning " << result << std::endl;
	std::cout << std::flush;
	return result;
}

jobject driftfx::JNI::callRendererCreateSwapchain(JNIEnv* env, jobject renderer, jobject swapchainConfig) {
	return env->CallObjectMethod(renderer, mRendererCreateSwapchain, swapchainConfig);
}

driftfx::Renderer::~Renderer() {
}




driftfx::RendererImpl::RendererImpl(JNIEnv* _env, jobject javaRenderer) {
	this->env = _env;
	this->javaInstance = javaRenderer;
}

jobject driftfx::RendererImpl::getJavaInstance() {
	return javaInstance;
}

driftfx::Vec2i driftfx::RendererImpl::getSize() {
	jobject javaSize = driftfx::JNI::callRendererGetSize(env, javaInstance);
	return driftfx::JNI::convertVec2i(env, javaSize);
}


driftfx::Swapchain* driftfx::RendererImpl::createSwapchain(driftfx::SwapchainConfig config) {
	jobject javaSwapchain = driftfx::JNI::callRendererCreateSwapchain(env, javaInstance, driftfx::JNI::convertSwapchainConfig(env, config));
	return new driftfx::SwapchainImpl(env, javaSwapchain);
}



driftfx::SwapchainImpl::SwapchainImpl(JNIEnv* _env, jobject _javaInstance) {
	this->env = _env;
	this->javaInstance = _javaInstance;
}

jobject driftfx::SwapchainImpl::getJavaInstance() {
	return javaInstance;
}

void driftfx::SwapchainImpl::present(driftfx::RenderTarget* target) {
	driftfx::RenderTargetImpl* internalTarget = (driftfx::RenderTargetImpl*) target;
	driftfx::JNI::callSwapchainPresent(env, javaInstance, internalTarget->getJavaInstance());
}

driftfx::RenderTarget* driftfx::SwapchainImpl::acquire() {
	jobject renderTarget = driftfx::JNI::callSwapchainAcquire(env, javaInstance);
	return new RenderTargetImpl(env, renderTarget);
}

driftfx::RenderTarget* driftfx::SwapchainImpl::tryAcquire() {
	jobject renderTarget = driftfx::JNI::callSwapchainTryAcquire(env, javaInstance);
	return nullptr; // TODO optional<rendertarget>
}

driftfx::Swapchain::~Swapchain() {
}
driftfx::SwapchainImpl::~SwapchainImpl() {
	driftfx::JNI::callSwapchainDispose(env, javaInstance);
}

driftfx::RenderTargetImpl::RenderTargetImpl(JNIEnv* _env, jobject _javaInstance) {
	this->env = _env;
	this->javaInstance = _javaInstance;
}

jobject driftfx::RenderTargetImpl::getJavaInstance() {
	return javaInstance;
}

int driftfx::RenderTargetImpl::getGLTexture() {
	return (int) driftfx::JNI::callRenderTargetGetGLTexture(env, javaInstance);
}


driftfx::TransferTypeImpl::TransferTypeImpl(JNIEnv* _env, jobject _javaInstance) {
	env = _env;
	javaInstance = _javaInstance;
}

::std::string driftfx::TransferTypeImpl::getId() {
	return nullptr;
}

bool driftfx::TransferTypeImpl::isAvailable() {
	return false;
}

jobject driftfx::TransferTypeImpl::getJavaInstance() {
	return javaInstance;
}



driftfx::Renderer* driftfx::initializeRenderer(JNIEnv* env, jobject javaRenderer) {

	// TODO - we want this only once!
	driftfx::JNI::init(env);

	// -- init transfer types -> TODO once!

	jclass cStandardTransferTypes = env->FindClass("org/eclipse/fx/drift/StandardTransferTypes");
	jfieldID fStandardTransferTypesMainMemory = env->GetStaticFieldID(cStandardTransferTypes, "MainMemory", "Lorg/eclipse/fx/drift/TransferType;");
	jfieldID fStandardTransferTypesIOSurface = env->GetStaticFieldID(cStandardTransferTypes, "IOSurface", "Lorg/eclipse/fx/drift/TransferType;");
	jfieldID fStandardTransferTypesNVDXInterop = env->GetStaticFieldID(cStandardTransferTypes, "NVDXInterop", "Lorg/eclipse/fx/drift/TransferType;");

	jobject mainMemory = env->GetStaticObjectField(cStandardTransferTypes, fStandardTransferTypesMainMemory);
	jobject ioSurface = env->GetStaticObjectField(cStandardTransferTypes, fStandardTransferTypesIOSurface);
	jobject nvdxInterop = env->GetStaticObjectField(cStandardTransferTypes, fStandardTransferTypesNVDXInterop);

	driftfx::StandardTransferTypes::MainMemory = new TransferTypeImpl(env, mainMemory);
	driftfx::StandardTransferTypes::IOSurface = new TransferTypeImpl(env, ioSurface);
	driftfx::StandardTransferTypes::NVDXInterop = new TransferTypeImpl(env, nvdxInterop);

	// --

	return new driftfx::RendererImpl(env, javaRenderer);
}




driftfx::TransferType* driftfx::StandardTransferTypes::MainMemory = nullptr;
driftfx::TransferType* driftfx::StandardTransferTypes::IOSurface = nullptr;
driftfx::TransferType* driftfx::StandardTransferTypes::NVDXInterop = nullptr;