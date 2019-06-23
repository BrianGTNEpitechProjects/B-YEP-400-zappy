import { Audio, AudioListener, AudioLoader } from "three";
import Game from "./game";

export enum Sound {
    MINECRAFT_MUSIC = 0,
    VILLAGER_HUM,
    VILLAGER_DEATH,
    VILLAGER_HIT,
    LEVELUP,
    POP_RESSOURCE
};

var soundsAssets = [
    "assets/sounds/minecraft_classic.mp3",
    "assets/sounds/villager_hum.mp3",
    "assets/sounds/villager_death.mp3",
    "assets/sounds/villager_hit.mp3",
    "assets/sounds/levelup.mp3",
    "assets/sounds/pop.mp3"
];

export class SoundManager {
    listener: AudioListener;
    audioLoader: AudioLoader;

    constructor() {
        this.listener = new AudioListener();
        Game.camera.add(this.listener);
        this.audioLoader = new AudioLoader();
    }

    playSound(sound: number, repeat: boolean) {
        var audio = new Audio(this.listener);
        this.audioLoader.load(
            soundsAssets[sound],
            function( audioBuffer: any) {
                audio.setBuffer( audioBuffer );
                audio.setVolume( 0.5 );
                audio.setLoop(repeat);
                audio.play();
            },
            function ( xhr: any ) {
                console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
            },
            function ( _err: any ) {
                console.log( 'An error happened' );
            }
        );
    }
}
