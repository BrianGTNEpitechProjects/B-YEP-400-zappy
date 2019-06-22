import Game from "./game";
import EventManager from "./EventManager";
import WebSocketManager from "./WebSocketManager";
import { EventWebSocketConnected, EventWebSocketMessage } from "./ZEvent";
import GraphicProtocol from "./GraphicProtocol";

// import { Color, PerspectiveCamera, Scene, WebGLRenderer, Camera } from 'three';
// import { OrbitControls } from "three-orbitcontrols-ts";
// import GLTFLoader from "three-gltf-loader";
//
// var scene: Scene = new Scene();
// var camera: Camera = new PerspectiveCamera(45, innerWidth / innerHeight, 0.1, 10000);
// var renderer: WebGLRenderer = new WebGLRenderer({antialias: true, canvas: document.getElementById('main-canvas') as HTMLCanvasElement});
// renderer.setClearColor(new Color('rgb(0, 0, 0)'));
// renderer.setSize(innerWidth, innerHeight);
// renderer.render(scene, camera);

var formConnection = document.getElementById("connection");
var waiting = document.getElementById("waiting");
var game = document.getElementById("game");

game.style.display = "none";
waiting.style.display = "none";

run();

function run() 
{
    let hostElement: HTMLInputElement = <HTMLInputElement>document.getElementById("host");
    let portElement: HTMLInputElement = <HTMLInputElement>document.getElementById("port");
    let connectButtonElement: HTMLButtonElement = <HTMLButtonElement>document.getElementById("connectButton");

    connectButtonElement.onclick = (ev: MouseEvent) => {
        formConnection.style.display = 'none';
        startGame(hostElement.value, parseInt(portElement.value));
    }
}

function startGame(host: string, port: number) {
    game.style.display = 'block';

    EventManager.getInstance().addListener("EventWebSocketConnected", (e: EventWebSocketConnected) => {
        WebSocketManager.sendMessage("msz\n");
    });

    var protocol = new GraphicProtocol();
    let reloadMapElement: HTMLButtonElement = <HTMLButtonElement>document.getElementById("reloadMap");


    reloadMapElement.onclick = (ev: MouseEvent) => {
        let game: Game = protocol.getGame();
        protocol.reloadMap();
    }
    WebSocketManager.connect(host, port);
}