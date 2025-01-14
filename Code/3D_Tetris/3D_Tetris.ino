//libraries used 
#include <FastLED.h>
#include <WiFi.h> //ESP32
#include <ESPForm.h>
#include <Preferences.h>

//Split into different files for better legibility 
#include "html.h"
String configFileName = "/wifi.json";

//The Wifi-credentials for logging in 
String apSSID = "3D-Tetris";
String apPSW = "12345678";
unsigned long serverTimeout = 2 * 60 * 1000;


const int X_DIM = 3;  // dimensin in X-direction
const int Y_DIM = 3;  // dimension in Y-direction
const int Z_DIM = 12;  // Adjustable dimension in Z-direction (testet for 10 and 12)

//LED Settings
#define LED_PIN 16
#define NUM_LEDS 108     // Number of LEDs
#define MAX_X 3          // Dimension X (3 layers)
#define MAX_Y 3          // Dimension Y (3 lines)
#define MAX_Z 12         // Dimension Z (12 columns)

//Idle Animation
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
#define BRIGHTNESS  80

// How many seconds to show each temperature before switching
#define DISPLAYTIME 20

// How many seconds to show black between switches
#define BLACKTIME   1

// FastLED-Array
CRGB leds[NUM_LEDS];

//Eeproom-adresses
Preferences preferences;

//Storage for the 3D-Matrix digital twin (with the variable dimensions)
int matrix[X_DIM][Y_DIM][Z_DIM]; 

//Color Options
byte color[25][3] = {{255,0,0},{255,64,0},{255,128,0},{255,191,0},{255,255,0},{191,255,0},{128,255,0},{64,255,0},{0,255,0},{0,255,64},{0,255,128},{0,255,191},{0,255,255},{0,191,255},
{0,128,255},{0,64,255},{0,0,255},{64,0,255},{128,0,255},{191,0,255},{255,0,255},{255,0,191},{255,0,128},{255,0,64},{255,0,0}};  //Array with the different color-values would be better to do this with a function
int row = 0;  //variable, that shows which color is selected 

//Struct for Tetrominos with extended points
struct Tetromino {
    int points[5][3];  // The 5 points in the format of {x, y, z}; non used values are set to -3
    int xPos;         // X-Position of the  Tetrominos
    int yPos;         // Y-Position of the Tetrominos
    int colorIndex;    // Color of the Tetrominos (Index in color-Array)
};

