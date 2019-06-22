export default class Logger {
    
    static logError(message: string) {
        message = "[ERROR] " + message;
        this.logMessage(message, "rgb(255, 0, 0)")
    }

    static logWarning(message: string) {
        message = "[WARNING] " + message;
        this.logMessage(message, "rgb(255, 69, 0)");
    }

    static logMessage(message: string, color: string = "rgb(0, 0, 0)") {
        let htmlElement: HTMLElement = document.getElementById("logBox");

        htmlElement.innerHTML += `<p style="color: ${color}">${message}</p>`;
    }

}