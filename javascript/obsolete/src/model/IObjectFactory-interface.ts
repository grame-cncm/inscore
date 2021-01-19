
///<reference path="IObject.ts"/>

var IObjectFactory : IObjectFactoryInterface;
abstract class  IObjectFactoryInterface {
	abstract createViews(obj: IObject, parent: Array<VObjectView>): Array<VObjectView>
    abstract createObj (name: string , type: string, parent: IObject): IObject
}