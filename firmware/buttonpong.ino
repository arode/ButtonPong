// This #include statement was automatically added by the Particle IDE.
#include <InternetButtonEvents.h>
#include <InternetButton.h>

int gameState = 0; // 0 - gameover, 1 - waiting, 2 - responding

// if you have the original SparkButton, which does not have a buzzer or 
// a plastic enclosure to use, just add a '1' between the parentheses in 
// following line of code.
InternetButton b = InternetButton();

InternetButtonEvents buttonEvents = InternetButtonEvents(b);

void setup() {
    Serial.begin(9600);
    Particle.function("ping", ping);
    
    Particle.subscribe("hook-response/pong", registrationHandler);
    buttonEvents.onButtonClicked(buttonClickedHandler);
    buttonEvents.onAllButtonsClicked(allButtonsClickedHandler);

    b.begin(INTERNET_BUTTON_TYPE);
    
}

void loop(){
    buttonEvents.update();
    
    if (gameState == 0 && buttonEvents.allButtonsOn()) {
        b.allLedsOn(0,20,20);
    } else if (gameState == 1) {
        if (buttonEvents.buttonOn(1)) {
            b.ledOn(1,0,20,0);
            b.ledOn(11,0,20,0);
        } else {
            b.ledOff(1);
            b.ledOff(11);
        }
        
        if (buttonEvents.buttonOn(2)) {
            b.ledOn(2,0,0,20);
            b.ledOn(3,0,0,20);
            b.ledOn(4,0,0,20);
        } else {
            b.ledOff(2);
            b.ledOff(3);
            b.ledOff(4);
        }
        
        if (buttonEvents.buttonOn(3)) {
            b.ledOn(5,20,0,0);
            b.ledOn(6,20,0,0);
            b.ledOn(7,20,0,0);
        } else {
            b.ledOff(5);
            b.ledOff(6);
            b.ledOff(7);
        }
        
        if (buttonEvents.buttonOn(4)) {
            b.ledOn(8,20,20,0);
            b.ledOn(9,20,20,0);
            b.ledOn(10,20,20,0);
        } else {
            b.ledOff(8);
            b.ledOff(9);
            b.ledOff(10);
        }

    }
    else {
        b.allLedsOff();
    }
}

void allButtonsClickedHandler() {
    
    if (gameState == 0) {
        Particle.publish("register");
    }

}

void buttonClickedHandler(int buttonNumber) {
    if (gameState == 2) {
        Particle.publish("pong", "TRUE");
    }
}

void registrationHandler(const char *event, const char *data) {
    gameState = 1;
    b.allLedsOn(0,20,0);
    delay(500);
}

int ping(String countdown) {
    b.rainbow(5);
    
    if (gameState == 1) {
        gameState = 2;
    }
    
    return 1;
}
