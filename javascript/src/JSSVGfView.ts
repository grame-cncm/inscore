
///<reference path="JSSVGView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSSVGfView extends JSSVGView 
{
    toString() : string			            { return "JSSVGfView"; }
	
	updateSpecial(obj: INScoreObject)	: boolean {
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.setSvg(obj, text);
			}
			else return false;
		});
		return false;
	}

}