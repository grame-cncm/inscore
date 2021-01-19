
///<reference path="JSObjectView.ts"/>

interface TUpdate { (obj: INScoreObject) : boolean }

class TASyncUpdate {
	static update (oid: number, f: TUpdate) {
		let obj = INScore.objects().create(oid);
		let ret = f (obj);
		INScore.objects().del (obj);
		return ret;			
	}
}
