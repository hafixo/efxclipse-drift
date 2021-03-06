package org.eclipse.fx.drift;

public class Vec2i {
	public final int x;
	public final int y;
	
	public Vec2i(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	@Override
	public String toString() {
		return "Vec2i(" + x + ", " + y + ")";
	}
}
