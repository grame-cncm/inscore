
///<reference path="IObject.ts"/>

var IObjectFactory : IObjectFactoryInterface;
abstract class  IObjectFactoryInterface {
	abstract createView(obj: IObject, parent?: VObjectView): void
    abstract createObj (name: string , type: string, parent: IObject): IObject
}