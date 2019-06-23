import Game from "./game";
import EventManager from "./EventManager";
import { EventWebSocketMessage, GameLoadedEvent } from "./ZEvent";
import WebSocketManager from "./WebSocketManager";
import Logger from "./Logger";
import { Vector, Vector2 } from "three";

export default class GraphicProtocol {
    private commands: Map<string, (args: Array<string>, protocol: GraphicProtocol) => void>;
    private game: Game;

    constructor() {
        this.commands = new Map();

        this.commands.set("msz", this.commandMsz);
        this.commands.set("bct", this.commandBct);
        this.commands.set("tna", this.commandTna);
        this.commands.set("pia", this.commandPia);
        this.commands.set("pnw", this.commandPnw);
        this.commands.set("ppo", this.commandPpo);
        this.commands.set("plv", this.commandPlv);
        this.commands.set("plu", this.commandPlu);
        this.commands.set("pin", this.commandPin);
        this.commands.set("pex", this.commandPex);
        this.commands.set("pbc", this.commandPbc);
        this.commands.set("pic", this.commandPic);
        this.commands.set("pie", this.commandPie);
        this.commands.set("pfk", this.commandPfk);
        this.commands.set("pdr", this.commandPdr);
        this.commands.set("pgt", this.commandPgt);
        this.commands.set("pdi", this.commandPdi);
        this.commands.set("enw", this.commandEnw);
        this.commands.set("eht", this.commandEht);
        this.commands.set("ebo", this.commandEbo);
        this.commands.set("edi", this.commandEdi);
        this.commands.set("sgt", this.commandSgt);
        this.commands.set("sst", this.commandSst);
        this.commands.set("seg", this.commandSeg);
        this.commands.set("smg", this.commandSmg);
        this.commands.set("suc", this.commandSuc);
        this.commands.set("sbp", this.commandSbp);

        var that = this;
        EventManager.getInstance().addListener("EventWebSocketMessage", (e: EventWebSocketMessage) => {
            var content: string = e.content;
            var commandList: Array<string> = content.split("\n");
            commandList.forEach(cmd => {
                var args = cmd.split(" ");

                that.commands.forEach((value: (args: Array<string>, protocol: GraphicProtocol) => void, key: string) => {
                    if (key == args[0])
                        value(args, that);
                });
            });
        });
    }

    reloadMap() {
        if (!this.game)
            return;
        this.game.visibleCase.forEach((pos: Vector2) => {
            WebSocketManager.sendMessage(`bct ${pos.x} ${pos.y}\n`);
        });
    }

    getGame(): Game {
        return this.game;
    }

    commandMsz(args: Array<string>, protocol: GraphicProtocol) {
        let width: number = parseInt(args[1]);
        let height: number = parseInt(args[2]);
        
        WebSocketManager.sendMessage("tna\n");
        protocol.game = new Game(width, height, protocol);
        protocol.reloadMap();
    }

    commandBct(args: Array<string>, protocol: GraphicProtocol) {
        let x: number = parseInt(args[1]);
        let y: number = parseInt(args[2]);
        let q1: number = parseInt(args[3]);
        let q2: number = parseInt(args[4]);
        let q3: number = parseInt(args[5]);
        let q4: number = parseInt(args[6]);
        let q5: number = parseInt(args[7]);
        let q6: number = parseInt(args[8]);
        let q7: number = parseInt(args[9]);

        protocol.game.setTileContent(x, y, q1, q2, q3, q4, q5, q6, q7);
    }

    commandTna(args: Array<string>, protocol: GraphicProtocol) {
        let teams: Array<string> = new Array();
        
        for (let i = 1; i < args.length; i++) {
            teams.push(args[i]);
            Logger.logMessage("Get team: " + args[i]);
        }
    }

    commandPia(args: Array<string>, protocol: GraphicProtocol) {
        let teamName: string = args[1];
        let playersIds: Array<number> = new Array();

        for (let i: number = 2; i < args.length; i++) {
            playersIds.push(parseInt(args[i]));
        }

        console.log(`Team ${teamName} contains ${playersIds.length} players`);
    }