// Tetrominos with 5 points (non used points set to -3)
Tetromino tetrominos[] = {
    //Easy mode:
    // Point-Tetromino - 0
    {
        {{1, 1, 1}, {-3, -3, -3}, {-3, -3, -3}, {-3, -3, -3}, {-3, -3, -3}}, 
        0,0,0 // Color
    },
    // I-Tetromino - 1
    {
        {{0, 1, 1}, {1, 1, 1}, {2, 1, 1}, {-3, -3, -3}, {-3, -3, -3}},
        0,0,0  // Color
    },
    // Small-I-Tetromino - 2
    {
        {{0, 1, 1}, {1, 1, 1}, {-3, -3, -3}, {-3, -3, -3}, {-3, -3, -3}}, 
        0,0,0  // Color
    },
    //middle:
    // L-Tetromino - 3
    {
        {{1, 0, 1}, {1, 1, 1}, {1, 2, 1}, {2, 2, 1}, {-3, -3, -3}}, 
        0,0,0  // Color
    },
    // T-Tetromino - 4
    {
        {{1, 0, 1}, {0, 1, 1}, {1, 1, 1}, {2, 1, 1}, {-3, -3, -3}}, 
        0,0,0  // color
    },
    // S-Tetromino - 5
    {
        {{0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {2, 0, 1}, {-3, -3, -3}}, 
        0,0,0  // Color
    },
    // o-Tetromino - 6
    {
        {{0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {-3, -3, -3}}, 
        0,0,0  // Color
    },
    // Small-L-Tetromino - 7
    {
        {{0, 1, 1}, {1, 1, 1}, {1, 2, 1}, {-3, -3, -3},{-3, -3, -3}}, 
        0,0,0  // color
    },
    //Expert:
    // Star-Tetromino - 8
    {
        {{0, 1, 1}, {1, 0, 1}, {1, 1, 1},  {2, 1, 1}, {1, 2, 1}}, 
        0,0,0  // Color
    },
    // Big-S-Tetromino - 9
    {
        {{0, 0, 1}, {0, 1, 1}, {1, 1, 1},  {2, 1, 1}, {2, 2, 1}}, 
        0,0,0  // Color
    },
    // Big-T-Tetromino - 10
    {
        {{0, 1, 1}, {1, 1, 1}, {2, 0, 1}, {2, 1, 1}, {2, 2, 1}}, 
        0,0,0  // Color
    },
    // Handy-Tetromino - 11
    {
        {{0, 1, 1}, {1, 1, 1}, {1, 0, 1},{2, 1, 1}, {2, 0, 1}}, 
        0,0,0  // Color
    },
    // Big-U-Tetromino - 12
    {
        {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}, {2, 1, 1}, {2, 0, 1}}, 
        0,0,0  // Color
    },
    // Big-L-Tetromino - 13
    {
        {{0, 0, 1}, {0, 1, 1}, {0, 2, 1}, {1, 2, 1}, {2, 2, 1}}, 
        0,0,0  // Color
    },
    // L with dot -Tetromino - 14
    {
        {{1, 0, 1}, {1, 1, 1}, {1, 2, 1}, {2, 2, 1}, {0, 1, 1}}, 
        0,0,0  // Color
    },
    // stair-Tetromino - 15
    {
        {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}, {1, 2, 1}, {2, 2, 1}}, 
        0,0,0  // Color
    },

    //3D Terominos:
    // 3*1 with corner -Tetromino - 16
    {
        {{0, 1, 1}, {1, 1, 1}, {2, 1, 1}, {0, 0, 0}, {1, 0, 0}}, 
        0,0,0  // Farbe
    },
    // L with dot -Tetromino - 17
    {
        {{1, 0, 1}, {1, 1, 1}, {1, 2, 1}, {2, 2, 1}, {1, 1, 0}}, 
        0,0,0  // Farbe
    },
    // T with dot -Tetromino - 18
    {
        {{1, 0, 1}, {0, 1, 1}, {1, 1, 1}, {2, 1, 1}, {1, 1, 0}}, 
        0,0,0  // Farbe
    },
    // S with dot -Tetromino - 20
    {
        {{0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {2, 0, 1}, {1, 1, 0}}, 
        0,0,0  // Farbe
    },
    // o with dot -Tetromino - 21
    {
        {{0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 1, 0}}, 
        0,0,0  // Farbe
    },
    // Small-KoordinatenSystem-Tetromino - 22
    {
        {{0, 1, 1}, {1, 1, 1}, {1, 2, 1},{1, 1, 0}, {-3, -3, -3}}, 
        0,0,0  // Farbe
    }
};

//Tetris realted Variables:
Tetromino currentTetromino;   // The active Tetromino
int nextTetrominoIndex = 0;   // The next Tetromino block as index of the Arrays
int currentZ = 0;             // Latest Z-Position of the falling Tetrominos
bool gameRunning = false;     // Variable to check if the game is running right now 
int gameDelay = 1000;         // variable to track the time of the now running action. Examples: block is falling or collision of blocks
int score = 0;                // variable to store the score of the running game
int levelScore = 0;           // variable that shows the level in which the user is. the level inceases every 10th layer they cleared
String playerData = "";       // string which buffers the highscore data
int difficulty = 0;           // variable to set the difficulty of the game
bool changeScore = false;     // toggle to signal that the new score has to be saved
int ElementCounter = 0;
ESPFormClass::HTMLElementItem ElementTrigger;   // set a Element for the Element press/or value change interrupts
ESPFormClass::HTMLElementItem PreviousElementTrigger; 

//regular Arduino functions
void setup();
void loop();

//3D-Tetris related functions
void idleAnimtation();                                                                 // function that shows an animation while no game is running
void gameOver();                                                                       // function to reset all values after gameOver
void saveData(String highscoreString);                                                 // function that saves the Highscore values on the Eproom of the Esp
void splitHighscores(String input, String names[], int scores[], int maxEntries);      // function to split the input string into different HighScore values
void clearMatrix();                                                                    // funciton to clear the matrix
int XYZ_to_index(int x, int y, int z);                                                 // function to calculate the LED-Index based on 3D-coordinates
void updateLEDs();                                                                     // function to refresh the LEDs based on the matrix
void renderTetromino(Tetromino &tetromino, int z, bool clear);                         // function to draw the position of the tetromino in the matrix temporary
void placeTetromino(Tetromino &tetromino, int z);                                      // function to put the tetromino in the matrix
bool moveTetrominoDown(Tetromino &tetromino);                                          // funciton to move the tetromino down
bool canPlaceTetromino(Tetromino &tetromino, int z);                                   // function to check the placement of the tetromino (collison check)
void updateAndDisplayMatrix();                                                         // function to display the game matrix in the serial monitor 
void spawnNewTetromino();                                                              // function to chose a random new Tetromino
int spawnRelativeToDiff();                                                             // function that returns a random new Tetromino relative to the selected difficulti
void clearFullLevelAndShiftDown(int level);                                            // function that removes the layer and shifts every upper layer on layer lower
void checkFullLevel();                                                                 // function that checkes every layer if it is filled with blocks

//3D-Tetris movment and rotation related functions
void moveTetromino(Tetromino &tetromino, int dx, int dy, int dz);   // General movement function that moves Tetromenio in x, y or z direction depending on the input 
void fallDown(Tetromino &tetromino);                                // function that lets the Tetromino fall down until it finds a collision with a block or the ground
void rotateTetromino(Tetromino &tetromino, char axis);              // General rotation function, which is responsible for rotation in every individual funciton
bool AdjustPosition(Tetromino &tetromino, int &currentZ);           // function to find a postion if the Tetromino rotates out of the gameMatrix

//wifi and webserver realted functions
bool startWiFi();                                                         //starts the Wifi protocol
void setupESPForm();                                                      //Initialised all the EventListener for the comminication between Esp and HTML
void formElementEventCallback(ESPFormClass::HTMLElementItem element);     //function that gets called if any of the EventListener get triggered. Used to get the different button presses and value changes
void checkForGameControllElements(ESPFormClass::HTMLElementItem element); //function that calls all calls the differnt functions for every button
void serverTimeoutCallback();                                             //If server timeout (no client connected within specific time)


void setup() {
  Serial.begin(115200);

  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  WiFi.persistent(false);

  if (!startWiFi()) {
    setupESPForm();
    Serial.println("MAIN:  Start server");
    ESPForm.startServer();
  }
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  preferences.begin("myScore", false);
  playerData = preferences.getString("score");
  Serial.println(playerData);
  clearMatrix();        // initiate the matrix
  updateLEDs();
}

void loop() {
  if(ESPForm.getClientCount() > 0) {
    ESPFormClass::HTMLElementItem element = ESPForm.getElementEventConfigItem("gameScores");
    String pufferplayer = element.value; 
    if(pufferplayer == "" || pufferplayer == "null" && playerData != ""){
      ESPForm.setElementContent("gameScores", playerData);
    }
  }
  // Show the matrix in the serial monitor (for debugging)
  //updateAndDisplayMatrix();
  if(gameRunning){
    static unsigned long lastUpdateTime = 0; 
    unsigned long currentTime = millis();
  
    // Check if gameDelay time have passed
    if (currentTime - lastUpdateTime >= gameDelay) {
      lastUpdateTime = currentTime;
      // Try to move the Tetromino down
      if (!moveTetrominoDown(currentTetromino)) {
        // Movement failed -> Spawn new Tetromino
        spawnNewTetromino();
      }
    }
  }
  else {
    idleAnimtation();
  }

  if(PreviousElementTrigger.id != ElementTrigger.id || ElementCounter > 1) {
    checkForGameControllElements(ElementTrigger);
    PreviousElementTrigger = ElementTrigger;
    ElementCounter--;
  }
}

// function that shows an animation while no game is running
void idleAnimtation(){
  // draw a generic, no-name rainbow
  static uint8_t starthue = 0;
  fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);

  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
    leds[0] = TEMPERATURE_1; // show indicator pixel
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
    leds[0] = TEMPERATURE_2; // show indicator pixel
  }

  // Black out the LEDs for a few seconds between color changes
  // to let the eyes and brains adjust
  if( (secs % DISPLAYTIME) < BLACKTIME) {
    memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
  }
  FastLED.show();
  FastLED.delay(8);
}

