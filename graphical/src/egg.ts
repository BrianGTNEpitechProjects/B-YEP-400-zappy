import { MapObject } from "./map_object";
import { Game } from "./game";
import { Vector2, LatheBufferGeometry, Mesh } from "three";

export class Egg extends MapObject {
    id: number;
    constructor (id: number, x: number, y: number) {
        super(x, y, 0, Game.foodSize);
        this.id = id;
        this.position.z = this.getHeightCellsObject(x, y) + this.sizeZ / 2;

        var points = [];
        for ( var deg = 0; deg <= 180; deg += 6 ) {
            var rad = Math.PI * deg / 180;
            var point = new Vector2( ( 0.72 + .08 * Math.cos( rad ) ) * Math.sin( rad ), - Math.cos( rad ) ); // the "egg equation"
            //console.log( point ); // x-coord should be greater than zero to avoid degenerate triangles; it is not in this formula.
            points.push( point );
        }
        var geometry = new LatheBufferGeometry( points, 32 );
        var material = this.createMaterialTexture("assets/textures/egg.png", 0, 0);
        var egg = new Mesh(geometry, material);

        egg.position.x = x * Game.squareSize + Game.squareSize / 2;
        egg.position.y = y * Game.squareSize + Game.squareSize/ 2;
        egg.position.z = this.position.z;
        egg.rotation.x = 90 * Math.PI / 180;
        egg.scale.set(2.5, 2.5, 2.5);
        this.object3D = egg;
        Game.scene.add(egg);
        console.log(this)
        Game.mapObject.push(this);
    }
}
