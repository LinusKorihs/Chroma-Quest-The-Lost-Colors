/*
#include "config.h" //Inkludieren aller Header-Dateien
#include <cstdlib>
#include <iostream>
#include "raylib.h"
#include "tileson.h"

const int buttonWidth = 150;
const int buttonHeight = 30;
const int buttonScreenWidth = PixelGame::ScreenWidth / 2 - 50;
int setKeyBindText = 0;
int countDrawText = 0;

enum VolumeType{ //Enum für die verschiedenen Soundtypen  
    Global,
    BGMusic,
    SFX
};

enum Direction { //Enum für die verschiedenen Richtungen  
    NONE = -1,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum MenuType { //Enum für die verschiedenen Menütypen  
    None,
    VolumeSliders,
    Control,
    Language
};

class GameState{
public:
    int globalVolume = 50;
    int globalMusicVolume = 50;
    int globalSFXVolume = 50;
    int gameIsRunning = 1;
    int jumpToSettings = 0;
    bool isKeyBindingsOpen = false;
    bool isPaused = false;
    Sound walkingSound;
    Music backgroundMusic;
    Texture2D myTexture;
    Texture2D myMC;
    MenuType activeMenu = None;
    const float moveSpeed = 2.0f;
    const int targettedFps = 60;
    std::map<Direction, int> keyBindings ={
            {UP, KEY_W},
            {DOWN, KEY_S},
            {LEFT, KEY_A},
            {RIGHT, KEY_D}
    };
    std::pair<Direction, int> lastChangedKey = {NONE, -1};
    Direction selectedKey;
    bool isWaitingForKey = false;

    void resetKeyBindingState()
    {
        isWaitingForKey = false;
        selectedKey = NONE;
    }

    enum Language { //Enum für die verschiedenen Sprachen  
        English,
        German
    };

    Language currentLanguage = English;

    const char* getLocalizedText(const char* englishText, const char* germanText) {
        switch (currentLanguage) {
            case English:
                return englishText;
            case German:
                return germanText;
        }
        return nullptr; // Sollte nie erreicht werden  
    }
};

GameState gameState;

class GameStateMachine {
public:
    enum State {
        MainMenu,
        StartGame,
        SettingsMenu,
        KeyBindingsMenu,
        PauseMenu,
        ResumeGame
    };

    void gamePause()
    {
        gameState.isPaused = true;
    }

    void gameResume()
    {
        gameState.isPaused = false;
    }

    void changeState(State newState) {
        currentState = newState;
    }

    State getCurrentState() {
        return currentState;
    }

private:
    State currentState = MainMenu;
};

GameStateMachine stateMachine;

void updateVolumes()// Die Funktion updateVolumes ist verantwortlich für das Aktualisieren der Lautstärkeeinstellungen.  
{
    // Überprüft, ob die globale Lautstärke auf 0 gesetzt ist  
    if (gameState.globalVolume == 0)
    {
        // Wenn ja, setzt sie die Lautstärke für den Geh-Sound und die Hintergrundmusik auf 0  
        SetSoundVolume(gameState.walkingSound, 0);
        SetMusicVolume(gameState.backgroundMusic, 0);
    }
    else
    {
        // Wenn nicht, setzt sie die Lautstärke für den Geh-Sound und die Hintergrundmusik  
        // basierend auf den globalen Lautstärkeeinstellungen und den spezifischen Lautstärkeeinstellungen für Musik und Soundeffekte        SetSoundVolume(gameState.walkingSound, (gameState.globalVolume / 100.0f) * (gameState.globalSFXVolume / 100.0f));  
        SetMusicVolume(gameState.backgroundMusic, (gameState.globalVolume / 100.0f) * (gameState.globalMusicVolume / 100.0f));
    }
}

void loadResourcesAndInitAudio()
{
    gameState.myTexture = LoadTexture("assets/graphics/testimage.png");
    gameState.myMC = LoadTexture("assets/graphics/MC_test_2.png");
    InitAudioDevice();     // Initialize audio device  
    gameState.walkingSound = LoadSound("assets/audio/sfx/FootSteps.wav");
    gameState.backgroundMusic = LoadMusicStream("assets/audio/tracks/TestSong.wav");
    updateVolumes();
    PlayMusicStream(gameState.backgroundMusic); // Start music playing  
}

void unloadResourcesAndCloseAudio()
{
    UnloadTexture(gameState.myTexture);
    UnloadTexture(gameState.myMC);
    UnloadSound(gameState.walkingSound);
    UnloadMusicStream(gameState.backgroundMusic);
    CloseAudioDevice();    // Close audio device  
}

bool drawButtonAndCheckClick(Rectangle button, const char* englishText, const char* germanText) // Function to draw a button and check for clicks  
{
    DrawRectangleRec(button, GRAY);
    DrawText(gameState.getLocalizedText(englishText, germanText), button.x + button.width/2 - MeasureText(gameState.getLocalizedText(englishText, germanText), 20)/2, button.y + button.height/2 - 10, 20, BLACK);
    return CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void drawPromptText(const char* englishDirection, const char* germanDirection)
{
    int screenWidth = PixelGame::ScreenWidth;
    int screenHeight = PixelGame::ScreenHeight;

    DrawText(TextFormat(gameState.getLocalizedText("Press a key to swap the %c key for the %s function.", "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), gameState.keyBindings[gameState.selectedKey], gameState.getLocalizedText(englishDirection, germanDirection)),
             screenWidth / 2 - MeasureText(TextFormat(gameState.getLocalizedText("Press a key to swap the %c key for the %s function.", "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), gameState.keyBindings[gameState.selectedKey], gameState.getLocalizedText(englishDirection, germanDirection)), 20) / 2,
             screenHeight / 2 - 150, 20, BLACK);
}

void drawVolumeSlider(VolumeType type, int* volume, const char* englishVolumeName, const char* germanVolumeName, float sliderY) // Function to draw a volume slider  
{
    int screenWidth = PixelGame::ScreenWidth;
    Rectangle slider = {(float)screenWidth/2 - 50, sliderY, 150, 30};
    DrawRectangleLines(slider.x, slider.y, slider.width, slider.height, BLACK);
    DrawRectangle(slider.x, slider.y, *volume * (slider.width / 100), slider.height, GRAY);
    if (CheckCollisionPointRec(GetMousePosition(), slider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        *volume = (mouseX - slider.x) * 100 / slider.width;
        if (*volume < 0) *volume = 0;
        if (*volume > 100) *volume = 100;
    }
    DrawText(TextFormat("%s: %i", gameState.getLocalizedText(englishVolumeName, germanVolumeName), *volume), slider.x + slider.width/2 - MeasureText(TextFormat("%s: %i", gameState.getLocalizedText(englishVolumeName, germanVolumeName), *volume), 20)/2, slider.y - 40, 20, BLACK);
}

int drawMainMenu()// Die Funktion drawMainMenu ist verantwortlich für das Zeichnen des Hauptmenüs des Spiels.  
{
    // Bildschirmgröße abrufen  
    int screenWidth = PixelGame::ScreenWidth;
    int screenHeight = PixelGame::ScreenHeight;

    // Ziel-FPS (Frames pro Sekunde) auf 60 setzen  
    SetTargetFPS(gameState.targettedFps);

    // Definition der Position und Größe der Menübuttons  
    Rectangle button1 = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 150, 30};
    Rectangle button2 = {(float)screenWidth/2 - 50, (float)screenHeight/2, 150, 30};
    Rectangle button3 = {(float)screenWidth/2 - 50, (float)screenHeight/2 + 50, 150, 30};

    // Hauptspiel-Loop  
    while (!WindowShouldClose())
    {
        // Beginnt das Zeichnen auf dem Bildschirm  
        BeginDrawing();

        // Setzt den Hintergrund auf Weiß  
        ClearBackground(RAYWHITE);

        // Zeichnet den Titel des Spiels auf dem Bildschirm  
        DrawText(gameState.getLocalizedText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"),
                 screenWidth/2 - MeasureText(gameState.getLocalizedText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"),20)/2, 50, 20, BLACK);

        // Überprüft, ob der Benutzer auf die Menübuttons geklickt hat  
        if (CheckCollisionPointRec(GetMousePosition(), button1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return 1; // Spiel starten  
        }

        if (CheckCollisionPointRec(GetMousePosition(), button2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return 2; // Einstellungen  
        }

        if (CheckCollisionPointRec(GetMousePosition(), button3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return 3; // Spiel beenden  
        }

        // Zeichnet die Menübuttons auf dem Bildschirm  
        if (drawButtonAndCheckClick(button1, "Start PixelGame", "Spiel starten"))
        {
            return 1;
        }

        if (drawButtonAndCheckClick(button2, "Settings", "Einstellungen"))
        {
            return 2;
        }

        if (drawButtonAndCheckClick(button3, "Quit PixelGame", "Spiel beenden"))
        {
            return 3;
        }
        // Beendet das Zeichnen auf dem Bildschirm  
        EndDrawing();
    }

    // Schließt das Fenster und gibt 0 zurück, wenn das Fenster geschlossen werden soll  
    CloseWindow();
    return 0;
}

void drawKeyBindingsMenu()
{
    // Definition der Position und Größe der Tastenbelegungsbuttons  
    Rectangle upKeyButton = {(float)buttonScreenWidth, (float)PixelGame::ScreenHeight / 2 - 100, buttonWidth, buttonHeight};
    Rectangle downKeyButton = {(float)buttonScreenWidth, (float)PixelGame::ScreenHeight / 2 - 50, buttonWidth, buttonHeight};
    Rectangle leftKeyButton = {(float)buttonScreenWidth, (float)PixelGame::ScreenHeight / 2, buttonWidth, buttonHeight};
    Rectangle rightKeyButton = {(float)buttonScreenWidth, (float)PixelGame::ScreenHeight / 2 + 50, buttonWidth, buttonHeight};

    // Überprüfen, ob der Benutzer auf die Tastenbelegungsbuttons geklickt hat  
    if (drawButtonAndCheckClick(upKeyButton, TextFormat("Up: %c", gameState.keyBindings[UP]), TextFormat("Hoch: %c", gameState.keyBindings[UP])))
    {
        gameState.selectedKey = UP;
        gameState.isWaitingForKey = true;
    }
    else if (drawButtonAndCheckClick(downKeyButton, TextFormat("Down: %c", gameState.keyBindings[DOWN]), TextFormat("Runter: %c", gameState.keyBindings[DOWN])))
    {
        gameState.selectedKey = DOWN;
        gameState.isWaitingForKey = true;
    }
    else if (drawButtonAndCheckClick(leftKeyButton, TextFormat("Left: %c", gameState.keyBindings[LEFT]), TextFormat("Links: %c", gameState.keyBindings[LEFT])))
    {
        gameState.selectedKey = LEFT;
        gameState.isWaitingForKey = true;
    }
    else if (drawButtonAndCheckClick(rightKeyButton, TextFormat("Right: %c", gameState.keyBindings[RIGHT]), TextFormat("Rechts: %c", gameState.keyBindings[RIGHT])))
    {
        gameState.selectedKey = RIGHT;
        gameState.isWaitingForKey = true;
    }

    if (setKeyBindText == 0)
    {
        gameState.resetKeyBindingState();
        setKeyBindText++;
    }

    // Überprüfen, ob der Benutzer eine Taste auf der Tastatur gedrückt hat  
    if (gameState.isWaitingForKey && gameState.selectedKey != NONE)
    {
        for (int key = KEY_A; key <= KEY_Z; key++)
        {
            if (IsKeyPressed(key))
            {
                bool isKeyAlreadyBound = false;
                for (const auto& binding : gameState.keyBindings)
                {
                    if (binding.second == key)
                    {
                        isKeyAlreadyBound = true;
                        break;
                    }
                }
                if (!isKeyAlreadyBound)
                {
                    gameState.keyBindings[gameState.selectedKey] = key;
                    gameState.isWaitingForKey = false;
                    // Speichern Sie den geänderten Schlüssel und seine neue Belegung  
                    gameState.lastChangedKey = {gameState.selectedKey, key};
                }
                break;
            }
        }
        const char *englishDirection;
        const char *germanDirection;
        switch (gameState.selectedKey)
        {
            case UP:
                englishDirection = "Up";
                germanDirection = "Hoch";
                break;
            case DOWN:
                englishDirection = "Down";
                germanDirection = "Runter";
                break;
            case LEFT:
                englishDirection = "Left";
                germanDirection = "Links";
                break;
            case RIGHT:
                englishDirection = "Right";
                germanDirection = "Rechts";
                break;
        }
        if (gameState.isWaitingForKey)
        {
            if (countDrawText != 0)
            {
                gameState.lastChangedKey = {NONE, -1};
            }
            drawPromptText(englishDirection, germanDirection);
        }
    }
    // Zeigen Sie die Bestätigungsnachricht an, wenn eine Taste erfolgreich umgelegt wurde  
    if (gameState.lastChangedKey.first != NONE)
    {
        const char *englishDirection;
        const char *germanDirection;
        switch (gameState.lastChangedKey.first)
        {
            case UP:
                englishDirection = "move forward";
                germanDirection = "vorne gehen";
                break;
            case DOWN:
                englishDirection = "move backward";
                germanDirection = "zurück gehen";
                break;
            case LEFT:
                englishDirection = "move left";
                germanDirection = "links gehen";
                break;
            case RIGHT:
                englishDirection = "move right";
                germanDirection = "rechts gehen";
                break;
        }
        DrawText(TextFormat(gameState.getLocalizedText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"), gameState.getLocalizedText(englishDirection, germanDirection), gameState.lastChangedKey.second),
                 PixelGame::ScreenWidth / 2 - MeasureText(TextFormat(gameState.getLocalizedText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"), gameState.getLocalizedText(englishDirection, germanDirection), gameState.lastChangedKey.second), 20) / 2,
                 PixelGame::ScreenHeight / 2 - 150, 20, BLACK);
        countDrawText++;
    }

    // Wenn die Escape-Taste gedrückt wird, wird das Tastenbelegungsmenü geschlossen und das Steuerungsmenü geöffnet  
    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.isKeyBindingsOpen = false;
        gameState.activeMenu = Control;
        gameState.isWaitingForKey = false;
        gameState.selectedKey = NONE;
        setKeyBindText = 0;
        countDrawText = 0;
        gameState.lastChangedKey = {NONE, -1};
    }
}

void moveCharacter(float& mcX, float& mcY, int direction) {
    switch (direction) {
        case KEY_RIGHT:
        case KEY_D:
            mcX += gameState.moveSpeed;
            break;
        case KEY_LEFT:
        case KEY_A:
            mcX -= gameState.moveSpeed;
            break;
        case KEY_UP:
        case KEY_W:
            mcY -= gameState.moveSpeed;
            break;
        case KEY_DOWN:
        case KEY_S:
            mcY += gameState.moveSpeed;
            break;
    }
}

void drawControlMenu()
{
    Rectangle button1 = {(float)buttonScreenWidth - 25, (float)PixelGame::ScreenHeight / 2 - 50, buttonWidth + 50, buttonHeight};
    Rectangle button2 = {(float)buttonScreenWidth - 25, (float)PixelGame::ScreenHeight / 2, buttonWidth + 50, buttonHeight};

    if (CheckButtonClick(button1, "Keyboard/Mouse", "Tastatur/Maus"))
    {
        gameState.isKeyBindingsOpen = true;
    }
    if (drawButtonAndCheckClick(button2, "Controller", "Controller"))
    {
        // Handle button2 click - Controller Belegung ändern  
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.activeMenu = None;
    }
}

void drawLanguageMenu()
{
    int screenWidth = PixelGame::ScreenWidth;
    int screenHeight = PixelGame::ScreenHeight;

    Rectangle button1 = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 150, 30};
    Rectangle button2 = {(float)screenWidth/2 - 50, (float)screenHeight/2, 150, 30};

    if (drawButtonAndCheckClick(button1, "German", "Deutsch"))
    {
        gameState.currentLanguage = GameState::German;
    }
    if (drawButtonAndCheckClick(button2, "English", "Englisch"))
    {
        gameState.currentLanguage = GameState::English;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.activeMenu = None;
    }
}

bool drawSettingsMenu()
{
    int screenWidth = PixelGame::ScreenWidth;
    int screenHeight = PixelGame::ScreenHeight;

    Rectangle button1 = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 150, 30};
    Rectangle button2 = {(float)screenWidth/2 - 50, (float)screenHeight/2, 150, 30};
    Rectangle button3 = {(float)screenWidth/2 - 50, (float)screenHeight/2 + 50, 150, 30};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState.activeMenu)
        {
            case None:
                if (drawButtonAndCheckClick(button1, "Sound", "Ton"))
                {
                    gameState.activeMenu = VolumeSliders;
                }

                if (drawButtonAndCheckClick(button2, "Controls", "Steuerung"))
                {
                    gameState.activeMenu = Control;
                    if (gameState.jumpToSettings == 0)
                    {
                        gameState.activeMenu = None;
                        gameState.jumpToSettings++;
                    }
                }                if (drawButtonAndCheckClick(button3, "Language", "Sprache"))
        {
            gameState.activeMenu = Language;
        }

                DrawRectangleRec(button1, GRAY);
                DrawText(gameState.getLocalizedText("Sound", "Ton"), button1.x + button1.width/2 - MeasureText(gameState.getLocalizedText("Sound", "Ton"), 20)/2, button1.y + button1.height/2 - 10, 20, BLACK);
                DrawRectangleRec(button2, GRAY);
                DrawText(gameState.getLocalizedText("Controls", "Steuerung"), button2.x + button2.width/2 - MeasureText(gameState.getLocalizedText("Controls", "Steuerung"), 20)/2, button2.y + button2.height/2 - 10, 20, BLACK);
                DrawRectangleRec(button3, GRAY);
                DrawText(gameState.getLocalizedText("Language", "Sprache"), button3.x + button3.width/2 - MeasureText(gameState.getLocalizedText("Language", "Sprache"), 20)/2, button3.y + button3.height/2 - 10, 20, BLACK);
                break;
            case VolumeSliders:
                drawVolumeSlider(Global, &gameState.globalVolume, "Global Volume", "Globale Lautstärke", (float)screenHeight/2 - 100);
                drawVolumeSlider(BGMusic, &gameState.globalMusicVolume, "Music Volume", "Musiklautstärke", (float)screenHeight/2);
                drawVolumeSlider(SFX, &gameState.globalSFXVolume, "Sound Effect Volume", "Soundeffektlautstärke", (float)screenHeight/2 + 100);
                break;
            case Control:
                if (!gameState.isKeyBindingsOpen)
                {
                    drawControlMenu();
                }
                break;
            case Language:
                drawLanguageMenu();
                break;
        }
        if (gameState.isKeyBindingsOpen)
        {
            drawKeyBindingsMenu();
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState.activeMenu = None;
            gameState.jumpToSettings = 0;
            stateMachine.changeState(GameStateMachine::PauseMenu);
        }

        EndDrawing();

        if (gameState.activeMenu == None && IsKeyPressed(KEY_ESCAPE))
        {
            return true;
        }
    }    CloseWindow();

    return false;
}

void drawTiles(tson::Map &Map, Texture2D &myTexture) {
    auto layer = Map.getLayer("Kachelebene 2")->getData();
    float tileWidth = 16;
    int tileSetColumns = 16;

    for (int y = 0; y < Map.getSize().y; y++) {
        for (int x = 0; x < Map.getSize().x; x++) {
            int data = layer[y * Map.getSize().x + x];
            data--;
            if (data < 0) continue;

            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle dest = {(float) x * tileWidth * 2, (float) y * tileWidth * 2, tileWidth * 2, tileWidth * 2};

            DrawTexturePro(myTexture, source, dest, {0, 0}, 0, WHITE);
        }
    }}

void drawSprite(Texture2D &myTexture, float mcX, float mcY) {
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle dest = {mcX, mcY, myTexture.width * 0.15f, myTexture.height * 0.15f};

    DrawTexturePro(myTexture, source, dest, {0, 0}, 0.0f, WHITE);
}

void gameInit()
{
    loadResourcesAndInitAudio();

    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK)
    {
        std::cout << gameState.getLocalizedText("Failed to parse map, error: ", "Fehler beim Parsen der Karte, Fehler: ") << Map.getStatusMessage() << std::endl;
    }
}

void drawPauseMenu()
{
    std::cout << "drawPauseMenu() aufgerufen" << std::endl;

    int screenWidth = PixelGame::ScreenWidth;
    int screenHeight = PixelGame::ScreenHeight;

    // Definieren Sie die Position und Größe der Buttons  
    Rectangle resumeButton = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 150, 150, 30};
    Rectangle quitButton = {(float)screenWidth/2 - 50, (float)screenHeight/2 + 125, 150, 30};

    while (!WindowShouldClose() && gameState.isPaused)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Zeichnen Sie die Lautstärkeregler  
        drawVolumeSlider(Global, &gameState.globalVolume, "Global Volume", "Globale Lautstärke", (float)screenHeight/2 - 75);
        drawVolumeSlider(SFX, &gameState.globalSFXVolume, "Sound Effect Volume", "Soundeffektlautstärke", (float)screenHeight/2);
        drawVolumeSlider(BGMusic, &gameState.globalMusicVolume, "Music Volume", "Musiklautstärke", (float)screenHeight/2 + 75);

        // Zeichnen Sie die Schaltflächen  
        if (drawButtonAndCheckClick(resumeButton, "Resume PixelGame", "Spiel fortsetzen"))
        {
            gameState.isPaused = false;
        }
        else if (drawButtonAndCheckClick(quitButton, "Back to Menu", "Zurück zum Menü"))
        {
            stateMachine.changeState(GameStateMachine::MainMenu);
        }

        // Zeichnen Sie den Text nach dem Zeichnen des Hintergrunds  
        DrawText("Pause Menu", 10, 10, 20, BLACK); // Fügt diese Zeile hinzu  

        EndDrawing();
    }

    std::cout << "drawPauseMenu() beendet" << std::endl;
}

void gameLoop(tson::Map &Map)
{
    float mcX = 16.0f * 5; //X-Koordinate spawn  
    float mcY = 16.0f * 23; //Y-Koordinate spawn  

    while (!WindowShouldClose())
    {
        if (gameState.isPaused)
        {
            drawPauseMenu();
        }
        else
        {
            BeginDrawing();
            ClearBackground(WHITE);

            drawTiles(Map, gameState.myTexture);
            drawSprite(gameState.myMC, mcX, mcY);

            if (IsKeyPressed(KEY_ESCAPE))
            {
                unloadResourcesAndCloseAudio();
                stateMachine.changeState(GameStateMachine::PauseMenu);
                return;
            }

            if (IsKeyDown(gameState.keyBindings[UP]))
            {
                moveCharacter(mcX, mcY, KEY_UP);
            }
            if (IsKeyDown(gameState.keyBindings[DOWN]))
            {
                moveCharacter(mcX, mcY, KEY_DOWN);
            }
            if (IsKeyDown(gameState.keyBindings[LEFT]))
            {
                moveCharacter(mcX, mcY, KEY_LEFT);
            }
            if (IsKeyDown(gameState.keyBindings[RIGHT]))
            {
                moveCharacter(mcX, mcY, KEY_RIGHT);
            }
            UpdateMusicStream(gameState.backgroundMusic); //Aktualisiert Musik-Buffer  

            EndDrawing();
        }
    }    CloseWindow();
    unloadResourcesAndCloseAudio();
}

int main()
{
    InitWindow(PixelGame::ScreenWidth, PixelGame::ScreenHeight, PixelGame::PROJECT_NAME);
    SetTargetFPS(gameState.targettedFps);
#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    SetExitKey(KEY_F4);

    int menuResult; // Deklarieren Sie die Variable außerhalb des switch-case-Blocks  

    while (gameState.gameIsRunning == 1)
    {
        // Run game logic  
        switch (stateMachine.getCurrentState())
        {
            case GameStateMachine::MainMenu:
                menuResult = drawMainMenu(); // Verwenden Sie die Variable innerhalb des case-Blocks  
                if (menuResult == 1)
                {
                    stateMachine.changeState(GameStateMachine::StartGame);
                }
                else if (menuResult == 2)
                {
                    stateMachine.changeState(GameStateMachine::SettingsMenu);
                }
                else if (menuResult == 3)
                {
                    gameState.gameIsRunning = 0;
                }
                break;
            case GameStateMachine::StartGame:
                gameInit();
                gameLoop(Map);
                break;
            case GameStateMachine::SettingsMenu:
                if (drawSettingsMenu())
                {
                    stateMachine.changeState(GameStateMachine::MainMenu);
                }
                break;
            case GameStateMachine::KeyBindingsMenu:
                drawKeyBindingsMenu();
                break;
            case GameStateMachine::PauseMenu:
                stateMachine.gamePause();
                drawPauseMenu();
                break;
            case GameStateMachine::ResumeGame:
                stateMachine.gameResume();
                break;
        }
    }    CloseWindow();

    return EXIT_SUCCESS;
}

*/