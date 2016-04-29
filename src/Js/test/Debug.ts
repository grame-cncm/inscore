///<reference path="src/model/IObject.ts"/>

function debug(): void {
    console.log("**********************************" + "\n" +
                "*       NOUVELLE EXECUTION       *" + "\n" +
                "**********************************" + "\n" );
    
    console.log("---MODEL---")
//    afficheModel(appl);
    console.log("Fin de l'exécution" + "\n" + 
                "----------------------------------" );
}

function afficheModel(obj: IObject): void {
    let child = obj.getSubNodes(); 
    if (child.length != 0) {
        for (var i=0; i < child.length; i++) {
            let c = child[i]
            console.log("Objet : "      + child[i].getName() + "\n" + 
                        "Type : "       + child[i].getTypeString() + "\n" +
                        
                        "Parent : "     + c.getParent().getName() + "\n" + 
                        "Enfant(s) : "     + c.getSubNodes().length + "\n" +  
                        
                        "Couleur : "    + "R : " + c.getColor().getR() + " | "
                                        + "G : " + c.getColor().getG() + " | "
                                        + "B : " + c.getColor().getB() +  "\n" +
                                        
                        "Position : "   + "xPos : " + c.getPos().getXPos() + " | " 
                                        + "yPos : " + c.getPos().getYPos() + " | "
                                        + "largeur : " + c.getPos().getWidth() + " | " 
                                        + "hauteur : " + c.getPos().getHeight() + "\n" +
                        "--------------------------------------------------------------------" + "\n"                 
                         );
                         
            afficheModel(child[i]);    
        }       
    } 
}