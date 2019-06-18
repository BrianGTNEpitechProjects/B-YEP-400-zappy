import { PerspectiveCamera, Scene, WebGLRenderer, TextureLoader, MeshBasicMaterial, RepeatWrapping } from 'three';
import { OrbitControls } from "three-orbitcontrols-ts";
import { Map } from "./map"
import { Food } from './food';
import { MapObject } from './map_object';
import { Player } from './player';
import { Egg } from './egg';
const loader = require('three-gltf-loader');

export class Game {
    static mapObject: Array<MapObject> = new Array<MapObject>();
    static lines:number = 10;
    static col:number = 11;
    static squareSize:number = 10;
    static foodSize:number = Game.squareSize / 2;
    static scene: Scene = new Scene();
    static gltfLoader = new loader();
    camera: PerspectiveCamera;
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
        this.camera = new PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        this.renderer = new WebGLRenderer({antialias:true});
        this.controls = new OrbitControls(this.camera, this.renderer.domElement);

        this.camera.position.set(50, 50, 100);
        window.addEventListener('resize', this.onWindowResize.bind(this), false);
        document.body.appendChild(this.renderer.domElement);
        this.controls.target.set(50, 50, 0);
        this.controls.update();
        this.animate();
        this.onWindowResize();
        this.map = new Map();
        // var that = this;
        // new Player(1, 5, 1, 1, "LECUL");
        // setTimeout(function () {that.dropRessource(1, 6);}, 1000);
        // setTimeout(function () {that.collectRessource(1, 6);}, 2000);
        // // this.setTile(1, 1, 3, 2, 1, 0, 1, 0, 1);
        // // setTimeout(function () {that.spawnPlayer(1, 1, 1, 1, 1, "LE CUL");}, 1000);
        // // setTimeout(function () {new Food(5, 1, 1);}, 2000);
        // var that = this;
        // setTimeout(function (){that.setPlayerPos(1, 2, 2, 1);}, 3000);
        // setTimeout(function (){that.setPlayerPos(1, 5, 1, 1);}, 4000);
        // // setTimeout(function (){that.deleteFood(1, 1, 1);}, 4000);
    }

    spawnPlayer(id: number, x: number, y: number, orientation: number, level: number, team_name: string) {
        new Player(id, x, y, level, team_name);
    }

    setPlayerPos(id: number, x: number, y: number, orientation: number) {
        var player = this.findPlayer(id);
        this.reajustHeight(player);
        player.moovePlayer(x, y);
    }

    findPlayer(id: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            var player = Game.mapObject[i] as Player;
            if (player.id == id) {
                return player;
            }
        }
    }

    addTeamName(name: string) {
    }

    setPlayerLevel(id: number, level: number) {
        var player = this.findPlayer(id);
        player.setLevel(level);
    }

    setPlayerInventory(id: number, x: number, y: number, res0: number, res1: number, res2: number, res3: number, res4: number, res5: number, res6: number) {
    }

    expulsePlayer(id: number) {
        var player = this.findPlayer(id);
        Game.scene.remove(player.object3D);
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
        this.camera.aspect = window.innerWidth / window.innerHeight;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    animate() {
        requestAnimationFrame(()=>this.animate());
        this.renderer.render(Game.scene, this.camera);
    }

    deleteFood(type: number, posX: number, posY: number) {
        for (var i = 0; i < Game.mapObject.length; i++) {
            if (Game.mapObject[i].position.x == posX && Game.mapObject[i].position.y == posY && Game.mapObject[i] instanceof Food) {
                var food = Game.mapObject[i] as Food;
                if (food.type == type) {
                    this.reajustHeight(Game.mapObject[i]);
                    Game.scene.remove(food.object3D);
                    Game.mapObject.splice(i, 1);
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

    // initiateIntervalSpawnFood() {
    //     var that = this;
    //     setInterval(function() { that.spawnFood(1, "textures/iron_ore");}, 3000);
    //     setInterval(function() { that.spawnFood(2, "textures/iron_block");}, 4500);
    //     setInterval(function() { that.spawnFood(3, "textures/gold_ore");}, 6000);
    //     setInterval(function() { that.spawnFood(4, "textures/gold_block");}, 7500);
    //     setInterval(function() { that.spawnFood(5, "textures/diamond_ore");}, 9000);
    //     setInterval(function() { that.spawnFood(6, "textures/diamond_block");}, 10500);
    // }

    spawnEgg(idEgg: number, idPlayer: number, x: number, y: number) {
        new Egg(idEgg, x, y);
    }

    dropRessource(id: number, typeRes: number) {
        var player = this.findPlayer(id);
        new Food(typeRes, player.position.x, player.position.y);
    }

    collectRessource(id: number, typeRes: number) {
        var player = this.findPlayer(id);
        this.deleteFood(typeRes, player.position.x, player.position.y);
    }
}
