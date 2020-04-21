
///<reference path="JSGMNView.ts"/>
///<reference path="TFileBased.ts"/>

class JSGMNfView extends JSGMNView { 
	fContent = new TFileBased;

	toString() : string		    { return "JSGMNfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (this.fContent.getData (obj.getFile(), this.getElement())) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	gmn2svg (obj: INScoreObject, unused: string, page: number)	: boolean {
		let gmn = this.fContent.get();
		if (gmn) return super.gmn2svg (obj, gmn, page);
		return false;
	}
}
