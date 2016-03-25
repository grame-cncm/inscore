
///<reference path="../model/IObject.ts"/>
///<reference path="../model/IRect.ts"/>
///<reference path="../model/IEllipse.ts"/>
///<reference path="../model/IObject.ts"/>
///<reference path="VObjectView.ts"/>
///<reference path="VEllipseView.ts"/>
///<reference path="VSceneView.ts"/>
///<reference path="VRectView.ts"/>
///<reference path="VCurveView.ts"/>
///<reference path="VLineView.ts"/>

class ViewFactory {
    
    static create (object: IObject, motherScene?: HTMLDivElement): void{   
        var type = object.getTypeString();
        switch (type) {
            case "ellipse":
                var view = new VEllipseView (object, motherScene);
                // la vue est mainteant attribut de l'objet
                object.setView(view);
                break;
                            
            case "rect":
                var view = new VRectView (object, motherScene);
                object.setView(view);         
                break;
                
            case "curve":
                var view = new VCurveView (object, motherScene);
                object.setView(view);
                break;
                
            case "line":
                var view = new VLineView (object, motherScene);
                object.setView(view);
                break;    
            
            case "scene":
                var view = new VSceneView (object);
                object.setView(view);
                break;
                
            default:
                break;
        }
    }  
}	
    
    
    