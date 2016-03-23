///<reference path="IObject.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IScene.ts"/>
///<reference path="ViewFactory.ts"/>
///<reference path="IAppl.ts"/>

class IObjectFactory {	
    
	static createView(obj: IObject, appl?: IAppl): void {
        // met le flag
        obj.checkScene();
        if (appl) { var motherScene: HTMLDivElement = obj.getScene(appl); }
        else { var motherScene: HTMLDivElement = obj.getView().getMotherScene() }
        
        ViewFactory.create(obj, motherScene);
        obj.updateView();        
    }
    
    
    static createObj(name: string , type: string, parent: IObject, appl?: IAppl) {
        var obj: IObject; 
        switch (type) {
            case "IEllipse.kEllipseType":
                obj = IEllipse.create(name, parent);
                this.createView(obj, appl);  
                break;
            
            case "IRect.kRectType":
                obj = IRect.create(name, parent);                
                this.createView(obj, appl);    
                break;
                
            case "IScene.kSceneType":
                obj = IScene.create(name, parent);
                this.createView(obj, appl);  
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