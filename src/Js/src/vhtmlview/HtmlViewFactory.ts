
///<reference path="../view/ViewFactory.ts"/>
///<reference path="VHtmlCurveView.ts"/>
///<reference path="VHtmlEllipseView.ts"/>
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="VHtmlImageView.ts"/>
///<reference path="VHtmlLineView.ts"/>
///<reference path="VHtmlRectView.ts"/>
///<reference path="VHtmlSceneView.ts"/>
///<reference path="VHtmlTextView.ts"/>
///<reference path="VHtmlView.ts"/>

class HtmlViewFactory implements ViewFactory {
    
    create (type: string, parent?: VHtmlView): VObjectView {   
        switch (type) {
            case "ellipse":
                return new VHtmlEllipseView (parent);
                            
            case "rect":
                return new VHtmlRectView (parent);
                
            case "curve":
                return new VHtmlCurveView (parent);
                
            case "line":
                return new VHtmlLineView (parent);

            case "txt":
            case "txtf":
                return new VHtmlTextView (parent);

            case "html":
                return new VHtmlHtmlView (parent);
            
            case "scene":
                return new VHtmlSceneView ();
            
            case "img":
                return new VHtmlImageView (parent);
                
            default:
                return null;
        }
    }  
}	
    
    
    