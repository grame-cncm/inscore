
///<reference path="JSSVGView.ts"/>
///<reference path="TFileLoader.ts"/>
///<reference path="TASyncUpdate.ts"/>

class JSSVGfView extends JSSVGView 
{
    toString() : string			            { return "JSSVGfView"; }
	
	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return TASyncUpdate.update (oid, (obj) => this.setSvg(obj, text));
			}
		});
		return false;
	}

}