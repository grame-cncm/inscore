
///<reference path="JSPianoRollView.ts"/>
///<reference path="TFileBased.ts"/>

class JSPianoRollfView extends JSPianoRollView {

	fContent = new TFileBased;

	toString() : string		    { return "JSPianoRollfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        let address = obj.getOSCAddress();
        let inscore = gGlue.inscore();
        let pending = (): void => { inscore.postMessageStr (address, "refresh"); };
		if (this.fContent.getData (obj.getFile(), this.getElement(), pending)) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	getGmn (proll: OPianorollInfos) : string {
		let gmn = this.fContent.get();
		return (gmn) ? gmn : "";
	}
}
