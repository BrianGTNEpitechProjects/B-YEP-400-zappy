import { BoxGeometry, Mesh, Material } from "three";
import { MapObject } from "./map_object";
import Game  from "./game";
import AssetsManager from "./AssetsManager";

var assets = [
    "melon",
    "iron_ore",
    "iron_block",
    "gold_ore",
    "gold_block",
    "diamond_ore",
    "diamond_block",
];

export class Food extends MapObject {
    type: number;

    constructor(type:number, x: number, y: number) {
        super(x, y, 0, Game.foodSize);
        var z = this.getHeightCellsObject(x, y) + this.sizeZ / 2;
        this.position.z = z;
        this.type = type;

        var geometry = new BoxGeometry(Game.foodSize, Game.foodSize, Game.foodSize);
        var material: Material = AssetsManager.getAsset(assets[type]);
        var food = new Mesh(geometry, material);

        food.position.x = x * Game.squareSize + Game.squareSize / 2;
        food.position.y = y * Game.squareSize + Game.squareSize/ 2;
        food.position.z = z;
        Game.scene.add(food);
        this.object3D = food;
        Game.mapObject.push(this);
    }
}
