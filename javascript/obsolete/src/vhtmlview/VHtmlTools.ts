
// -----------------------------------------------------------------
// tools based on typescript lib
// -----------------------------------------------------------------

class TWindow { 
	static getSize() : { w: number, h: number} {
/*
		let e = document.documentElement;
		let g = document.getElementsByTagName('body')[0];
		let w = window.innerWidth || e.clientWidth || g.clientWidth;
		let h = window.innerHeight|| e.clientHeight|| g.clientHeight;
		let width = window.innerWidth ;
		let height = window.innerHeight;
*/
		let width = Math.max(window.innerWidth, document.documentElement.clientWidth, document.body.clientWidth);
		let height = Math.max(window.innerHeight, document.documentElement.clientHeight, document.body.clientHeight);
		return { w: width, h: height };
	}
}