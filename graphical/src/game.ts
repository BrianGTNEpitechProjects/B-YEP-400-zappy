import { PerspectiveCamera, Scene, WebGLRenderer, TextureLoader, MeshBasicMaterial, RepeatWrapping, Color } from 'three';
import { OrbitControls } from "three-orbitcontrols-ts";
import { Map } from "./map"
import { Food } from './food';
import { MapObject } from './map_object';
import { Player, Orientation } from './player';
import { Egg } from './egg';
import { SoundManager, Sound } from './sound_manager';
const loader = require('three-gltf-loader');

export default class Game {
    static mapObject: Array<MapObject> = new Array<MapObject>();
    static lines:number = 10;
    static col:number = 11;
    static squareSize:number = 10;
    static foodSize:number = Game.squareSize / 2;
    static scene: Scene = new Scene();
    static gltfLoader = new loader();
    static camera = new PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    soundManager: SoundManager;
    renderer: WebGLRenderer;
    controls: OrbitControls;
    map: Map;

    constructor(lineSize: number, colSize: number) {
        if (lineSize) {
            Game.lines = lineSize;
        }
        if (colSize) {
            Game.col = colSize;
        }
        this.renderer = new WebGLRenderer({antialias:true});
        this.controls = new OrbitControls(Game.camera, this.renderer.domElement);
        this.soundManager = new SoundManager();

        Game.camera.position.set(50, 50, 100);
        window.addEventListener('resize', this.onWindowResize.bind(this), false);
        document.body.appendChild(this.renderer.domElement);
        this.controls.target.set(50, 50, 0);
        this.controls.update();
        this.animate();
        this.onWindowResize();
        this.map = new Map();
        this.soundManager.playSound(Sound.MINECRAFT_MUSIC, true);




        this.spawnPlayer(1, 1, 2, 1, 1, "OUI");

        var that = this;
        setTimeout(function () {that.setPlayerLevel(1, 10);}, 1500);
        setTimeout(function () {that.spawnEgg(2, 1, 1, 1);}, 2000);
        setTimeout(function () {that.setPlayerPos(1, 1, 1, 0);}, 1500);
        setTimeout(function () {that.dropRessource(1, 1);}, 3000);
        setTimeout(function () {that.spawnPlayer(3, 1, 1, 1, 1, "OUI");}, 3500);
        setTimeout(function () {that.spawnPlayer(4, 1, 1, 1, 1, "OUI");}, 4000);
        setTimeout(function () {that.expulsePlayer(1,);}, 5000);
    }

    spawnPlayer(id: number, x: number, y: number, orientation: number, level: number, team_name: string) {
        new Player(id, x, y, level, team_name, orientation);
        this.soundManager.playSound(Sound.VILLAGER_HUM, false);
    }

    setPlayerPos(id: number, x: number, y: number, orientation: number) {
        var player = this.findPlayer(id);
        this.reajustHeight(player);
        player.moovePlayer(x, y, orientation);
    }

    findPlayer(id: number) {
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

    setTile(x: number, y: number, res0: number, res1: number, res2: number, res3: number, res4: number, res5: number, res6: number) {
        var numberRessources = [res0, res1, res2, res3, res4, res5, res6];

        for (var i = 0; i < numberRessources.length; i++) {
            for (var j = 0; j < numberRessources[i]; j++) {
                new Food(i, x, y);
            }
        }
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
        Game.camera.aspect = window.innerWidth / window.innerHeight;
        Game.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    animate() {
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
}
