import ZEvent from './ZEvent'

export default class EventManager {
    public static instance: EventManager;

    static getInstance() {
        if (!EventManager.instance)
            EventManager.instance = new EventManager();
        return EventManager.instance;
    }

    /**
     * Non Static
     */

    private id: number;
    private events: Array<[number, string, (e: ZEvent) => void]>;

    private constructor() { 
        this.events = new Array<[number, string, (e: ZEvent) => void]>();
        this.id = 0;
    }

    emit(event: ZEvent) {
        this.events.forEach(element => {
            if (element[1] == event.getName())
                element[2](event);
        });
    }
    
    addListener(name: string, callback: (e: ZEvent) => void): number {
        this.events.push([this.id, name, callback]);
        return this.id++;
    }

    removeListener(id: number) {
        var index: number = this.events.findIndex(event => event[0] == id);
        this.events.splice(index, 1);
    }

}