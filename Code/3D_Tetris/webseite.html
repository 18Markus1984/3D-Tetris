#include <Arduino.h>

// Raw content of index.html in plain text
static const char *index_html = R"--espform--(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>3D Tetris</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: flex-start;
            min-height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
            overflow: auto;
        }

        .content-container {
            background-color: white;
            padding: 20px;
            border-radius: 15px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.2);
            width: 90%;
            max-width: 600px;
            text-align: center;
        }

        h1 {
            color: white;
            font-family: 'Arial', sans-serif;
            font-size: 60px;
            margin-bottom: 20px;
        }

        .start-btn {
            padding: 15px 30px;
            font-size: 18px;
            cursor: pointer;
            background-color: #007BFF;
            color: white;
            border: none;
            border-radius: 10px;
            margin-top: 20px;
      margin-right:10px;
      margin-left:10px;
            transition: background-color 0.3s ease, transform 0.1s ease;
        }

        .start-btn:hover {
            background-color: #0056b3;
            transform: scale(1.1);
        }

        .start-btn:active {
            transform: scale(0.95);
        }
    
    #pauseButton {
      //display:flex;
      display:none;
    }

        .control-container {
            display: flex;
            justify-content: space-between; /* Richtungssteuerung und Fall-Button nebeneinander */
            align-items: center;
            margin-top: 20px;
            width: 100%;
        }
    .control-containerRotations{
      display:inline-block;

    }
    
    .rotation-btns{
      display:flex;
      flex-direction: row;
    }
    
        .section-title {
            font-size: 20px;
            font-weight: bold;
            margin-top: 20px;
            margin-bottom: 10px;
        }

        .direction-btns {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .fall-button-container {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .row {
            display: flex;
            justify-content: center;
            margin: 5px;
        }

        .control-btn {
            width: 70px;
            height: 70px;
            margin: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 28px;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: background-color 0.3s ease, transform 0.1s ease;
        }
    #hiddenButton {
      color:white;
      background-color: white;
    }
        .control-btn:hover {
            background-color: #45a049;
            transform: scale(1.1);
        }

        .control-btn:active {
            transform: scale(0.95);
        }

        #moveUp::before {
            content: '↑';
        }

        #moveDown::before {
            content: '↓';
        }

        #moveLeft::before {
            content: '←';
        }

        #moveRight::before {
            content: '→';
        }

        #fallButton {
            background-color: #FF5733;
            color: white;
            font-size: 28px;
        }

        #fallButton:hover {
            background-color: #C70039;
            transform: scale(1.1);
        }

        #fallButton:active {
            transform: scale(0.95);
        }

        canvas {
            border: 1px solid #000;
      border-radius: 5px;
        }

        .highscores-container {
            margin-top: 40px;
            background-color: white;
            padding: 20px;
            border-radius: 15px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.2);
            width: 90%;
            max-width: 600px;
            text-align: center;
        }

        table {
            width: 100%;
            border-collapse: collapse;
        }

        table th, table td {
            padding: 10px;
            text-align: left;
            border: 1px solid #ddd;
        }

        table th {
            background-color: #f2f2f2;
        }

        #gameOverPopup {
            display: none;
            background-color: rgba(0, 0, 0, 0.7);
            color: white;
            padding: 30px;
            border-radius: 15px;
            text-align: center;
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            width: 80%;
            max-width: 400px;
        }

        #gameOverPopup input {
            padding: 10px;
            width: 100%;
            margin: 10px 0;
        }

        #gameOverPopup button {
            padding: 10px 20px;
            background-color: #FF5733;
            color: white;
            border: none;
            border-radius: 10px;
            cursor: pointer;
        }

        #gameOverPopup button:hover {
            background-color: #C70039;
        }
    
    /* Dropdown für Schwierigkeit */
        .difficulty-container {
            margin-top: 20px;
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        #difficultySelect {
            padding: 10px;
            font-size: 16px;
            margin-top: 10px;
            border-radius: 5px;
            border: 1px solid #ddd;
            width: 200px;
            background-color: white;
        }
        /* Sprachauswahl im Header */
        .header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 15px;
            background-color: #004b99;
            color: white;
        }

        .header select {
            padding: 8px;
            border-radius: 5px;
            border: none;
            background-color: white;
            color: #004b99;
            font-size: 14px;
        }
        #styleScoreText{
            font-family: 'Arial', sans-serif;
            font-size: 40px;
            margin-right:30px;
        }
        #next-piece-container{
            margin-left:30px;
        }
    
    </style>
