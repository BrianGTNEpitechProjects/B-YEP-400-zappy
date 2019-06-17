export class Map extends MapObject {
    constructor(scene) {
        super();
        var geometryPlane = new THREE.PlaneGeometry(lines * squareSize, col * squareSize, 1);
        var materialPlane = this.createMaterialTexture("assets/textures/dirt.png", lines, col);
        var plane = new THREE.Mesh(geometryPlane, materialPlane);

        plane.position.x = lines * squareSize / 2;
        plane.position.y = col * squareSize / 2;
        scene.add(plane);
    }
}