// function to reset all values after gameOver
void gameOver(){
  gameRunning = false;
  Serial.println("Game Over!");
  ESPForm.setElementContent("gameOverInput", "GameOver");
  clearMatrix();
  updateLEDs();
}

// function that saves the Highscore values on the Eproom of the Esp
void saveData(String highscoreString){
  Serial.println("SaveData");
  Serial.println(highscoreString);
  int maxEntries = 10; // Max amout of stored entries
  int count = 0;
  String names[maxEntries];
  int scores[maxEntries];
  
  //Call the function
  splitHighscores(highscoreString, names, scores, maxEntries);
  String scoreData = "";
  for (int i = 0; i < maxEntries; i++) {
    if (names[i] != "") { // check if the name is valid
      Serial.print("Name: ");
      Serial.print(names[i]);
      Serial.print(", Score: ");
      Serial.println(scores[i]);
      scoreData+= names[i]+","+scores[i]+";";
    }
  }
  preferences.putString("score",scoreData);
  playerData = scoreData;
}

// function to split the input string into different HighScore values
void splitHighscores(String input, String names[], int scores[], int maxEntries) {
  int entryIndex = 0;
  while (input.length() > 0 && entryIndex < maxEntries) {
    int delimiterPos = input.indexOf(';');
    String entry;
    if (delimiterPos != -1) {
      entry = input.substring(0, delimiterPos);
      input = input.substring(delimiterPos + 1);
    } else {
      entry = input;
      input = "";
    }

    int commaPos = entry.indexOf(',');
    if (commaPos != -1) {
      names[entryIndex] = entry.substring(0, commaPos);
      scores[entryIndex] = entry.substring(commaPos + 1).toInt();
      entryIndex++;
    }
  }
}

