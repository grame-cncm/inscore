
// -----------------------------------------------------------------
// tools based on typescript lib
// -----------------------------------------------------------------

class TWindow extends Window {

	static getSize() : { w: number, h: number} {
		return { w: innerWidth, h: innerHeight };
	}
	
}