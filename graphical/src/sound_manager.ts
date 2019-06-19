import { Audio, AudioListener, AudioLoader } from "three";
import { Game } from "./game";

export enum Sound {
}

var sounds = [
    ""
];

export class SoundManager {
    listener: AudioListener;
    audio: Audio;
    audioLoader: AudioLoader;

    constructor() {
        this.listener = new AudioListener();
        Game.camera.add(this.listener);
        this.audio = new Audio(this.listener);
        Game.scene.add(this.audio);
        this.audioLoader = new AudioLoader();
        var that = this;
        this.audioLoader.load(
            'assets/sounds/minecraft_classic.mp3',
            function( audioBuffer: any) {
                that.audio.setBuffer( audioBuffer );
                that.audio.setLoop( true );
                that.audio.setVolume( 0.5 );
                that.audio.play();
            },
            function ( xhr: any ) {
                console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
            },
            function ( _err: any ) {
                console.log( 'An error happened' );
            }
        );

        // for (var i = 0; i < sounds.length; i++) {
        //     this.audioLoader.load(
        //         'sounds/ambient.ogg',
        //         function( audioBuffer: any) {
        //             that.audio.setBuffer( audioBuffer );
        //             that.audio.setLoop( true );
        //             that.audio.setVolume( 0.5 );
        //             that.audio.play();
        //         },
        //         function ( xhr: any ) {
        //             console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
        //         },
        //         function ( err: any ) {
        //             console.log( 'An error happened' );
        //         }
        //     );
        // }
    }
}