// funciton to clear the matrix
void clearMatrix() {
  Serial.println("Clear-Matrix");
  for (int z = 0; z < Z_DIM; z++) {
    for (int y = 0; y < Y_DIM; y++) {
      for (int x = 0; x < X_DIM; x++) {
        matrix[x][y][z] = 0; // Initiate matrix with zero
      }
    }
  }
}

// function to calculate the LED-Index based on 3D-coordinates
int XYZ_to_index(int x, int y, int z) {
  int reverseZ = MAX_Z - 1 - z; // invert z-direction(from top to bottom)
  return (reverseZ * MAX_X * MAX_Y) + (y * MAX_X) + x;
}

// function to refresh the LEDs based on the matrix
void updateLEDs() {
  for (int x = 0; x < MAX_X; x++) {
    for (int y = 0; y < MAX_Y; y++) {
      for (int z = 0; z < MAX_Z; z++) {
        int index = XYZ_to_index(x, y, z);
        if (index < NUM_LEDS) { // check: Index in range
          if (matrix[x][y][z] > 0 && matrix[x][y][z] <= 25) {
            leds[index].setRGB(color[matrix[x][y][z]][0],color[matrix[x][y][z]][1],color[matrix[x][y][z]][2]); // Stone active: colored
          } else {
            leds[index] = CRGB::Black; // stone deactivated: LED off
          }
        }
      }
    }
  }
  FastLED.show();
}

// function to draw the position of the tetromino in the matrix temporary
void renderTetromino(Tetromino &tetromino, int z, bool clear = false) {
    for (int i = 0; i < 5; i++) {
        //Check if the point is vaild (ignore -3)
        if (tetromino.points[i][0] != -3) {
            int nx = tetromino.xPos + tetromino.points[i][0];
            int ny = tetromino.yPos + tetromino.points[i][1];
            int nz = z + tetromino.points[i][2];

            //Check if the point is in the boundaries of the matrix 
            if (nx >= 0 && nx < X_DIM && ny >= 0 && ny < Y_DIM && nz >= 0 && nz < Z_DIM) {
                matrix[nx][ny][nz] = clear ? 0 : tetromino.colorIndex;
            }
        }
    }
}

