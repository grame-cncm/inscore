
///<reference path="JSTextView.ts"/>
///<reference path="TFileBased.ts"/>

class JSTextfView extends JSTextView {

	fContent = new TFileBased;

	toString() : string					{ return "JSTextfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        let address = obj.getOSCAddress();
        let pending = (): void => { this.refresh (address); };
		if (this.fContent.getData (obj.getFile(), this.getElement(), pending)) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	getText (infos: OTextInfo) : string {
		let text = this.fContent.get();
		return text ? text.replace(/\r?\n'/g, "<br />") : "";
	}
}