import { Game } from "./game";
import EventManager from "./EventManager";
import { EventWebSocketMessage } from "./ZEvent";
import WebSocketManager from "./WebSocketManager";

export default class GraphicProtocol {
    private commands: Map<string, (args: Array<string>) => void>;
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

        EventManager.getInstance().addListener("EventWebSocketMessage", (e: EventWebSocketMessage) => {
            var content: string = e.content;
            var commandList: Array<string> = content.split("\n");
            commandList.forEach(cmd => {
                var args = cmd.split(" ");
            
                this.commands.forEach((value: (args: Array<string>) => void, key: string) => {
                    if (key == args[0]) 
                        value(args);
                });
            });
        });
    }

    commandMsz(args: Array<string>) {
        let width: number = parseInt(args[1]);
        let height: number = parseInt(args[2]);
        setTimeout(() => {WebSocketManager.sendMessage("mct\n"); console.log("sltr")}, 1000)
        
        this.game = new Game(width, height);
    }

    commandBct(args: Array<string>) {
        let x: number = parseInt(args[1]);
        let y: number = parseInt(args[2]);
        let q1: number = parseInt(args[3]);
        let q2: number = parseInt(args[4]);
        let q3: number = parseInt(args[5]);
        let q4: number = parseInt(args[6]);
        let q5: number = parseInt(args[7]);
        let q6: number = parseInt(args[8]);
        let q7: number = parseInt(args[9]);
        
        this.game.setTile(x, y, q1, q2, q3, q4, q5, q6, q7);
    }

    commandTna(args: Array<string>) {
        console.log("Team: " + args[1]);
    }

    commandPia(args: Array<string>) {
        let teamName: string = args[1];
        let playersIds: Array<number> = new Array();

        for (let i: number = 2; i < args.length; i++) {
            playersIds.push(parseInt(args[i]));
        }

        console.log(`Team ${teamName} contains ${playersIds.length} players`);
    }

    commandPnw(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let X: number = parseInt(args[2]);
        let Y: number = parseInt(args[3]);
        let O: number = parseInt(args[4]);
        let level: number = parseInt(args[5]);
        let teamName: string = args[6]

        this.game.spawnPlayer(id, X, Y, O, level, teamName);
        console.log(`New player connected with id: ${id} at coordinate(${X}, ${Y}) Oriented ${O} with a level of ${level} his team name is ${teamName}`);
    }

    commandPpo(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let X: number = parseInt(args[2]);
        let Y: number = parseInt(args[3]);
        let O: number = parseInt(args[4]);

        this.game.setPlayerPos(id, X, Y, O);
        console.log(`player ${id} position is (${X}, ${Y}) and orientation is ${O}`);
    }

    commandPlv(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let level: number = parseInt(args[2]);

        this.game.setPlayerLevel(id, level);
        console.log(`level of player ${id} is ${level}`);
    }

    commandPin(args: Array<string>) {
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

        this.game.setPlayerInventory(id, x, y, q1, q2, q3, q4, q5, q6, q7);
    }

    commandPex(args: Array<string>) {
        let id: number = parseInt(args[1]);

        this.game.expulsePlayer(id);
    }

    commandPbc(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let message: string = args[2];

        for (let i = 3; i < args.length; i++) {
            message += args[i];
        }
        // TODO
        console.log(`Player ${id} broadcast message ${message}`);
    }

    commandPic(args: Array<string>) {
        let X: number = parseInt(args[1]);
        let Y: number = parseInt(args[2]);
        let level: number = parseInt(args[3]);
        let idStarted: number = parseInt(args[4]);
        let players: Array<number> = new Array(idStarted);

        for (let i = 5; i < args.length; i++) {
            players.push(parseInt(args[i]));
        }
        // TODO
        console.log(`Incantation started by player ${idStarted} from level ${level} at (${X}, ${Y}) with ${players.length} player`);
    }

    commandPie(args: Array<string>) {
        let X: number = parseInt(args[1]);
        let Y: number = parseInt(args[2]);

        // TODO
        console.log(`Incantation at (${X}, ${Y}) ended`);
    }

    commandPfk(args: Array<string>) {
        let id: number = parseInt(args[1]);
        
        // TODO (maybe)
        console.log(`Player ${id} laying an egg`);
    }

    commandPdr(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let resourceId: number = parseInt(args[2]);

        this.game.dropRessource(id, resourceId);
        console.log(`Player ${id} drop resource ${resourceId}`);
    }

    commandPgt(args: Array<string>) {
        let id: number = parseInt(args[1]);
        let resourceId: number = parseInt(args[2]);

        this.game.collectRessource(id, resourceId);
        console.log(`Player ${id} collecting resource ${resourceId}`);
    }

    commandPdi(args: Array<string>) {
        let id: number = parseInt(args[1]);

        this.game.playerDead(id);
        console.log(`player ${id} is now dead`);
    }

    commandEnw(args: Array<string>) {
        let eggId: number = parseInt(args[1]);
        let playerId: number = parseInt(args[2]);
        let X: number = parseInt(args[3]);
        let Y: number = parseInt(args[4]);
        
        this.game.spawnEgg(eggId, playerId, X, Y);
        console.log(`Egg with id ${eggId} was laid by the player ${playerId} at (${X}, ${Y})`);
    }

    commandEht(args: Array<string>) {
        let eggId: number = parseInt(args[1]);

        // TODO 
        console.log(`An egg have hatch ${eggId}`);
    }

    commandEbo(args: Array<string>) {
        let id: number = parseInt(args[1]);
        
        this.game.playerConnectionForEgg(id);
        console.log(`A new player is connected and take the egg ${id}`);
    }

    commandEdi(args: Array<string>) {
        let id: number = parseInt(args[1]);

        // TODO
        console.log(`Egg ${id} was dead`);
    }

    commandSgt(args: Array<string>) {
        let timeUnit: number = parseInt(args[1]);

        // TODO
        console.log(`Current time unit is: ${timeUnit}`);
    }

    commandSst(args: Array<string>) {
        let timeUnit: number = parseInt(args[1]);

        // TODO
        console.log(`New time unit is: ${timeUnit}`);
    }

    commandSeg(args: Array<string>) {
        // TODO
        console.log(`end of game`);
    }

    commandSmg(args: Array<string>) {
        console.log("[ZAPPY GRAPHICAL PROTOCOL SERVER] New message: " + args[1]);
    }

    commandSuc(args: Array<string>) {
        console.error("[ZAPPY GRAPHICAL PROTOCOL SERVER] Unknown Command");
    }

    commandSbp(args: Array<string>) {
        console.error("[ZAPPY GRAPHICAL PROTOCOL SERVER] Invalid parameter");
    }
}