// function to put the tetromino in the matrix
void placeTetromino(Tetromino &tetromino, int z) {
    for (int i = 0; i < 5; i++) {
        //Check if the point is vaild (ignore -3)
        if (tetromino.points[i][0] != -3) {
            int nx = tetromino.xPos + tetromino.points[i][0];
            int ny = tetromino.yPos + tetromino.points[i][1];
            int nz = z + tetromino.points[i][2];

            //Set the point in the matrix if it is valid
            if (nx >= 0 && nx < X_DIM && ny >= 0 && ny < Y_DIM && nz >= 0 && nz < Z_DIM) { 
                matrix[nx][ny][nz] = tetromino.colorIndex;
            }
        }
    }
    // check and delete the complet layer 
    checkFullLevel();
}

//funciton to move the tetromino down
bool moveTetrominoDown(Tetromino &tetromino) {
    // Delete the old position in the current layer (currentZ)
    renderTetromino(tetromino, currentZ-1, true);
    renderTetromino(tetromino, currentZ, true);

    //Check if the tetrominocan be placed in the next layer
    if (canPlaceTetromino(tetromino, currentZ + 1)) {
        //Go down one layer
        currentZ++;
        // Draw the tetromino in the new z-layer
        renderTetromino(tetromino, currentZ);
        updateLEDs();
        return true;
    } else {
        // Place it if no more movment is possible
        Serial.println("Collision detected - Placement of block.");
        placeTetromino(tetromino, currentZ);
        return false;
    }
}

//Function to check the placement of the tetromino (collison check)
bool canPlaceTetromino(Tetromino &tetromino, int z) {
    for (int i = 0; i < 5; i++) {
        // Check if the point is valid (ignore -3)
        if (tetromino.points[i][0] != -3) {
            int nx = tetromino.xPos + tetromino.points[i][0];
            int ny = tetromino.yPos + tetromino.points[i][1];
            int nz = z + tetromino.points[i][2];

            // Debugging-output
            Serial.print("Check block of: (");
            Serial.print(nx);
            Serial.print(", ");
            Serial.print(ny);
            Serial.print(", ");
            Serial.print(nz);
            Serial.println(")");

            //Check if the position is outside of the matrix or collides
            if (nx < 0 || nx >= X_DIM || ny < 0 || ny >= Y_DIM || nz < 0 || nz >= Z_DIM || matrix[nx][ny][nz] != 0) {
                Serial.println("Block outside the matrix boundaries!");
                return false; // Collison detected
            }
        }
    }
    return true; // No collison, placment is empty
}

// Method to display matrix
void updateAndDisplayMatrix() {
  Serial.println("Current state of the 3D-Matrix:");
  for (int z = 0; z < Z_DIM; z++) {
    Serial.print("Layer ");
    Serial.print(z);
    Serial.println(":");
    for (int y = 0; y < Y_DIM; y++) {
      for (int x = 0; x < X_DIM; x++) {
        Serial.print(matrix[x][y][z]);
        Serial.print("\t");
      }
      Serial.println(); // New line for the next row
    }
    Serial.println(); // Blank space between the layers
  }
}

// function to chose a random new Tetromino
void spawnNewTetromino() {
  currentZ = -1; // Start in the top most layer
  Serial.print("Difficulty:");
  Serial.println(difficulty);
  currentTetromino = tetrominos[nextTetrominoIndex];
  nextTetrominoIndex = spawnRelativeToDiff();
  if(nextTetrominoIndex > 15) {
    ESPForm.setElementContent("hidden-piece-input", "16");
  }
  else{
    ESPForm.setElementContent("hidden-piece-input", String(nextTetrominoIndex));
  }

  currentTetromino.xPos = 0;                  // middle in X
  currentTetromino.yPos = 0;                  // middle in Y
  currentTetromino.colorIndex = random(1, 26);

   if (!canPlaceTetromino(currentTetromino, currentZ)) {
    renderTetromino(currentTetromino, 0);
    updateLEDs();
    gameOver();
    return;
  }
  renderTetromino(currentTetromino, currentZ);
  updateLEDs();
}

// function that returns a random new Tetromino relative to the selected difficulti
int spawnRelativeToDiff(){
  int i = 0;
  switch(difficulty){ 
    case 0:
      i = random(0, 3); // Random Tetromino difficulti easy
      break;
    case 1:
      i = random(0, 8); // Random Tetromino difficulti middel
      break;
    case 2:
      i = random(3, 13); // Random Tetromino difficulti hard
      break;
    case 3:
      i = random(3, 16); // Random Tetromino difficulti experte
      break;
    case 4:
      i = random(8, 22); // Random Tetromino difficulti impossible
      currentZ=1;
      break;
    }
    return i;
}

