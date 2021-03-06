package org.eclipse.fx.drift.internal;

import org.eclipse.fx.drift.util.NativeUtil;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class OSGiActivator implements BundleActivator {

	@Override
	public void start(BundleContext context) throws Exception {
		Log.info("DriftFX OSGi Mode");
		NativeUtil.useOsgiEnvironment();
		
		//DriftCPP.classLoader = context.getBundle().adapt(BundleWiring.class).getClassLoader();
	}

	@Override
	public void stop(BundleContext context) throws Exception {
	}

}