</head>
<body>
    <div class="header">    
  <h1>Tetris-3D</h1>
        <div class="language-selector">
            <label for="language-select" style="display: none;">Sprache auswählen:</label>
            <select id="language-select" onchange="updateLanguage()">
                <option value="de">Deutsch</option>
                <option value="en">English</option>
                <option value="fr">Français</option>
        <option value="es">Spanisch </option>
        <option value="it">Italienisch </option>
            </select>
        </div>
  </div>

    <div class="content-container">
        <input type="hidden" id="gameOverInput" value="">
        <input type="hidden" id="gameScores" value="">
		    <input type="hidden" id="difficultyTextbox" value="easy">
        <button id="startButton" class="start-btn">Start</button>
    <button id="pauseButton" class="start-btn">Pause</button>
    <!-- Dropdown für Schwierigkeit -->
        <div class="difficulty-container">
            <div class="section-title">Schwierigkeitsstufe</div>
            <select id="difficultySelect">
                <option value="easy">Leicht</option>
                <option value="medium">Mittel</option>
                <option value="hard">Schwer</option>
                <option value="expert">Experte</option>
                <option value="impossible">Unmöglich</option>
            </select>
        </div>
    <div class="control-container">
    <div id="next-piece-container">
        <h3>Nächster Stein:</h3>
        <canvas id="next-piece-canvas" width="120" height="120"></canvas>
        <input type="hidden" id="hidden-piece-input" value="17" >
      </div>
	  <div id="styleScoreText">
		  <p><b><k id="LevelStatusText">Level</k>: <k id="levelText">0</k></b></p>
		  <p><b><k id="punkteText">Punkte</k>: <k id="scoreText">0</k></b></p>
      </div>
    </div>
        <div class="control-container">
            <div class="direction-btns">
                <div class="section-title">Richtungen</div>
                <div class="row">
                    <button id="moveUp" class="control-btn"></button>
                </div>
                <div class="row">
                    <button id="moveLeft" class="control-btn"></button>
          <button id="hiddenButton" class="control-btn"></button>
                    <button id="moveRight" class="control-btn"></button>
                </div>
                <div class="row">
                    <button id="moveDown" class="control-btn"></button>
                </div>
            </div>

            <div class="fall-button-container">
                <div class="section-title">Schnell Nachunten</div>
                <button id="fallButton" class="control-btn">↓</button>
            </div>
        </div>

        <div class="control-containerRotations">
            <div class="section-title">Rotationen</div>
            <div class="rotation-btns">
                <button id="rotateX" class="control-btn">X</button>
                <button id="rotateY" class="control-btn">Y</button>
                <button id="rotateZ" class="control-btn">Z</button>
            </div>
        </div>
    </div>

    <div class="highscores-container">
        <h2>Highscores</h2>
        <table id="highscoresTable">
            <thead>
                <tr>
                    <th>Rang</th>
                    <th>Name</th>
                    <th>Punkte</th>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>
    </div>

    <div id="gameOverPopup">
        <h2>Game Over</h2>
        <p>Ihr Score: <span id="finalScore"></span></p>
        <input type="text" id="playerName" placeholder="Name eingeben">
        <button id="submitName">Name speichern</button>
    </div>