// function that removes the layer and shifts every upper layer on layer lower
void clearFullLevelAndShiftDown(int level) {

  // Delete the layer (set all blocks to zero)
  for (int y = 0; y < Y_DIM; y++) {
    for (int x = 0; x < X_DIM; x++) {
      matrix[x][y][level] = 0;
    }
  }

  // Shift all blocks above the deleted layer down
  for (int z = level; z > 0; z--) {
    for (int y = 0; y < Y_DIM; y++) {
      for (int x = 0; x < X_DIM; x++) {
        matrix[x][y][z] = matrix[x][y][z - 1];
      }
    }
  }

  //Set the top most layer to 0
  for (int y = 0; y < Y_DIM; y++) {
    for (int x = 0; x < X_DIM; x++) {
      matrix[x][y][0] = 0;
    }
  }
  //LED-refresh after changment in the matrix
  updateLEDs();
}

// function that checkes every layer if it is filled with blocks
void checkFullLevel() {
  for (int z = 0; z < Z_DIM; z++) {
    bool full = true;

    //Check if all blocks in the layer are occupied
    for (int x = 0; x < X_DIM; x++) {
      for (int y = 0; y < Y_DIM; y++) {
        if (matrix[x][y][z] == 0) {
          full = false;
          break;
        }
        if (z == currentZ){
          full = false;
          break;
        }
      }
      if (!full) break;
    }

    //If the layer is completly occupied proceed with deleting it
    if (full) {
      switch(difficulty){ 
      case 0:
        score += 40;
        gameDelay -= 10;
        if(score/40%10 == 0) {
          levelScore++;
        }
        break;
      case 1:
        score += 80;
        gameDelay -= 30;
        if(score/80%10 == 0) {
          levelScore++;
        }
        break;
      case 2:
        score += 120;
        gameDelay -= 40;
        if(score/120%10 == 0) {
          levelScore++;
        }
        break;
      case 3:
        score += 400;
        gameDelay -= 60;
        if(score/400%10 == 0) {
          levelScore++;
        }
        break;
      case 4:
        score += 800;
        gameDelay -= 80;
        if(score/800%10 == 0) {
          levelScore++;
        }
        break;
      }
      if(gameDelay < 400) {
        gameDelay = 400;
      }
      Serial.print("Gamedelay:");
      Serial.println(gameDelay);
      ESPForm.setElementContent("levelText", String(levelScore));
      ESPForm.setElementContent("scoreText", String(score));
      clearFullLevelAndShiftDown(z);
    }
  }
}

// General movement function that moves Tetromenio in x, y or z direction depending on the input 
void moveTetromino(Tetromino &tetromino, int dx, int dy, int dz) {
  renderTetromino(tetromino, currentZ, true); // Delete tetromino

  tetromino.xPos += dx;
  tetromino.yPos += dy;
  currentZ += dz;

  if (!canPlaceTetromino(tetromino, currentZ)) {
    // Undo the movement
    tetromino.xPos -= dx;
    tetromino.yPos -= dy;
    currentZ -= dz;
    Serial.println("Invalid move. Reverting.");
  }

  renderTetromino(tetromino, currentZ); // Rerender tetromonio
  updateLEDs();
}

// function that lets the Tetromino fall down until it finds a collision with a block or the ground
void fallDown(Tetromino &tetromino) {
  // Remove the Tetromino of its current position
  renderTetromino(tetromino, currentZ, true); // delete Tetromino

  // Calculate the lowest possible z-position
  int zWert = currentZ;
  while (canPlaceTetromino(tetromino, zWert + 1)) { // Check the next position
    zWert++;
  }

  //Set the tetromino on the lowest possible position
  currentZ = zWert-2;
  renderTetromino(tetromino, currentZ); //Render Tetromino in the new position

  // Update LEDs
  updateLEDs();
}

