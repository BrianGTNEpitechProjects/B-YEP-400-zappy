import { BoxGeometry, Mesh } from "three";
import { MapObject } from "./map_object";
import { Game } from "./game";

var assets = [
    "textures/iron_block",
    "textures/iron_ore",
    "textures/gold_block",
    "textures/gold_ore",
    "textures/diamond_block",
    "textures/diamond_ore",
];

export class Food extends MapObject {
    type: number;

    constructor(type:number, x: number, y: number) {
        super(x, y, 0, Game.foodSize);
        var z = this.getHeightCellsObject(x, y) + this.sizeZ / 2;
        this.position.z = z;
        this.type = type;

        var geometry = new BoxGeometry(Game.foodSize, Game.foodSize, Game.foodSize);
        var material = this.createMaterialTexture("assets/" + assets[type] + ".png", 0, 0);
        var food = new Mesh(geometry, material);

        food.position.x = x * Game.squareSize + Game.squareSize / 2;
        food.position.y = y * Game.squareSize + Game.squareSize/ 2;
        food.position.z = z;
        Game.scene.add(food);
        this.object3D = food;
        Game.mapObject.push(this);
    }
}