<script>
    let isGameRunning = false; // Status: false = gestoppt, true = läuft
    const translations = {
      de: {
        start: 'Start',
        stop: "Abbrechen",
        pause: "Pause",
        difficulty: "Schwierigkeitsstufe",
        score: "Punkte",
        directions: "Richtungen",
        fall: "Schnell Nachunten",
        rotations: "Rotationen",
        gameOver: "Game Over",
        enterName: "Name eingeben",
        saveName: "Name speichern",
        highscores: "Highscores",
        rank: "Rang",
        name: "Name",
        points: "Punkte",
        easy: "Leicht",
        medium: "Mittel",
        hard: "Schwer",
        expert: "Experte"
      },
      en: {
        start: "Start",
        stop: "Stop",
        pause: "Pause",
        difficulty: "Difficulty Level",
        score: "Score",
        directions: "Directions",
        fall: "Quick Fall",
        rotations: "Rotations",
        gameOver: "Game Over",
        enterName: "Enter Name",
        saveName: "Save Name",
        highscores: "Highscores",
        rank: "Rank",
        name: "Name",
        points: "Points",
        easy: "Easy",
        medium: "Medium",
        hard: "Hard",
        expert: "Expert"
      },
      fr: {
        start: "Démarrer",
        stop: "Arrêter",
        pause: "Pause",
        difficulty: "Niveau de difficulté",
        score: "Score",
        directions: "Directions",
        fall: "Chute rapide",
        rotations: "Rotations",
        gameOver: "Game Over",
        enterName: "Entrez le nom",
        saveName: "Enregistrer le nom",
        highscores: "Meilleurs Scores",
        rank: "Rang",
        name: "Nom",
        points: "Points",
        easy: "Facile",
        medium: "Moyen",
        hard: "Difficile",
        expert: "Expert"
      },
      es: {
        start: "Iniciar",
        stop: "Detener",
        pause: "Pausa",
        difficulty: "Nivel de Dificultad",
        score: "Puntuación",
        directions: "Direcciones",
        fall: "Caída rápida",
        rotations: "Rotaciones",
        gameOver: "Fin del Juego",
        enterName: "Introducir Nombre",
        saveName: "Guardar Nombre",
        highscores: "Puntuaciones Altas",
        rank: "Rango",
        name: "Nombre",
        points: "Puntos",
        easy: "Fácil",
        medium: "Intermedio",
        hard: "Difícil",
        expert: "Experto"
      },
      it: {
        start: "Avvia",
        stop: "Ferma",
        pause: "Pausa",
        difficulty: "Livello di Difficoltà",
        score: "Punteggio",
        directions: "Direzioni",
        fall: "Caduta Veloce",
        rotations: "Rotazioni",
        gameOver: "Fine del Gioco",
        enterName: "Inserisci Nome",
        saveName: "Salva Nome",
        highscores: "Punteggi Alti",
        rank: "Classifica",
        name: "Nome",
        points: "Punti",
        easy: "Facile",
        medium: "Medio",
        hard: "Difficile",
        expert: "Esperto"
      }
    };

    document.getElementById('startButton').addEventListener('click', function() {
      const button = document.getElementById('startButton');
      const buttonPause = document.getElementById('pauseButton');
      const languageSelect = document.getElementById('language-select');
      const selectedLanguage = languageSelect.value; // Aktuelle Sprache setzen

      const translation = translations[selectedLanguage];

      if (button.textContent.trim() === translation.start) {
        // Spiel starten
        isGameRunning = true; // Status aktualisieren
        button.textContent = translation.stop; // Button-Text aktualisieren
        buttonPause.style.display = 'inline'; // Pause-Button anzeigen
        buttonPause.textContent = translation.pause;
        console.log("Spiel gestartet");
      } else if(button.textContent.trim() === translation.stop){
        // Spiel stoppen
        isGameRunning = false; // Status aktualisieren
        button.textContent = translation.start; // Button-Text aktualisieren
        buttonPause.style.display = 'none'; // Pause-Button ausblenden
        console.log("Spiel gestoppt");
      }
    });

        
    function updateLanguage() {
      const languageSelect = document.getElementById('language-select');
      
      selectedLanguage = languageSelect.value;
      lang=languageSelect.value;
      // Übersetzungstexte für verschiedene Sprachen
      

      const texts = translations[selectedLanguage];

      // Übersetzungen anwenden
      document.getElementById('startButton').textContent = texts.start;
      document.getElementById('pauseButton').textContent = texts.pause;
      document.getElementById('punkteText').textContent = texts.score;
      document.querySelector('.difficulty-container .section-title').textContent = texts.difficulty;
      document.querySelector('.fall-button-container .section-title').textContent = texts.fall;
      document.querySelector('.control-containerRotations .section-title').textContent = texts.rotations;
      document.querySelector('.direction-btns .section-title').textContent = texts.directions;
      document.querySelector('.highscores-container h2').textContent = texts.highscores;
      document.querySelector('#highscoresTable th:nth-child(1)').textContent = texts.rank;
      document.querySelector('#highscoresTable th:nth-child(2)').textContent = texts.name;
      document.querySelector('#highscoresTable th:nth-child(3)').textContent = texts.points;
      document.querySelector('#gameOverPopup h2').textContent = texts.gameOver;
      document.querySelector('#gameOverPopup input').placeholder = texts.enterName;
      document.querySelector('#gameOverPopup button').textContent = texts.saveName;
      
      const difficultySelect = document.getElementById("difficultySelect");

            // Aktualisiere jede Option im Dropdown
            Array.from(difficultySelect.options).forEach(option => {
                const key = option.value;
                if (translations[key]) {
                    option.textContent = translations[key];
                }
            });
    }
    
    // Funktion, um die Highscore-Daten aus der unsichtbaren Textbox zu holen und die Tabelle zu aktualisieren
      function updateHighscores() {
          const scoresInput = document.getElementById("gameScores").value.trim(); // Holt den Wert der Textbox und entfernt überflüssige Leerzeichen
          if (scoresInput !== "") {
              // Splitte die Eingabe in Einträge, ignoriere leere Einträge
              const highscores = scoresInput.split(";").filter(entry => entry.trim() !== "");
      
              // Konvertiere die Highscores in ein Array von Objekten für die Sortierung
              const scoresArray = highscores.map(entry => {
                  const [name, points] = entry.split(",");
                  return { name: name.trim(), points: parseInt(points, 10) }; // Punkte als Zahl speichern
              });
      
              // Sortiere das Array absteigend nach Punkten
              scoresArray.sort((a, b) => b.points - a.points);
      
              // Aktualisiere die Tabelle mit den sortierten Ergebnissen
              const tableBody = document.getElementById("highscoresTable").getElementsByTagName("tbody")[0];
              tableBody.innerHTML = ""; // Tabelle leeren
      
              scoresArray.forEach((score, index) => {
                  const row = tableBody.insertRow();
                  row.insertCell(0).textContent = index + 1; // Rang (1-basiert)
                  row.insertCell(1).textContent = score.name; // Name des Spielers
                  row.insertCell(2).textContent = score.points; // Punkte des Spielers
              });
      
              // Speichere den sortierten String zurück in die Textbox
              const sortedHighscores = scoresArray
                  .map(score => `${score.name},${score.points}`) // Formatiere jeden Eintrag
                  .join(";"); // Füge sie mit Semikolon zusammen
              document.getElementById("gameScores").value = sortedHighscores; // Aktualisiere die Textbox
          } else {
              // Wenn die Textbox leer ist, leere auch die Tabelle
              const tableBody = document.getElementById("highscoresTable").getElementsByTagName("tbody")[0];
              tableBody.innerHTML = ""; // Tabelle leeren
          }
      }


        // Funktion, um das GameOver zu überprüfen und Popup anzuzeigen
        function checkGameOver() {
            const gameOverInput = document.getElementById('gameOverInput').value;
            const startButton = document.getElementById('startButton');
            const gameOverPopup = document.getElementById('gameOverPopup');
            const finalScore = document.getElementById('finalScore');
            const scoreText = document.getElementById('scoreText').textContent;
            const pauseButton = document.getElementById('pauseButton');
            const languageSelect = document.getElementById('language-select');
            const selectedLanguage = languageSelect.value; // Aktuelle Sprache setzen
      updateHighscores();
	  updateNextPiece();
            if (gameOverInput == "GameOver") {
              // Start-Button zurücksetzen
              const translation = translations[selectedLanguage];
              startButton.textContent = translation.start;
              pauseButton.style.display = 'none';
        
              // Zeige GameOver Popup an
              gameOverPopup.style.display = 'block';
              finalScore.textContent = scoreText;    
            }
        }

        // Funktion zum Speichern des Namens
        document.getElementById('submitName').addEventListener('click', function() {
            const playerName = document.getElementById('playerName').value;
            const scoreText = document.getElementById('scoreText').textContent;
            const gameScores = document.getElementById('gameScores');
            const gameOverInput = document.getElementById('gameOverInput');

            if (playerName) {
                // Neuen Score in der Format "Name,Punkte" hinzufügen
                const newScore = playerName + ',' + scoreText;
                gameScores.value = gameScores.value + ";" + newScore;
                updateHighscores();
            }
            // Verstecke das Popup
            document.getElementById('gameOverPopup').style.display = 'none';
            gameOverInput.value = "Idle";
        });
		
		// Funktion, um die Auswahl der Combobox in die Textbox zu schreiben
		document.getElementById("difficultySelect").addEventListener("change", function () {
			const selectedValue = this.value; // Aktueller Wert der Combobox
			const textbox = document.getElementById("difficultyTextbox"); // Die Textbox
			textbox.value = selectedValue; // Schreibe den Wert in die Textbox
		});


        // Überprüft regelmäßig den GameOver Status
        setInterval(checkGameOver, 1000);  // Alle 1 Sekunde überprüfen

        // Initiale Tabelle anzeigen
        updateHighscores();
    
    document.getElementById("hidden-piece-input").addEventListener("change", function () {
		updateNextPiece();
	  });

      // Definiere Tetris-Steine als Koordinatenmuster
      const pieces = {
  0: { // Punkt-Tetromino
    color: 'gray',
    blocks: [[1, 1]]
  },
  1: { // I-Tetromino
    color: 'cyan',
    blocks: [[0, 1], [1, 1], [2, 1]]
  },
  2: { // Kleines-I-Tetromino
    color: 'blue',
    blocks: [[0, 1], [1, 1]]
  },
  3: { // L-Tetromino
    color: 'orange',
    blocks: [[1, 0], [1, 1], [1, 2], [2, 2]]
  },
  4: { // T-Tetromino
    color: 'purple',
    blocks: [[1, 0], [0, 1], [1, 1], [2, 1]]
  },
  5: { // S-Tetromino
    color: 'green',
    blocks: [[0, 1], [1, 0], [1, 1], [2, 0]]
  },
  6: { // O-Tetromino
    color: 'yellow',
    blocks: [[0, 0], [0, 1], [1, 0], [1, 1]]
  },
  7: { // Kleines-L-Tetromino
    color: 'red',
    blocks: [[0, 1], [1, 1], [1, 2]]
  },
  8: { // Stern-Tetromino
    color: 'pink',
    blocks: [[0, 1], [1, 0], [1, 1], [2, 1], [1, 2]]
  },
  9: { // Großes-S-Tetromino
    color: 'lime',
    blocks: [[0, 0], [0, 1], [1, 1], [2, 1], [2, 2]]
  },
  10: { // Großes-T-Tetromino
    color: 'magenta',
    blocks: [[0, 1], [1, 1], [2, 0], [2, 1], [2, 2]]
  },
  11: { // Handy-Tetromino
    color: 'brown',
    blocks: [[0, 1], [1, 1], [1, 0], [2, 1], [2, 0]]
  },
  12: { // Großes-U-Tetromino
    color: 'teal',
    blocks: [[0, 0], [0, 1], [1, 1], [2, 1], [2, 0]]
  },
  13: { // Großes-L-Tetromino
    color: 'navy',
    blocks: [[0, 0], [0, 1], [0, 2], [1, 2], [2, 2]]
  },
  14: { // L mit Pickel
    color: 'olive',
    blocks: [[1, 0], [1, 1], [1, 2], [2, 2], [0, 1]]
  },
  15: { // Treppe-Tetromino
    color: 'gold',
    blocks: [[0, 0], [0, 1], [1, 1], [1, 2], [2, 2]]
  },
  16: { // Fragezeichen-Tetromino
    color: 'silver',
    blocks: [[-1, 1], [-1, 0], [1, 1], [0, 2], [3, 1]]
  },
  17: { // Smili-Tetromino
    color: 'black',
    blocks: [[-1, 1], [0, 2], [1, 2], [2, 2], [3, 1],[0,-1],[2,-1]]
  }
};
      // Zeichne den Tetris-Stein auf dem Canvas
      function drawPiece(pieceId) {
	  const canvas = document.getElementById('next-piece-canvas');
      const ctx = canvas.getContext('2d');
        const piece = pieces[pieceId];
        if (!piece) return; // Keine Aktion bei ungültiger ID

        // Canvas leeren
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        // Größe und Position des Blocks anpassen
        const blockSize = 20;
        const offsetX = 30;
        const offsetY = 30;

        // Setze Farbe
        ctx.fillStyle = piece.color;

        // Zeichne alle Blöcke des Steins
        piece.blocks.forEach(([row, col]) => {
          ctx.fillRect(offsetX + col * blockSize, offsetY + row * blockSize, blockSize, blockSize);
          ctx.strokeRect(offsetX + col * blockSize, offsetY + row * blockSize, blockSize, blockSize);
        });
      }

      // Funktion zum Aktualisieren des nächsten Steins
      function updateNextPiece() {
	  const hiddenInput = document.getElementById('hidden-piece-input');
        const pieceId = parseInt(hiddenInput.value, 10);
        drawPiece(pieceId);
      }

      // Initiale Anzeige
      updateNextPiece();

    
    </script>
</body>
</html>
)--espform--";
