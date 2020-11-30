
///<reference path="JSGMNView.ts"/>
///<reference path="TFileBased.ts"/>

class JSGMNfView extends JSGMNView { 
	fContent = new TFileBased;

	toString() : string		    { return "JSGMNfView"; }

	// oldupdateSpecial(obj: INScoreObject, oid: number)	: boolean {
    //     let address = obj.getOSCAddress();
    //     let pending = (): void => { this.refresh (address); };
	// 	if (this.fContent.getData (obj.getFile(), this.getElement(), pending)) 
	// 		return super.updateSpecial (obj, oid);
	// 	return false;
	// }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        let address = obj.getOSCAddress();
		this.fContent.getDataASync (obj.getFile(), this.getElement()).then ( (text) => {
			if (text) {
				let obj = INScore.objects().create(oid);
				this.refresh (obj.getOSCAddress());
				let ret = super.updateSpecial (obj, oid);
				INScore.objects().del (obj);
				return ret;
			}
		});
		return false;
	}

	gmn2svg (obj: INScoreObject, unused: string, page: number)	: boolean {
		let gmn = this.fContent.get();
		if (gmn) return super.gmn2svg (obj, gmn, page);
		return false;
	}
}
