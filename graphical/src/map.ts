import { MapObject } from "./map_object";
import { PlaneGeometry, Mesh } from "three";
import Game  from "./game";
import AssetsManager from "./AssetsManager";

export class ZMap extends MapObject {
    constructor() {
        super(0, 0, 0, 0);
        var geometryPlane = new PlaneGeometry(Game.lines * Game.squareSize, Game.col * Game.squareSize, 1);
        var materialPlane = AssetsManager.getAsset("dirt");
        var plane = new Mesh(geometryPlane, materialPlane);

        plane.position.x = Game.lines * Game.squareSize / 2;
        plane.position.y = Game.col * Game.squareSize / 2;
        this.object3D = plane;
        Game.scene.add(plane);
    }
}
