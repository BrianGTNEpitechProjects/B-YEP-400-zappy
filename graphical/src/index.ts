import Game from "./game";
import EventManager from "./EventManager";
import WebSocketManager from "./WebSocketManager";
import { EventWebSocketConnected, EventWebSocketMessage, EventWebSocketError } from "./ZEvent";
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

    EventManager.getInstance().addListener("EventWebSocketConnected", (e: EventWebSocketConnected) => {
        game.style.display = 'block';
        WebSocketManager.sendMessage("msz\n");
    });

    EventManager.getInstance().addListener("EventWebSocketError", (e: EventWebSocketError) => {
        waiting.style.display = "block";
    });

    var protocol = new GraphicProtocol();
    WebSocketManager.connect(host, port);
}