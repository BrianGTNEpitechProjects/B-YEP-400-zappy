import { MapObject } from "./map_object";
import { PlaneGeometry, Mesh, Scene } from "three";
import { Game } from "./game";

export class Map extends MapObject {
    constructor() {
        super(0, 0, 0, 0, 0);
        var geometryPlane = new PlaneGeometry(Game.lines * Game.squareSize, Game.col * Game.squareSize, 1);
        var materialPlane = this.createMaterialTexture("assets/textures/dirt.png", Game.lines, Game.col);
        var plane = new Mesh(geometryPlane, materialPlane);

        plane.position.x = Game.lines * Game.squareSize / 2;
        plane.position.y = Game.col * Game.squareSize / 2;
        console.log(plane.position.x, plane.position.y, plane.position.z)
        Game.scene.add(plane);
    }
}
