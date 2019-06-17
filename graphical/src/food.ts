import { Scene, BoxGeometry, Mesh } from "three";
import { MapObject } from "./map_object";
import { Game } from "./game";

export class Food extends MapObject {
    type: number;
    constructor(type:number, assetName:string) {
        var x = Math.floor(Math.random() * Game.lines);
        var y = Math.floor(Math.random() * Game.col);
        super(x, y, 0, 0, Game.foodSize);
        var z = this.getHeightCellsObject(x, y) + this.sizeZ / 2;
        this.position.z = z;
        this.type = type;

        var geometry = new BoxGeometry(Game.foodSize, Game.foodSize, Game.foodSize);
        var material = this.createMaterialTexture("assets/" + assetName + ".png", 0, 0);
        var food = new Mesh(geometry, material);

        food.position.x = x * Game.squareSize + Game.squareSize / 2;
        food.position.y = y * Game.squareSize + Game.squareSize/ 2;
        food.position.z = z;
        Game.scene.add(food);
    }
}
