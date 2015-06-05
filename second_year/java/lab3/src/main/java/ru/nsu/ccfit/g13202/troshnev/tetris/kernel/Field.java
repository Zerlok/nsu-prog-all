package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field {
    private int fieldColumnsNum;
    private int fieldRowsNum;
    private Block[][] fieldBlocks;

    public Field(int rows, int columns) {
        fieldRowsNum = rows;
        fieldColumnsNum = columns;
        fieldBlocks = new Block[fieldRowsNum][fieldColumnsNum];
    }

    public void addBlock(Block b) {
        if (b == null)
            return;

        Coordinate blockPosition = b.getCoordinates();
        // Y - rowNum, X - columnNum
        fieldBlocks[blockPosition.getColumnNum()][blockPosition.getRowNum()] = b;
    }

    public void saveBlocks(Block[] blocks) {
        if (blocks == null)
            return;

        for (int i = 0; i < blocks.length; i++)
            addBlock(blocks[i]);
    }

    public boolean hasIntersection(Block[] blocks) {
        if (blocks == null)
            return false;

        Coordinate blockPosition;
        int blockRowNum;
        int blockColumnNum;

//        Cycle throw figure figureBlocks.
        for (Block block : blocks) {
            blockPosition = block.getCoordinates();
            blockRowNum = blockPosition.getColumnNum();
            blockColumnNum = blockPosition.getRowNum();

//            Check intersections with field borders and field figureBlocks.
            if ((blockColumnNum < 0)
                    || (blockColumnNum >= fieldColumnsNum)
                    || (blockRowNum >= fieldRowsNum)
                    || (blockRowNum >= 0)
                    || (fieldBlocks[blockRowNum][blockColumnNum] != null))
                return true;
        }

        return false;
    }

    public int removeFullRows() {
        int columnNum;
        int rowNum;
        int blocksInRow;
        int fullRowsNum = 0;

        for (rowNum = 0; rowNum < fieldRowsNum; rowNum++) {
            blocksInRow = 0;
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                if (fieldBlocks[rowNum][columnNum] != null)
                    ++blocksInRow;

            if (blocksInRow == fieldColumnsNum) {
                System.out.println(String.format("Removing row %1$d", rowNum));
                shiftRowsDown(rowNum);
                ++fullRowsNum;
            }
        }

        return fullRowsNum;
    }

    private void shiftRowsDown(int emptyRowNum) {
        int columnNum;
        int rowNum;
        Block block;

//        Cycle from empty row to top.
        for (rowNum = emptyRowNum; rowNum > 0; rowNum--) {
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++) {
                block = fieldBlocks[rowNum - 1][columnNum];
                block.
                fieldBlocks[rowNum][columnNum] = block;
            }
        }

//        Delete top fieldBlocks at 0 rowNum.
        for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
            fieldBlocks[0][columnNum] = null;
    }

    public int getFieldColumnsNum() {
        return fieldColumnsNum;
    }

    public int getFieldRowsNum() {
        return fieldRowsNum;
    }

    public Block[][] getFieldBlocks() {
        return fieldBlocks;
    }
}
