
///<reference path="../view/ViewFactory.ts"/>
///<reference path="VHtmlArcView.ts"/>
///<reference path="VHtmlCurveView.ts"/>
///<reference path="VHtmlEllipseView.ts"/>
///<reference path="VHtmlFileView.ts"/>
///<reference path="VHtmlGMNView.ts"/>
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="VHtmlImageView.ts"/>
///<reference path="VHtmlLineView.ts"/>
///<reference path="VHtmlPianoRollView.ts"/>
///<reference path="VHtmlPolygonView.ts"/>
///<reference path="VHtmlRectView.ts"/>
///<reference path="VHtmlSceneView.ts"/>
///<reference path="VHtmlSVGfView.ts"/>
///<reference path="VHtmlSVGView.ts"/>
///<reference path="VHtmlTextView.ts"/>
///<reference path="VHtmlVideoView.ts"/>
///<reference path="VHtmlView.ts"/>

class HtmlViewFactory implements ViewFactory {
    
    create (type: string, parent?: VHtmlView, name?: string): VObjectView {   
        switch (type) {
            case kEllipseType:
                return new VHtmlEllipseView (parent);
                            
            case kRectType:
                return new VHtmlRectView (parent);
                
            case kCurveType:
                return new VHtmlCurveView (parent);
                
            case kLineType:
                return new VHtmlLineView (parent);
                
            case kPolygonType:
                return new VHtmlPolygonView (parent);                

            case kTextType:
            case kTextfType:
                return new VHtmlTextView (parent);

            case kHtmlType:
                return new VHtmlHtmlView (parent);
            
            case kSceneType:
                return new VHtmlSceneView (name);
            
            case kSvgfType :
                return new VHtmlSVGfView (parent);

            case kImgType:
                return new VHtmlImageView (parent);
                
            case kArcType:
                return new VHtmlArcView (parent);

            case kVideoType:
                return new VHtmlVideoView (parent);    
                            
            case kGuidoCodeType:
                    return new VHtmlGMNView (parent);
                    
            case kGuidoPianoRollType:
                    return new VHtmlPianoRollView (parent);                    

            case kSvgType:
                    return new VHtmlSvgView (parent);
            
            case kFileType:
                    return new VHtmlFilefView(parent);
                                    
            default:
                return null;
        }
    }  
}	
    
    
    