//General rotation function, which is responsible for rotation in every individual funciton
void rotateTetromino(Tetromino &tetromino, char axis){
  Tetromino tPuffer = tetromino;
  renderTetromino(tetromino, currentZ, true);

  //Subtract 1 of every coordinate to set the origin in the middle of the matrix
  for(int i = 0;i<5;i++){
    if (tetromino.points[i][0] != -3) {
      for(int k = 0;k<3;k++){
        tetromino.points[i][k] = tetromino.points[i][k]-1;
      }
    }
  }
  //Rotate around x,y,z for 90°
  for(int i = 0; i<5;i++){
    if (tetromino.points[i][0] != -3) {
      int temp[2];
            switch (axis) {
                case 'X': // Rotation around X-axis
                    temp[0] = -tetromino.points[i][2];
                    temp[1] = tetromino.points[i][1];
                    tetromino.points[i][1] = temp[0];
                    tetromino.points[i][2] = temp[1];
                    break;
                case 'Y': // Rotation around Y-axis
                    temp[0] = tetromino.points[i][2];
                    temp[1] = -tetromino.points[i][0];
                    tetromino.points[i][0] = temp[0];
                    tetromino.points[i][2] = temp[1];
                    break;
                case 'Z': // Rotation around Z-axis
                    temp[0] = -tetromino.points[i][1];
                    temp[1] = tetromino.points[i][0];
                    tetromino.points[i][0] = temp[0];
                    tetromino.points[i][1] = temp[1];
                    break;
            }
    }
  }
  //The reverse transformation to the original coordinate system
  for(int i = 0;i<5;i++){
    if (tetromino.points[i][0] != -3) {
      for(int k = 0;k<3;k++){
        tetromino.points[i][k] = tetromino.points[i][k]+1;
      }
    }
  }
  if (!canPlaceTetromino(tetromino, currentZ)){
    if (!AdjustPosition(tetromino,currentZ)) {
        // Tetromino can't be adjusted nicht angepasst werden
        Serial.println("No final position found.");
        tetromino = tPuffer; // Reset to original position
    }
  }
  renderTetromino(tetromino, currentZ);
  updateLEDs();
}

// function to find a postion if the Tetromino rotates out of the gameMatrix
bool AdjustPosition(Tetromino &tetromino, int &currentZ) {
    const int maxAttempts = 5;
    int adjustments[6][3] = {
        { 1,  0,  0}, // right
        {-1,  0,  0}, // left
        { 0,  1,  0}, // top
        { 0, -1,  0}, // down
        { 0,  0,  1}, // front
        { 0,  0, -1}  // back
    };

    // Save orgiginal position
    int originalX = tetromino.xPos;
    int originalY = tetromino.yPos;
    int originalZ = currentZ;

    // Try every combination before adjusting
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        for (int dir = 0; dir < 6; ++dir) {
            // Shift position temporarily
            tetromino.xPos += adjustments[dir][0];
            tetromino.yPos += adjustments[dir][1];
            currentZ += adjustments[dir][2];

            // Check if the tetromino can be placed
            if (canPlaceTetromino(tetromino, currentZ)) {
                Serial.println("PasstAdjust");
                return true; // Valid position found
            }

            // Take the shift back
            tetromino.xPos -= adjustments[dir][0];
            tetromino.yPos -= adjustments[dir][1];
            currentZ -= adjustments[dir][2];
        }
    }

    // Restore original position if no other position can be found
    tetromino.xPos = originalX;
    tetromino.yPos = originalY;
    currentZ = originalZ;

    return false; // No valid position could be found
}

