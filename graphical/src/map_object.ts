import { TextureLoader, MeshBasicMaterial, RepeatWrapping, Object3D, Vector3 } from "three";
import Game  from "./game";
import WebSocketManager from "./WebSocketManager";


export class MapObject {
    position: Vector3;
    heightPlace: number;
    sizeZ: number;
    object3D: Object3D;
    constructor(posX: number, posY: number, posZ: number, sizeZ: number) {
        this.position = new Vector3(
            posX,
            posY,
            posZ
        );
        this.sizeZ = sizeZ;
    }

    createMaterialTexture(textureName: string, repeatX: number, repeatY: number) {
        var texture = new TextureLoader().load(textureName);

        texture.wrapS = texture.wrapT = RepeatWrapping;
        if (repeatX && repeatY) {
            texture.offset.set(0, 0);
            texture.repeat.set(repeatX, repeatY);
        }
        return new MeshBasicMaterial({map: texture});
    }

    getHeightCellsObject(posX: number, posY: number, playerToIgnore?: Player) {
        var height = 0;

        for (var i = 0; i < Game.mapObject.length; i++) {
            if (playerToIgnore && Game.mapObject[i] instanceof Player && (Game.mapObject[i] as Player).id == playerToIgnore.id)
                continue;
            if (Game.mapObject[i].position.x == posX && Game.mapObject[i].position.y == posY) {
                if (Game.mapObject[i].position.z + Game.mapObject[i].sizeZ / 2 > height) {
                    height = Game.mapObject[i].position.z + Game.mapObject[i].sizeZ / 2;
                }
            }
        }
        return height;
    }
}


export enum Orientation {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
}

export class Player extends MapObject {
    static rotation: Array<number> = [
        0,
        90 * Math.PI / 180 * 2,
        90 * Math.PI / 180 * 3,
        0,
        90 * Math.PI / 180 * 1
    ];
    id: number;
    level: number;
    team_name: string;
    orientation: number;
    constructor(id: number, posX: number, posY: number, level: number, team_name: string, orientation: number, sendPos: boolean = false) {
        super(posX, posY, 0, 20);
        var height = this.getHeightCellsObject(posX, posY);
        this.position.z = height;
        this.id = id;
        this.level = level;
        this.team_name = team_name;
        this.orientation = orientation;
        var that = this;

        Game.gltfLoader.load(
            "assets/3DModels/steveriged.gltf",
            function(gltf: any) {
                gltf.scene.scale.set(2, 2, 2);
                gltf.scene.position.x = posX * Game.squareSize + Game.squareSize / 2;
                gltf.scene.position.y = posY * Game.squareSize + Game.squareSize / 2;
                gltf.scene.position.z = height;
                gltf.scene.rotation.x = 90 * Math.PI / 180;
                gltf.scene.rotation.y = Player.rotation[that.orientation];
                Game.scene.add(gltf.scene);
                that.object3D = gltf.scene;
                Game.mapObject.push(that);
                if (sendPos) {
                    WebSocketManager.sendMessage(`ppo #${id}\n`);
                }
        });
    }

    moovePlayer(x: number, y: number, orientation: number) {
        var height = this.getHeightCellsObject(x, y, this);
        this.position.x = x;
        this.position.y = y;
        this.position.z = height;
        this.orientation = orientation;
        this.object3D.position.x = x * Game.squareSize + Game.squareSize / 2;
        this.object3D.position.y = y * Game.squareSize + Game.squareSize / 2;
        this.object3D.position.z = height;
        this.object3D.rotation.y = Player.rotation[orientation];
    }

    setLevel(level: number) {
        this.level = level;
    }
}