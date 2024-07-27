import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {

    private static Matrix product;

    public static void main(String[] args) {
        Matrix m1 = new Matrix(2, 3) ;
        Matrix m2 = new Matrix(3, 1) ;
        m1.setData( new int[][] {
            { 1 , 2 , 6 } , 
            { 0 , -1 , 2 }
        });
        m2.setData( new int[][] {
            { 0 } , 
            { -5 } , 
            { 6 }
        });
        System.out.println( m1.toString() ) ;
        System.out.println( m2.toString() ) ;

        Matrix product = multiply(m1 , m2) ; 
        System.out.println( product.toString() ) ;
    }

    private static Matrix multiply(Matrix m1, Matrix m2) {
        int m = m1.getNumRows() ; 
        int n = m2.getNumCols() ; 
        System.out.println( m + " " + n ) ;
        product = new Matrix(m, n) ;
        ExecutorService threadPool = Executors.newFixedThreadPool(10) ; 
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                threadPool.submit(new MultiplyRowColRunnable(m1, m2, i, j)) ;
            }
        }
        try {
            threadPool.shutdown();
            threadPool.awaitTermination(60, TimeUnit.SECONDS) ;
            return product;
        }
        catch (InterruptedException e) {
            return null ;
        }
    }

    public static class MultiplyRowColRunnable implements Runnable {

        private Matrix m1 ; 
        private Matrix m2 ;
        private int row ;
        private int col ; 

        public MultiplyRowColRunnable(
            Matrix m1 , 
            Matrix m2 ,
            int row, 
            int col
        ) {
            this.m1 = m1 ; 
            this.m2 = m2 ; 
            this.row = row ;
            this.col = col ; 
        }

        @Override
        public void run() {
            product.setElement(
                this.row , 
                this.col , 
                dotProduct(
                    m1.getRow(this.row), 
                    m2.getColumn(this.col)
                ) 
            );
        }
    }

    private static int dotProduct(int[] vec1, int[] vec2) {
        assert vec1.length == vec2.length ; 
        int dotProduct = 0 ;
        for (int i = 0; i < vec1.length; i++) {
            dotProduct += (vec1[i] * vec2[i]) ;
        }
        return dotProduct ;
    }

}
