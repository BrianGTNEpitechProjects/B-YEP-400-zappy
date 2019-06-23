import { PerspectiveCamera, Scene, WebGLRenderer, TextureLoader, MeshBasicMaterial, RepeatWrapping, Color, Frustum, Matrix4, Vector3, Vector2, Fog } from 'three';
import { OrbitControls } from "three-orbitcontrols-ts";
import { ZMap } from "./map"
import { Food } from './food';
import { MapObject, Player, Orientation } from './map_object';
import { Egg } from './egg';
import { SoundManager, Sound } from './sound_manager';
import EventManager from './EventManager';
import { GameLoadedEvent } from './ZEvent';
import GraphicProtocol from './GraphicProtocol';
import WebSocketManager from './WebSocketManager';
import AssetsManager from './AssetsManager';
const loader = require('three-gltf-loader');

export default class Game {
    static mapObject: Array<MapObject> = new Array<MapObject>();
    static lines:number = 10;
    static col:number = 11;
    static squareSize:number = 10;
    static gameWidth: number = 1200;
    static gameHeight: number = 800;
    static foodSize:number = Game.squareSize / 4;
    static scene: Scene = new Scene();
    static gltfLoader = new loader();
    static cameraSpeed = 0.8;
    //static camera = new OrthographicCamera(Game.gameWidth / -2, Game.gameWidth / 2, Game.gameHeight / -2, Game.gameHeight / 2);    
    static camera = new PerspectiveCamera(75, Game.gameWidth / Game.gameHeight, 0.1, 500);
    static soundManager: SoundManager;
    movement: number = 0;
    zoomLevel: number = 0;
    visibleCase: Array<Vector2>;
    renderer: WebGLRenderer;
    map: ZMap;
    protocol: GraphicProtocol;
    soundManager: SoundManager;
    elapsedTime: number;
    lastUpdate: number;

    constructor(lineSize: number, colSize: number, protocol: GraphicProtocol) {
        if (lineSize) {
            Game.lines = lineSize;
        }
        if (colSize) {
            Game.col = colSize;
        }
        Game.scene.background = new Color(0x808080);
        AssetsManager.getInstance().load();
        this.renderer = new WebGLRenderer({antialias:true, canvas: document.getElementById("gameCanvas") as HTMLCanvasElement});
        this.protocol = protocol;
        this.soundManager = new SoundManager();
        this.elapsedTime = 0;
        this.lastUpdate = 0;

        Game.camera.position.set(50, 50, 100);
        window.addEventListener('resize', this.onWindowResize.bind(this), false);
        document.body.appendChild(this.renderer.domElement);
        Game.camera.lookAt(50, 50, -10);
        this.animate();
        this.onWindowResize();
        this.map = new ZMap();

        var that = this;
        document.addEventListener("keydown", onDocumentKeyDown, false);
        function onDocumentKeyDown(event: any) {
            var keyCode = event.which;

            if (keyCode == 83) {
                Game.camera.position.y -= Game.cameraSpeed;
                that.movement += Game.cameraSpeed;
            }
            if (keyCode == 90) {
                Game.camera.position.y += Game.cameraSpeed;
                that.movement += Game.cameraSpeed;            
            }
            if (keyCode == 81) {
                Game.camera.position.x -= Game.cameraSpeed;
                that.movement += Game.cameraSpeed;
            }
            if (keyCode == 68) {
                Game.camera.position.x += Game.cameraSpeed;
                that.movement += Game.cameraSpeed;
            }
            if (keyCode == 32) {
                if (that.zoomLevel + Game.cameraSpeed <= 30) {
                    Game.camera.position.z += Game.cameraSpeed;
                    that.zoomLevel += Game.cameraSpeed;
                }
            }
            if (keyCode == 78) {
                if (that.zoomLevel - Game.cameraSpeed >= 0) {
                    Game.camera.position.z -= Game.cameraSpeed;
                    that.zoomLevel -= Game.cameraSpeed;
                }
            }
            if (that.movement >= 10) {
                that.movement = 0;
                let visibles = that.getCurrentVisisble();
                let removed = that.visibleCase.filter(val => visibles.findIndex((elem: Vector2) => {return elem.x == val.x && elem.y == val.y}) < 0);
                let added = visibles.filter(val => that.visibleCase.findIndex((elem: Vector2) => {return elem.x == val.x && elem.y == val.y}) < 0);

                removed.forEach((pos: Vector2) => {
                    that.clearCoordinate(pos.x, pos.y);
                });
                added.forEach((pos: Vector2) => {
                    WebSocketManager.sendMessage(`bct ${pos.x} ${pos.y}\n`);
                });
                that.visibleCase = visibles;
            }
            
        }
        
        this.soundManager.playSound(Sound.MINECRAFT_MUSIC, true);
        this.reloadVisible();
        EventManager.getInstance().emit(new GameLoadedEvent());
    }

