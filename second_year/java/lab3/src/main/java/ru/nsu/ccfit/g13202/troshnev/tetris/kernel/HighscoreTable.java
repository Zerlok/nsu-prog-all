package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import java.io.*;

/**
 * Created by zerlok on 6/11/15.
 */
public class HighscoreTable {
    private int maxHighscoresNum = 20;
    private String filepath = "highscores.txt";
    private String[] players;
    private long[] scores;

    public HighscoreTable() {
        players = new String[maxHighscoresNum];
        scores = new long[maxHighscoresNum];

        try {
            readHighscoresFromFile();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addHighscore(String name, long score) {
        String[] updatedPlayers = new String[maxHighscoresNum];
        long[] updatedScores = new long[maxHighscoresNum];
        int index;

        for (index = 0; index < maxHighscoresNum; index++) {
            updatedPlayers[index] = players[index];
            updatedScores[index] = scores[index];

            if (score > scores[index]) {
                updatedPlayers[index] = name;
                updatedScores[index] = score;
                break;
            }
        }

        for (int j = index + 1; j < maxHighscoresNum; j++) {
            updatedPlayers[j] = players[j - 1];
            updatedScores[j] = scores[j - 1];
        }

        players = updatedPlayers;
        scores = updatedScores;

        try {
            saveHighscoresToFile();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveHighscoresToFile() throws IOException {
        File tableFile = new File(filepath);

        if (!tableFile.exists())
            tableFile.createNewFile();

        if (!tableFile.canWrite())
            throw new IOException("Can't write to file: " + tableFile.getAbsolutePath());

        BufferedWriter fileBuffer = new BufferedWriter(new FileWriter(tableFile));

        for (int i = 0; i < maxHighscoresNum; i++) {
            if (players[i] != null)
                fileBuffer.write(String.format("%1$s %2$d\n", players[i], scores[i]));
        }

        fileBuffer.close();
    }

    private void readHighscoresFromFile() throws IOException {
        File tableFile = new File(filepath);

        if (!tableFile.exists())
            tableFile.createNewFile();

        if (!tableFile.canRead())
            throw new IOException("Can't read from file: " + tableFile.getAbsolutePath());

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

    public long[] getScores() {
        long[] highscores = new long[maxHighscoresNum];

        for (int i = 0; i < maxHighscoresNum; i++)
            highscores[i] = scores[i];

        return highscores;
    }

    public long getHighscore() {
        return scores[0];
    }
}
