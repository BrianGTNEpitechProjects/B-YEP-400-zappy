import { MapObject } from "./map_object";
import { Game } from "./game";

export class Player extends MapObject {
    constructor(posX: number, posY: number) {
        console.log("HERE")
        super(posX, posY, 0, Game.foodSize * 2);
        var height = this.getHeightCellsObject(posX, posY);

        var load3dmodel = function(gltf: { scene: { scale: { x: number; y: number; z: number; }; position: { x: number; y: number; z: number; }; rotation: { x: number; }; }; }) {
            console.log("LA");
            gltf.scene.scale.x = 3;
            gltf.scene.scale.y = 3;
            gltf.scene.scale.z = 3;
            gltf.scene.position.x = posX * Game.squareSize + Game.squareSize / 2;
            gltf.scene.position.y = posY * Game.squareSize + Game.squareSize / 2;
            gltf.scene.rotation.x = 90 * Math.PI / 180;
            gltf.scene.position.z = height;
            this.scene.add(gltf.scene);
        };
    }
}
