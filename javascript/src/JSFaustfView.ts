
///<reference path="JSFaustView.ts"/>
///<reference path="TFileLoader.ts"/>


class JSFaustfView extends JSFaustView {

    toString() : string	{ return "JSFaustfView"; }
 
    getCode(code: string) : Promise <string | null>	{ 
  		  return TFileLoader.load (this.getElement(), code);
    }

}
