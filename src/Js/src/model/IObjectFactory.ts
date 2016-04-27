///<reference path="../vhtmlview/HtmlViewFactory.ts"/>
///<reference path="IAppl.ts"/>
///<reference path="IScene.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="ICurve.ts"/>
///<reference path="ILine.ts"/>

class IObjectFactory {	
	static fViewFactory = new HtmlViewFactory();
    
	static createView(obj: IObject, parent: VObjectView): void {
        let view = this.fViewFactory.create (obj.getTypeString(), <VHtmlView>parent);
        obj.setView (view);
    }
        
    static createObj (name: string , type: string, parent: IObject) {
        var obj: IObject;
        switch (type) {
            case "ellipse":
                obj = new IEllipse(name, parent);
                this.createView(obj, parent.getView());  
                break;
            
            case "rect":
                obj = new IRect(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case "curve":
                obj = new ICurve(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                
            case "line":
                obj = new ILine(name, parent);                
                this.createView(obj, parent.getView());    
                break;
                   
            case "scene":
                obj = new IScene(name, parent);
                this.createView(obj, parent.getView());  
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
        } */
        
        return obj; 
    }
}