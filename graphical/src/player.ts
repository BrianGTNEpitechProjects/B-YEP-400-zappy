import { MapObject } from "./map_object";
import { Game } from "./game";

export class Player extends MapObject {
    constructor(posX: number, posY: number) {
        super(posX, posY, 0, 20);
        var height = this.getHeightCellsObject(posX, posY);
        this.position.z = height;
        var that = this;

        Game.gltfLoader.load(
            "assets/3DModels/steveriged.gltf",
            function(gltf) {
                gltf.scene.scale.set(2, 2, 2);
                gltf.scene.position.x = posX * Game.squareSize + Game.squareSize / 2;
                gltf.scene.position.y = posY * Game.squareSize + Game.squareSize / 2;
                gltf.scene.position.z = height;
                gltf.scene.rotation.x = 90 * Math.PI / 180;
                Game.scene.add(gltf.scene);
                that.object3D = gltf.scene;
                Game.mapObject.push(that);

        });
    }
}
