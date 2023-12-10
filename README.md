# cub3d


Make Your Own Raycaster Part 1
https://youtu.be/gYRrGTC7GtA?si=-BGRp_D0vWSgi-eN

42 docs - cub3d
https://harm-smits.github.io/42docs/projects/cub3d


---
*TO DO*
---

--> Optionnel : rendre le jeu plus fluide

--> pouvoir gerer plusieurs inputs du clavier en meme temps

--> Parsing : Cas ou une clef est vraiment random : oiwehroiwhr, le programme se lance quand meme


Une fois tout le reste fait :

--> Re-tester avec pleins de maps : Le parsing + leaks de memoire

--> Re-tester avec pleins de mauvaises maps ou de mauvais fichier : Parsing + leak de memoire
	-> faire un dossier de test mauvais

--> In game : bien verifier que l'on ait pas de bugs visuels, notamment proche des murs, dans les angles etc...


Tests a realiser pour le parsing et les leaks :
- Mauvais format de fichier
- Fichier vide
- Mauvaise clef pour les textures ou le sol
- Clef en double pour les textures
- Clef manquante -> A verifier car l'erreur affiche n'est pas la bonne, fonction is_map a verifier
- Plusieurs players / aucun player
- Map non fermee
- Mauvaise key dans la map
- Tester avec differentes map correctes de differentes tailles
- Mauvais format de texture
- Texture presente mais pas un xpm a l'interieur

Problemes de malloc :

--> A verifier, si gnl a un petit buffer (50000), un leak apparait venant de la fonctin file_in_line, leak seulement observe avec la big map. Ce leak disparait lorsque le buffer est augmente (500000)