//starts the Wifi protocol
bool startWiFi(){
  //WiFi data is ready then start connction
  WiFi.mode(WIFI_AP);
  Serial.print("MAIN:  Connecting to Wi-Fi..");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("MAIN:  Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  }
  else {
    Serial.println();
    Serial.println("MAIN:  WiFi connection failed!");
    return false;
  }
  return true;
}

//Initialised all the EventListener for the comminication between Esp and HTML
void setupESPForm(){
  Serial.println("MAIN:  Setup ESPForm");
  ESPForm.setAP(apSSID.c_str(), apPSW.c_str());
  //Prepare html contents (in html.h) for the web page rendering (only once)
  //Flash's uint8_t array, file name, size of array, gzip compression
  ESPForm.addFileData(index_html, "index.html");

  //Add html element event listener, id "text1" for onchange event
  ESPForm.addElementEventListener("moveUp", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("moveDown", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("moveLeft", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("moveRight", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("rotateX", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("rotateY", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("rotateZ", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("startButton", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("pauseButton", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("fallButton", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("submitName", ESPFormClass::EVENT_ON_CLICK);
  ESPForm.addElementEventListener("gameScores", ESPFormClass::EVENT_ON_CHANGE);
  ESPForm.addElementEventListener("difficultyTextbox", ESPFormClass::EVENT_ON_CHANGE);
  
  //Start ESPForm's Webserver
  ESPForm.begin(formElementEventCallback, serverTimeoutCallback, serverTimeout, true);

  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("=================================================");
  Serial.println("Use web browser and navigate to " + WiFi.localIP().toString());
  Serial.println("=================================================");
  Serial.println();
}

//function that gets called if any of the EventListener get triggered. Used to get the different button presses and value changes
void formElementEventCallback(ESPFormClass::HTMLElementItem element){
  Serial.println();
  Serial.println("***********************************");
  Serial.println("id: " + element.id);
  Serial.println("value: " + element.value);
  Serial.println("type: " + element.type);
  Serial.println("event: " + ESPForm.getElementEventString(element.event));
  Serial.println("***********************************");
  Serial.println();

  ElementTrigger = element;
  ElementCounter++;

  if(element.id == "gameScores") {
    if(changeScore){
      saveData(element.value);
      changeScore = false;
    }
    ElementCounter--;
  }
}

void checkForGameControllElements(ESPFormClass::HTMLElementItem element){
  //Check for any game running related button presses according to the id
  if(element.id == "startButton"){
    if(!gameRunning) {
      gameRunning = true;
      score = 0;
      levelScore = 0;
      ESPForm.setElementContent("levelText", String(score));
      ESPForm.setElementContent("scoreText", String(score));
      ESPFormClass::HTMLElementItem value = ESPForm.getElementEventConfigItem("difficultyTextbox");
      String diffi = value.value;
      Serial.println("GameMode:");
      Serial.println(diffi);
      //Set the difficulti relative to the value in the combobox
      if(diffi == "easy"){
            difficulty = 0;
            gameDelay = 3000;
      } else if(diffi == "medium"){
            difficulty = 1;
            gameDelay = 2500;
      } else if(diffi == "hard"){
            difficulty = 2;
            gameDelay = 2000;
      } else if(diffi == "expert"){
            difficulty = 3;
            gameDelay = 1500;
      } else if(diffi == "impossible"){
            difficulty = 4;
            gameDelay = 1000;
      }
      //Spawn the next Tetromino before the first one was even created to show it in the GUI
      nextTetrominoIndex = spawnRelativeToDiff();
      //Check for the index of the Tetromino because the ones above 15 can't be displayes anymore on a 2D surface
      if(nextTetrominoIndex > 15) {
        ESPForm.setElementContent("hidden-piece-input", "16");
      }
      else{
        ESPForm.setElementContent("hidden-piece-input", String(nextTetrominoIndex));
      }
      clearMatrix();        // init gamefield
      spawnNewTetromino();  // spawn new Tetromino
      delay(1000);
    } else {
      gameRunning = false;
      clearMatrix();
      updateLEDs();
    }
  }
  else if(element.id == "pauseButton") {
    gameRunning = !gameRunning;
  }
  if(element.id == "submitName") {
    changeScore = true;
  } 

  //Check for any movment related button presses according to the id
  if(gameRunning) {
    if(element.id == "moveUp") {
      moveTetromino(currentTetromino, 0, -1, 0);
    }
    else if(element.id == "moveDown"){
      moveTetromino(currentTetromino, 0, 1, 0);
    }
    else if(element.id == "moveLeft"){
      moveTetromino(currentTetromino, 1, 0, 0);
    }
    else if(element.id == "moveRight") {
      moveTetromino(currentTetromino, -1, 0, 0);
    }
    else if(element.id == "fallButton") {
      fallDown(currentTetromino);
    }
    else if(element.id == "rotateZ") {
      rotateTetromino(currentTetromino, 'Z');
    }
    else if(element.id == "rotateX") {
      rotateTetromino(currentTetromino, 'X');
    }
    else if(element.id == "rotateY") {
      rotateTetromino(currentTetromino, 'Y');
    }
  }
}

//If server timeout (no client connected within specific time)
void serverTimeoutCallback(){
  Serial.println("***********************************");
  Serial.println("Server Timeout");
  Serial.println("***********************************");
  Serial.println();
}
