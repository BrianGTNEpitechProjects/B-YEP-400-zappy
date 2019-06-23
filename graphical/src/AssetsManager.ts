import { Material, TextureLoader, RepeatWrapping, MeshBasicMaterial } from "three";
import Game from "./game";

export default class AssetsManager {
    
    private static instance: AssetsManager = new AssetsManager();

    static getInstance(): AssetsManager {
        return AssetsManager.instance;
    }

    static getAsset(name: string): Material {
        return this.getInstance().get(name);
    }


    private assets: Map<string, Material>;

    constructor() {
        this.assets = new Map();
    }

    load() {
        this.assets.set("melon", this.createMaterialTexture("assets/textures/melon_side.png", 0, 0));
        this.assets.set("iron_ore", this.createMaterialTexture("assets/textures/iron_ore.png", 0, 0));
        this.assets.set("iron_block", this.createMaterialTexture("assets/textures/iron_block.png", 0, 0));
        this.assets.set("gold_ore", this.createMaterialTexture("assets/textures/gold_ore.png", 0, 0));
        this.assets.set("gold_block", this.createMaterialTexture("assets/textures/gold_block.png", 0, 0));
        this.assets.set("diamond_ore", this.createMaterialTexture("assets/textures/diamond_ore.png", 0, 0));
        this.assets.set("diamond_block", this.createMaterialTexture("assets/textures/diamond_block.png", 0, 0));
        this.assets.set("egg", this.createMaterialTexture("assets/textures/egg.png", 0, 0));
        this.assets.set("dirt", this.createMaterialTexture("assets/textures/dirt.png", Game.lines, Game.col));
    }

    get(name: string): Material {
        return this.assets.get(name);
    }

    createMaterialTexture(textureName: string, repeatX: number, repeatY: number): MeshBasicMaterial {
        var texture = new TextureLoader().load(textureName);

        texture.wrapS = texture.wrapT = RepeatWrapping;
        if (repeatX && repeatY) {
            texture.offset.set(0, 0);
            texture.repeat.set(repeatX, repeatY);
        }
        return new MeshBasicMaterial({map: texture});
    }

}