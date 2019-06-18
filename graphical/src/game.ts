import { PerspectiveCamera, Scene, WebGLRenderer, TextureLoader, MeshBasicMaterial, RepeatWrapping } from 'three';
import { OrbitControls } from "three-orbitcontrols-ts";
import { Map } from "./map"
import { Food } from './food';
import { MapObject } from './map_object';
import { Player } from './player';
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
        new Food(1, 2, 2);
        new Food(2, 2, 2);
        new Player(2, 2);
        var that = this;
        setTimeout(function(){that.deleteFood(1, 2, 2);}, 2000);
        setTimeout(function(){new Food(1, 2, 2);}, 3000);
        // new Food(1, 2, 2);
        // this.initiateIntervalSpawnFood();
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
                    for (var j = 0; j < Game.mapObject.length; j++) {
                        if (Game.mapObject[j].position.x == posX && Game.mapObject[j].position.y == posY && Game.mapObject[j].position.z > Game.mapObject[i].position.z) {
                            Game.mapObject[j].position.z -= Game.mapObject[i].sizeZ;
                            Game.mapObject[j].object3D.position.z -= Game.mapObject[i].sizeZ;
                        }
                    }
                    Game.scene.remove(food.object3D);
                    Game.mapObject.splice(i, 1);
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

    // spawnFood(type: number, texture: string) {
    //     var food = new Food(type, texture);
    //     // Game.mapObject.push(food);
    // }
}
