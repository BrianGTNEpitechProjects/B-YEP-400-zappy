export class Food extends MapObject {
    constructor(type, assetName, scene) {
        var x = Math.floor(Math.random() * lines);
        var y = Math.floor(Math.random() * col);
        super(x, y, 0, 0,foodSize);
        var z = this.getHeightCellsObject(x, y) + this.sizeZ / 2;
        this.position.z = z;
        this.type = type;

        var geometry = new THREE.BoxGeometry(foodSize, foodSize, foodSize);
        var material = this.createMaterialTexture("assets/" + assetName + ".png");
        var food = new THREE.Mesh(geometry, material);

        food.position.x = x * squareSize + squareSize / 2;
        food.position.y = y * squareSize + squareSize/ 2;
        food.position.z = z;
        scene.add(food);
    }
}
