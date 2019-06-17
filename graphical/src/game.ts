export class Game {
    scene: THREE.Scene;
    camera: THREE.PerspectiveCamera;
    renderer: THREE.WebGLRenderer;

    constructor() {
        this.scene = new THREE.Scene();
        this.camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        this.renderer = new THREE.WebGLRenderer({antialias:true});
        this.controls = new THREE.OrbitControls(this.camera, this.renderer.domElement);

        this.camera.position.set(50, 50, 100);
        window.addEventListener('resize', this.onWindowResize.bind(this), false);
        document.body.appendChild(this.renderer.domElement);
        this.controls.target.set(50, 50, 0);
        this.controls.update();
        this.animate();
        this.map = new Map(this.scene);
        this.initiateIntervalSpawnFood();
    }

    onWindowResize() {
        this.camera.aspect = window.innerWidth / window.innerHeight;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    animate() {
        requestAnimationFrame(()=>this.animate());
        this.renderer.render(this.scene, this.camera);
    }

    initiateIntervalSpawnFood() {
        var that = this;
        setInterval(function() { that.spawnFood(1, "textures/iron_ore");}, 3000);
        setInterval(function() { that.spawnFood(1, "textures/iron_block");}, 4500);
        setInterval(function() { that.spawnFood(1, "textures/gold_ore");}, 6000);
        setInterval(function() { that.spawnFood(1, "textures/gold_block");}, 7500);
        setInterval(function() { that.spawnFood(1, "textures/diamond_ore");}, 9000);
        setInterval(function() { that.spawnFood(1, "textures/diamond_block");}, 10500);
    }

    spawnFood(type, texture) {
        var food = new Food(type, texture, this.scene);
        mapObject.push(food);
    }
}
