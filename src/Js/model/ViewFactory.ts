
///<reference path="IObject.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IObject.ts"/>
///<reference path="VObjectView.ts"/>
///<reference path="VEllipseView.ts"/>
///<reference path="VSceneView.ts"/>
///<reference path="VRectView.ts"/>


class ViewFactory {
    
    static create (object: IObject, motherScene: HTMLDivElement): void{   
        var type = object.getTypeString();
        switch (type) {
            case "ellipse":
                var view = new VEllipseView (motherScene, object);
                object.setView(view);
                break;
                
            case "scene":
                var view = new VSceneView (motherScene, object);
                object.setView(view);
                break;
                         
            case "rect":
                var view = new VRectView (motherScene, object);
                object.setView(view);         
                break;
                
            default:
                break;
        }
    }  
}	
    
    
    