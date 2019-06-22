export default abstract class ZEvent {
    abstract getName(): string;
}

export class EventWebSocketConnected extends ZEvent {
    getName(): string {
        return "EventWebSocketConnected";
    }
}

export class EventWebSocketConnectionFailed extends ZEvent {
    getName(): string {
        return "EventWebSocketConnectionFailed";
    }
}

export class EventWebSocketMessage extends ZEvent {
    content: string;

    constructor(content: string) {
        super();
        this.content = content;
    }
    
    getName(): string {
        return "EventWebSocketMessage";
    }
}

export class GameLoadedEvent extends ZEvent {
    getName(): string {
        return "GameLoadedEvent";
    }
}