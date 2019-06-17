import { Color, PerspectiveCamera, Scene, WebGLRenderer, Camera } from 'three';

var scene: Scene = new Scene();
var camera: Camera = new PerspectiveCamera(45, innerWidth / innerHeight, 0.1, 10000);
var renderer: WebGLRenderer = new WebGLRenderer({antialias: true, canvas: document.getElementById('main-canvas') as HTMLCanvasElement});
renderer.setClearColor(new Color('rgb(0, 0, 0)'));
renderer.setSize(innerWidth, innerHeight);
renderer.render(scene, camera);