    commandPnw(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1].split("#")[1]);
        let X: number = parseInt(args[2]);
        let Y: number = parseInt(args[3]);
        let O: number = parseInt(args[4]);
        let level: number = parseInt(args[5]);
        let teamName: string = args[6]

        Logger.logMessage(`New player connected with id: ${id} at coordinate(${X}, ${Y}) Oriented ${O} with a level of ${level} his team name is ${teamName}`)
        protocol.game.spawnPlayer(id, X, Y, O, level, teamName);
    }

    commandPpo(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let X: number = parseInt(args[2]);
        let Y: number = parseInt(args[3]);
        let O: number = parseInt(args[4]);

        protocol.game.setPlayerPos(id, X, Y, O);
        console.log(`player ${id} position is (${X}, ${Y}) and orientation is ${O}`);
    }

    commandPlv(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let level: number = parseInt(args[2]);

        protocol.game.setPlayerLevel(id, level);
        console.log(`level of player ${id} is ${level}`);
    }

    commandPlu(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let level: number = parseInt(args[2]);

        Logger.logMessage(`Player ${id} leveled up to ${level}`);
    }

    commandPin(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let x: number = parseInt(args[2]);
        let y: number = parseInt(args[3]);
        let q1: number = parseInt(args[4]);
        let q2: number = parseInt(args[5]);
        let q3: number = parseInt(args[6]);
        let q4: number = parseInt(args[7]);
        let q5: number = parseInt(args[8]);
        let q6: number = parseInt(args[9]);
        let q7: number = parseInt(args[10]);

        protocol.game.setPlayerInventory(id, x, y, q1, q2, q3, q4, q5, q6, q7);
    }

    commandPex(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);

        Logger.logMessage(`Player ${id} expulse player on his case`);
        protocol.game.expulsePlayer(id);
    }

    commandPbc(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let message: string = args[2];

        for (let i = 3; i < args.length; i++) {
            message += args[i];
        }
        
        Logger.logMessage(`[BROADCAST] ${id}: ${message}`);
        console.log(`Player ${id} broadcast message ${message}`);
    }

    commandPic(args: Array<string>, protocol: GraphicProtocol) {
        let X: number = parseInt(args[1]);
        let Y: number = parseInt(args[2]);
        let level: number = parseInt(args[3]);
        let id: number = parseInt(args[4]);

        // TODO
        Logger.logMessage(`Player ${id} started incantation from level ${level} at (${X}, ${Y})`);
    }

    commandPie(args: Array<string>, protocol: GraphicProtocol) {
        let X: number = parseInt(args[1]);
        let Y: number = parseInt(args[2]);

        // TODO
        Logger.logMessage(`Incantation at (${X}, ${Y}) ended`);
    }

    commandPfk(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);

        // TODO (maybe)
        Logger.logMessage(`Player ${id} laying an egg`);
    }

    commandPdr(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let resourceId: number = parseInt(args[2]);

        protocol.game.dropRessource(id, resourceId);
        Logger.logMessage(`Player ${id} drop resource ${resourceId}`);
    }

    commandPgt(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);
        let resourceId: number = parseInt(args[2]);

        protocol.game.collectRessource(id, resourceId);
        Logger.logMessage(`Player ${id} collecting resource ${resourceId}`);
    }

    commandPdi(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);

        protocol.game.playerDead(id);
        Logger.logWarning(`player ${id} is now dead`);
    }

    commandEnw(args: Array<string>, protocol: GraphicProtocol) {
        let eggId: number = parseInt(args[1]);
        let playerId: number = parseInt(args[2]);
        let X: number = parseInt(args[3]);
        let Y: number = parseInt(args[4]);

        protocol.game.spawnEgg(eggId, playerId, X, Y);
        Logger.logMessage(`Egg with id ${eggId} was laid by the player ${playerId} at (${X}, ${Y})`);
    }

    commandEht(args: Array<string>, protocol: GraphicProtocol) {
        let eggId: number = parseInt(args[1]);

        // TODO
        Logger.logMessage(`An egg have hatch ${eggId}`);
    }

    commandEbo(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);

        protocol.game.playerConnectionForEgg(id);
        Logger.logMessage(`A new player is connected and take the egg ${id}`);
    }

    commandEdi(args: Array<string>, protocol: GraphicProtocol) {
        let id: number = parseInt(args[1]);

        // TODO
        Logger.logWarning(`Egg ${id} was dead`);
    }

    commandSgt(args: Array<string>, protocol: GraphicProtocol) {
        let timeUnit: number = parseInt(args[1]);

        // TODO
        Logger.logWarning(`Current time unit is: ${timeUnit}`);
    }

    commandSst(args: Array<string>, protocol: GraphicProtocol) {
        let timeUnit: number = parseInt(args[1]);

        // TODO
        Logger.logWarning(`New time unit is: ${timeUnit}`);
    }

    commandSeg(args: Array<string>, protocol: GraphicProtocol) {
        // TODO
        Logger.logWarning(`end of game`);
    }

    commandSmg(args: Array<string>, protocol: GraphicProtocol) {
        Logger.logError("[ZAPPY GRAPHICAL PROTOCOL SERVER] New message: " + args[1]);
    }

    commandSuc(args: Array<string>, protocol: GraphicProtocol) {
        Logger.logError("[ZAPPY GRAPHICAL PROTOCOL SERVER] Unknown Command");
    }

    commandSbp(args: Array<string>, protocol: GraphicProtocol) {
        Logger.logError("[ZAPPY GRAPHICAL PROTOCOL SERVER] Invalid parameter");
    }
}