    getProtocol(): GraphicProtocol {
        return this.protocol;
    }

    getVisibleCases(): Array<Vector2> {
        return this.visibleCase;
    }

    reloadVisible() {
        this.visibleCase = this.getCurrentVisisble();
    }

    getCurrentVisisble(): Array<Vector2> {
        let cases: Array<Vector2> = new Array<Vector2>();
        for (let x : number = 0; x < Game.lines; x++) {
            for (let y : number = 0; y < Game.col; y++) {
                if (Game.isCameraVisible(x, y)) {
                    cases.push(new Vector2(x, y));
                }
            }
        }
        return cases;
    }

    spawnPlayer(id: number, x: number, y: number, orientation: number, level: number, team_name: string, sendPos: boolean = false) {
        new Player(id, x, y, level, team_name, orientation, sendPos);
        this.soundManager.playSound(Sound.VILLAGER_HUM, false);
    }

    setPlayerPos(id: number, x: number, y: number, orientation: number) {
        var player = this.findPlayer(id);

        this.reajustHeight(player);        
        player.moovePlayer(x, y, orientation);
    }

    findPlayer(id: number): Player {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i] instanceof Player) {
                var player = Game.mapObject[i] as Player;
                if (player.id == id) {
                    return player;
                }
            }
        }
    }

    findEgg(id: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i] instanceof Egg) {
                var egg = Game.mapObject[i] as Egg;
                if (egg.id == id) {
                    return egg;
                }
            }
        }
    }

    endOfGame(teamName: string) {
        console.log("End of the game, " + teamName + " won the game");
    }

    addTeamName(teamName: string) {
        console.log("New team: " + teamName);
    }

    setPlayerLevel(id: number, level: number) {
        var player = this.findPlayer(id);
        player.setLevel(level);
        this.soundManager.playSound(Sound.LEVELUP, false);
    }

    setPlayerInventory(id: number, x: number, y: number, res0: number, res1: number, res2: number, res3: number, res4: number, res5: number, res6: number) {
    }

    expulsePlayer(id: number) {
        var player = this.findPlayer(id);
        var x = player.position.x;
        var y = player.position.y;

        if (player.orientation == Orientation.NORTH) {
            if (y + 1 == Game.col) {
                y = 0;
            } else {
                y++;
            }
        } else if (player.orientation == Orientation.SOUTH) {
            if (y == 0) {
                y = Game.col - 1;
            } else {
                y--;
            }
        } else if (player.orientation == Orientation.EAST) {
            if (x + 1 == Game.lines) {
                x = 0;
            } else {
                x++;
            }
        } else {
            if (x == 0) {
                x = Game.lines - 1;
            } else {
                x--;
            }
        }
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i] instanceof Player && Game.mapObject[i].position.x == player.position.x && Game.mapObject[i].position.x == player.position.x) {
                var currentPlayer = Game.mapObject[i] as Player;
                if (currentPlayer.id == id) {
                    continue;
                }
                currentPlayer.moovePlayer(x, y, currentPlayer.orientation);
                this.soundManager.playSound(Sound.VILLAGER_HIT, false);
            }
        }
    }

    setTileContent(x: number, y: number, res0: number, res1: number, res2: number, res3: number, res4: number, res5: number, res6: number) {
        var numberRessources = [res0, res1, res2, res3, res4, res5, res6];
        var currentNumber = [0, 0, 0, 0, 0, 0, 0];

        Game.mapObject.forEach((elem: MapObject) => {
            if (elem instanceof Food) {
                let food: Food = elem as Food;

                if (food.position.x == x && food.position.y == y) {
                    currentNumber[food.type]++;
                }
            }
        });
        for (var i = 0; i < currentNumber.length; i++) {
            if (numberRessources[i] - currentNumber[i] > 0) {
                for (var j = 0; j < numberRessources[i] - currentNumber[i]; j++) {
                    new Food(i, x, y);
                }
            } else if (numberRessources[i] - currentNumber[i] <= 0) {
                for (var j = 0; j > numberRessources[i] - currentNumber[i]; j++) {
                    let index = Game.mapObject.findIndex((elem: MapObject) => {return elem instanceof Food && elem.position.x == x && elem.position.y == y && (elem as Food).type == i});
                    Game.scene.remove(Game.mapObject[index].object3D);                    
                    Game.mapObject.splice(index, 1);
                }
            }
        }
    }
    
    addToTile(x: number, y: number, type: number, qty: number) {
        for (let i: number = 0; i < qty; i++)
            new Food(type, x, y);
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

    onWindowResize() {
        Game.camera.aspect = Game.gameWidth / Game.gameHeight;
        Game.camera.updateProjectionMatrix();
        this.renderer.setSize(Game.gameWidth, Game.gameHeight);
    }

    static isCameraVisible(x: number, y: number): boolean {
        let frustum = new Frustum();
        var cameraProjectionMatrix = new Matrix4();

        Game.camera.updateMatrixWorld();
        Game.camera.matrixWorldInverse.getInverse(Game.camera.matrixWorld);
        cameraProjectionMatrix.multiplyMatrices(Game.camera.projectionMatrix, Game.camera.matrixWorldInverse)
        frustum.setFromMatrix(cameraProjectionMatrix);

        if (frustum.containsPoint(new Vector3(x * Game.squareSize, y * Game.squareSize, 1))) {
            return true;
        } else {
            return false;
        }
    }

    animate() {
        let current = new Date().getTime();

        this.elapsedTime += current - this.lastUpdate;
        this.lastUpdate = current;
        if (this.elapsedTime >= 1000) {
            this.elapsedTime = 0;
            this.protocol.reloadMap();
        }
        requestAnimationFrame(()=>this.animate());
        this.renderer.render(Game.scene, Game.camera);
    }

    deleteFood(type: number, posX: number, posY: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i].position.x == posX && Game.mapObject[i].position.y == posY && Game.mapObject[i] instanceof Food) {
                var food = Game.mapObject[i] as Food;
                if (food.type == type) {
                    this.reajustHeight(Game.mapObject[i]);
                    Game.scene.remove(food.object3D);
                    Game.mapObject.splice(i, 1);
                    break;
                }
            }
        }
    }

    reajustHeight(object: MapObject) {
        for (var j = 0; j < Game.mapObject.length; j++) {
            if (Game.mapObject[j].position.x == object.position.x && Game.mapObject[j].position.y == object.position.y && Game.mapObject[j].position.z > object.position.z) {
                if (object instanceof Player) {
                    Game.mapObject[j].position.z -= object.sizeZ / 2;
                    Game.mapObject[j].object3D.position.z -= object.sizeZ / 2;
                } else {
                    Game.mapObject[j].position.z -= object.sizeZ;
                    Game.mapObject[j].object3D.position.z -= object.sizeZ;
                }
            }
        }
    }

    spawnEgg(idEgg: number, idPlayer: number, x: number, y: number) {
        var player = this.findPlayer(idPlayer);
        new Egg(idEgg, x, y, player.team_name);
    }

    eggDeath(id: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i] instanceof Egg) {
                var egg = Game.mapObject[i] as Egg;
                if (egg.id == id) {
                    this.reajustHeight(egg);
                    Game.scene.remove(egg.object3D);
                    Game.mapObject.splice(i, 1);
                    break;
                }
            }
        }
    }

    dropRessource(id: number, typeRes: number) {
        var player = this.findPlayer(id);
        new Food(typeRes, player.position.x, player.position.y);
        this.soundManager.playSound(Sound.POP_RESSOURCE, false);
    }

    collectRessource(id: number, typeRes: number) {
        var player = this.findPlayer(id);
        this.deleteFood(typeRes, player.position.x, player.position.y);
    }

    playerDead(id: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i] instanceof Player) {
                var player = Game.mapObject[i] as Player;
                if (player.id == id) {
                    this.reajustHeight(player);
                    Game.scene.remove(player.object3D);
                    Game.mapObject.splice(i, 1);
                    this.soundManager.playSound(Sound.VILLAGER_DEATH, false);
                    break;
                }
            }
        }
    }

    serverMessage(message: string) {
        console.log(message);
    }

    playerConnectionForEgg(e: number) {
        var egg = this.findEgg(e);
        this.eggDeath(e);
        this.spawnPlayer(e, egg.position.x, egg.position.y, 0, 1, egg.team_name);
    }

    hatchEgg(idEgg: number) {
    }

    clearMap() {
        Game.mapObject.forEach((val: MapObject) => {
            Game.scene.remove(val.object3D);
        });
        Game.mapObject = new Array<MapObject>();
    }
    
    clearCoordinate(x: number, y: number) {
        let index = Game.mapObject.findIndex((elem: MapObject) => {return elem.position.x == x && elem.position.y == y});

        while (index >= 0) {
            Game.scene.remove(Game.mapObject[index].object3D);
            Game.mapObject.splice(index, 1);
            index = Game.mapObject.findIndex((elem: MapObject) => {return elem.position.x == x && elem.position.y == y});
        }
    }
}
