import java.util.Random;

/**
 * QuickSortParallel
 * Partition the array once and run quick-sort in parallel for the two halves. 
 * Note that this is not the best approach, and we will see a better one later.
 */
class QuickSortParallel implements Runnable {
    private static final String TAG = QuickSorter.class.getSimpleName();

    private int[]   mDataset;
    private int     mStart, mEnd;

    QuickSortParallel(int[] data, int start, int end) {
        this.mDataset   = data;
        this.mStart     = start;
        this.mEnd       = end;
    }

    public void run() {
        qSort(this.mDataset, this.mStart, this.mEnd);
    }

    static void qSort(int[] data, int start, int end) {
        if (start >= end) return;
        int s = partition(data, start, end);
        qSort(data, start, s - 1);
        qSort(data, s + 1, end);
    }

    static int partition(int[] data, int lo, int hi) {
        if (lo == hi) return lo;
        int i = lo + 1;
        int j = hi;

        while (true) {
            while (data[i] <= data[lo] && i < hi) i++;
            while (data[lo] < data[j] && j > lo) j--;
            if (i >= j) break;
            exch(data, i, j);
        }
        exch(data, lo, j);
        return j;
    }

    static void exch(int[] data, int i, int j) {
        int tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }

    static int[] randomList(int n, int k) {
        Random random = new Random();
        int[] data = new int[n];
        for (int i = 0; i < data.length; i++) 
            data[i] = random.nextInt(k);
        return data;
    }

    public static void main(String[] args) {
        int[] data = {3, 1, 2, 5, 9, 7, 4, 1, 3, 8, 10};
        qSort(data, 0, data.length - 1);
        for (int i:data)
            System.out.printf("%d ", i);

        int n = 10000000;
        System.out.printf("\nSTART: Sorting %d mil elements", n);
        data = randomList(n, 1000000);
        int s = partition(data, 0, n - 1);
        Thread t1 = new Thread(new QuickSortParallel(data, 0, s - 1));
        Thread t2 = new Thread(new QuickSortParallel(data, s + 1, data.length - 1));
        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
        System.out.println("\nDONE");
    }
}