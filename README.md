# Dugeon Master Project

The movement is done with the ZQSD keys (or WASD if QWERTY keyboard). The A key turns the camera to the left (Q for QWERTY) and the E key to the right. The space bar allows you to interact with ladders, holes, doors, items and attack monsters. If the player dies, the R key will reload the game. The ladders allow you to go up to the next level, the holes to go down.

At any time, the player can check his statistics via the interface at the top right. A text is eventually displayed during an action to better understand what is happening in the game.

# Requierment

Dedicated GPU, to build CMake 3.20 and C++ 11.

---

# References

## Graphics

Item sont issus https://cainos.itch.io/pixel-art-icon-pack-rpg Pixel Art Icon Pack RPG par Cainos.

Monstres sont issus https://luizmelo.itch.io/monsters-creatures-fantasy Monsters Creatures Fantasy par LuizMelo.

Textures des murs, eau, sol et portes sont issues https://screamingbrainstudios.itch.io/tiny-texture-pack-2 Tiny texturepack 2 par	Screaming Brain Studios. (Upscale grâce à https://upscayl.github.io/ Upscayl)
 
Police d'écriture utilisée https://www.dafont.com/dungeon-sn.font Dungeon SN Font.

## Code C++ utilisées

La fonction GLSL `mat4  rotationMatrix()` dans le fichier `3D_Facing.vs.glsl` est issue du site de https://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/ Neil Mendoza.

### Rendu de texte

Pour cette partie du projet, j'ai suivi le site conseillé dans les ressources de TD : https://learnopengl.com/In-Practice/Text-Rendering LearnOpenGL section Text Rendering.

Les fichiers `text.vs.glsl` and `text.fs.glsl` sont similaires au tutoriel (delta les noms de variables).
La classe `TextRenderer.cpp `qui permet de stocker les glyphes, générer les quads correspondants à chaque lettre d'une string et calculer la taille (en pixel) d'une chaine de caractères. Le constructeur et la fonction `renderText()` utilisent du code du tutoriel, celui-ci a été modifié pour l'adapter pour à la POO.

## Bibliothèques utilisées

GLFW, GLAD, Glimac, https://github.com/g-truc/glm}{GLM}, https://github.com/leimao/PPMIo PPMIO and https://github.com/nlohmann/json Json for modern C++.