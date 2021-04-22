Le dossier 'FilDeSoi1_rawPatch_Grame2021' comprend tous 
les éléments pour tester le début de la pièce Fil de Soi1,
pour guitare acoustique et temps réel (2016), 
à savoir une grande partie de la page 1 (événements 1 à 4,
 respectivements mesures 1 à 34).

La partition de cet extrait, au format PDF,
se trouve dans le dossier 'partition'

L'enregistrement de la guitare solo de cet extrait de la 
partition se trouve dans le dossier 'wav_guitare_solo' 
(fichier Wav mono).

Le code Faust de l'ensemble des traitements, 
'FilDeSoi1PanStereo' se trouve dans le répertoire 'Faust'. 
Par rapport à l'original en 8 pistes, il a été retravaillé 
pour obtenir une sortie stéréo, en utilisant un panning à la 
Chowning.

Deux implémentations sont proposées, une pour Max, une pour 
PureData, fondées toutes deux sur le code Faust mentionné 
ci-dessus, permetttant de générer l'objet FilDeSoi1PanStereo~ 
(.mxo pour Max, .pd_darwin pour PureData).

Dans les deux cas, le patch principal se nomme 
'FilDeSoi1_stereo_rawpatch_1_2_3_4'.
Il permet de tester soit avec un micro en entrée 
(actuellement via adc~ 1) soit en utilisant l'enregistrement
de guitare grâce à un player. Les numéros d'événements
dans le patch correspondent aux numéros encadrés visibles
sur la partition. L'événement 1 est aussi celui du reset de 
l'élecronique, l'extrait de partition va de 1 à 4.
Pour lancer l'événement, il suffit de cliquer sur le message 
correspondant.








