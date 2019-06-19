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

// EventManager.getInstance().addListener("EventWebSocketConnected", (e: EventWebSocketConnected) => {
//     WebSocketManager.sendMessage("msz\n");
// });
//
//
// new GraphicProtocol();
// WebSocketManager.connect("localhost", 4244);

var game = new Game(0, 0);
