import { TextureLoader, MeshBasicMaterial, RepeatWrapping } from "three";
import { Game } from "./game";

export class MapObject {
    position: { x: number; y: number; z: number; };
    heightPlace: number;
    sizeZ: number;
    constructor(posX: number, posY: number, posZ: number, heightPlace: number, sizeZ: number) {
        this.position = {
            x:posX,
            y:posY,
            z:posZ
        };
        this.heightPlace = heightPlace;
        this.sizeZ = sizeZ;
    }

    createMaterialTexture(textureName: string, repeatX: number, repeatY: number) {
        var texture = new TextureLoader().load(textureName);

        texture.wrapS = texture.wrapT = RepeatWrapping;
        if (repeatX && repeatY) {
            texture.offset.set(0, 0);
            texture.repeat.set(repeatX, repeatY);
        }
        return new MeshBasicMaterial({map: texture});
    }

    getHeightCellsObject(posX: number, posY: number) {
        var height = 0;

        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i].position.x == posX && Game.mapObject[i].position.y == posY) {
                height = Game.mapObject[i].position.z + Game.mapObject[i].sizeZ / 2;
            }
        }
        return height;
    }
}
