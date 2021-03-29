
///<reference path="lib/libINScore.d.ts"/>

interface GraphicSyncManager {
	updateSync(obj: INScoreObject): boolean;
	clean() : void;
}
