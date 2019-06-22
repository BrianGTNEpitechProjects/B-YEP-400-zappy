import { MapObject } from "./map_object";
import { PlaneGeometry, Mesh } from "three";
import Game  from "./game";

export class ZMap extends MapObject {
    constructor() {
        super(0, 0, 0, 0);
        var geometryPlane = new PlaneGeometry(Game.lines * Game.squareSize, Game.col * Game.squareSize, 1);
        var materialPlane = this.createMaterialTexture("assets/textures/dirt.png", Game.lines, Game.col);
        var plane = new Mesh(geometryPlane, materialPlane);

        plane.position.x = Game.lines * Game.squareSize / 2;
        plane.position.y = Game.col * Game.squareSize / 2;
        this.object3D = plane;
        Game.scene.add(plane);
    }
}
