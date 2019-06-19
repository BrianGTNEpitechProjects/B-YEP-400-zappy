import EventManager from "./EventManager";
import { EventWebSocketConnected, EventWebSocketMessage } from "./ZEvent";

export default class WebSocketManager {
    private static ws: WebSocket = undefined;

    static connect(url: string = "localhost", port: number = 4242): WebSocket {
        var ws: WebSocket = new WebSocket(`ws://${url}:${port}`);
        
        ws.onopen = (ev: Event) => {
            EventManager.getInstance().emit(new EventWebSocketConnected());
        };

        ws.onmessage = (ev: MessageEvent) => {
            EventManager.getInstance().emit(new EventWebSocketMessage(ev.data));
        }

        this.ws = ws;
        return WebSocketManager.ws;
    }

    static sendMessage(toSend: string | ArrayBufferLike | Blob | ArrayBufferView): void {
        this.ws.send(toSend);
    }
}