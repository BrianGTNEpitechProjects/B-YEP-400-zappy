export class MapObject {
    constructor(posX, posY, posZ, heightPlace, sizeZ) {
        this.position = {
            x:posX,
            y:posY,
            z:posZ
        };
        this.heightPlace = heightPlace;
        this.sizeZ = sizeZ;
    }

    createMaterialTexture(textureName, repeatX, repeatY) {
        var texture = new THREE.TextureLoader().load(textureName);

        texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
        if (repeatX && repeatY) {
            texture.offset.set(0, 0);
            texture.repeat.set(repeatX, repeatY);
        }
        return new THREE.MeshBasicMaterial({map: texture});
    }

    getHeightCellsObject(posX, posY) {
        var height = 0;

        for (var i = 0; i < mapObject.length; i++) {
            if (mapObject[i].position.x == posX && mapObject[i].position.y == posY) {
                height = mapObject[i].position.z + mapObject[i].sizeZ / 2;
            }
        }
        return height;
    }
}
