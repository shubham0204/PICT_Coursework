import java.util.Arrays;

public class Matrix extends Object {

    private int[][] data ; 
    private int rows ; 
    private int cols ;

    public Matrix(
        int rows , 
        int cols 
    ) {
        this.rows = rows ; 
        this.cols = cols ; 
        this.data = new int[rows][cols] ; 
    }

    public int getNumRows() {
        return this.rows ; 
    }

    public int getNumCols() {
        return this.cols ; 
    }

    public void setData(int[][] data) {
        assert data.length == this.rows ; 
        assert data[0].length == this.cols ; 
        this.data = data ;
    }

    public void setElement(int rowIndex, int colIndex , int element) {
        data[rowIndex][colIndex] = element ; 
    }

    public int getElement(int rowIndex, int colIndex) {
        return data[rowIndex][colIndex] ; 
    }

    public int[] getRow(int rowIndex) {
        return data[rowIndex] ; 
    }

    public int[] getColumn(int colIndex) {
        int[] col = new int[rows] ; 
        for (int i = 0; i < rows; i++) {
            col[i] = data[i][colIndex] ; 
        }
        return col ; 
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder() ; 
        for (int[] row: data) {
            sb.append( Arrays.toString(row) + "\n" ) ;
        }
        return sb.toString() ;
    }

}