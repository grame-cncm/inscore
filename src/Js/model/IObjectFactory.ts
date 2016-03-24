///<reference path="IObject.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IScene.ts"/>
///<reference path="ViewFactory.ts"/>
///<reference path="IAppl.ts"/>

class IObjectFactory {	
    
	static createView(obj: IObject): void {
        // met le flag
        obj.checkScene();
        
        // si ce n'est pas une scene, on récupère la scene mere
        if (obj.getTypeString() !== 'scene') { var motherScene: HTMLDivElement = obj.getScene(); }
        
        ViewFactory.create(obj, motherScene);
        obj.afficheView();        
    }
    
    
    static createObj(name: string , type: string, parent: IObject) {
        var obj: IObject;
        switch (type) {
            case "IEllipse.kEllipseType":
                obj = new IEllipse(name, parent);
                this.createView(obj);  
                break;
            
            case "IRect.kRectType":
                obj = new IRect(name, parent);                
                this.createView(obj);    
                break;
                
            case "IScene.kSceneType":
                obj = new IScene(name, parent);
                this.createView(obj);  
                break;
                
            default:
                break;
        }


        /*else
            ITLErr << "unknown object type: " << type << ITLEndl;

        if (obj) {
            obj.setHandlers();
            obj.createVirtualNodes();
            obj.setVisible(IAppl.fDefaultShow);
        }
        return obj; */
        
    }
}