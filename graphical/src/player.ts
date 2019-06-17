import { MapObject } from "./map_object";

export class Player extends MapObject {
    constructor(posX: number, posY: number) {
        super(0, 0, 0, 0, 0);
        var height = this.getHeightCellsObject(posX, posY);

        var load3dmodel = function(gltf: { scene: { scale: { x: number; y: number; z: number; }; position: { x: number; y: number; z: number; }; rotation: { x: number; }; }; }) {
            gltf.scene.scale.x = 3;
            gltf.scene.scale.y = 3;
            gltf.scene.scale.z = 3;
            gltf.scene.position.x = posX * this.squareSize + this.squareSize / 2;
            gltf.scene.position.y = posY * this.squareSize + this.squareSize / 2;
            gltf.scene.rotation.x = 90 * Math.PI / 180;
            gltf.scene.position.z = height;
            this.scene.add(gltf.scene);
        };
    }
}
