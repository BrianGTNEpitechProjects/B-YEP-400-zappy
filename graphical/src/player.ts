import { MapObject } from "./map_object";
import { Game } from "./game";

export class Player extends MapObject {
    id: number;
    level: number;
    team_name: string;
    constructor(id: number, posX: number, posY: number, level: number, team_name: string) {
        super(posX, posY, 0, 20);
        var height = this.getHeightCellsObject(posX, posY);
        this.position.z = height;
        this.id = id;
        this.level = level;
        this.team_name = team_name;
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

    moovePlayer(x: number, y: number) {
        var height = this.getHeightCellsObject(x, y);
        this.position.x = x;
        this.position.y = y;
        this.position.z = height;
        this.object3D.position.x = x * Game.squareSize + Game.squareSize / 2;
        this.object3D.position.y = y * Game.squareSize + Game.squareSize / 2;
        this.object3D.position.z = height;
    }

    setLevel(level: number) {
        this.level = level;
    }
}
