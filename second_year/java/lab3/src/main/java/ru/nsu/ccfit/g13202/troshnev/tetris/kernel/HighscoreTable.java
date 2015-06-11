package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import java.io.*;

/**
 * Created by zerlok on 6/11/15.
 */
public class HighscoreTable {
    private int maxHighscoresNum = 10;
    private String filepath = "highscores.txt";
    private String[] players;
    private int[] scores;

    public HighscoreTable() {
        players = new String[maxHighscoresNum];
        scores = new int[maxHighscoresNum];

        try {
            readHighscoresFromFile();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void readHighscoresFromFile() throws IOException {
        File tableFile = new File(filepath);

        if (!tableFile.exists())
            tableFile.createNewFile();

        if (!tableFile.canRead())
            throw new IOException("Can't read file: " + tableFile.getAbsolutePath());

        BufferedReader fileBuffer = new BufferedReader(new FileReader(tableFile));
        String line;
        String[] args;
        int i = 0;

        while ((i < maxHighscoresNum)
                && ((line = fileBuffer.readLine()) != null)) {
            args = line.split(" ");
            players[i] = args[0];
            scores[i] = Integer.valueOf(args[1]);
            ++i;
        }

        fileBuffer.close();
    }

    public String[] getPlayers() {
        String[] bestPlayers = new String[maxHighscoresNum];

        for (int i = 0; i < maxHighscoresNum; i++)
            bestPlayers[i] = players[i];

        return bestPlayers;
    }

    public int[] getScores() {
        int[] highscores = new int[maxHighscoresNum];

        for (int i = 0; i < maxHighscoresNum; i++)
            highscores[i] = scores[i];

        return highscores;
    }

    public int getHighscore() {
        return scores[0];
    }
}
