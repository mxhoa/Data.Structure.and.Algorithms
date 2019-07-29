import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Executors;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import java.util.concurrent.ExecutorService;

public class MultithreadedMergeSort {

    private int[] m_data;
    private int m_num_threads;
    private List<int[]> sortedChunks;

    private MultithreadedMergeSort(int numThreads, int[] data) {
        this.m_num_threads = numThreads;
        this.m_data = data;
    }

    // Sort recursively a chunk
    private static void recursiveMergeSort(int[] data, int lo, int hi) {
        if (hi - lo > 1) {
            int mi = lo + (hi - lo) / 2;
            recursiveMergeSort(data, lo, mi);
            recursiveMergeSort(data, mi, hi);
            merge(data, lo, mi, hi);
        }
    }

    // Basic algorithm: it merges two consecutives sorted chunks
    private static void merge(int[] data, int lo, int mi, int hi) {
        int[] firstPart = Arrays.copyOfRange(data, lo, mi);
        int i = 0;
        int j = mi;
        int k = lo;
        while (i < firstPart.length && j < hi) {
            if (firstPart[i] <= data[j]) {
                data[k++] = firstPart[i++];
            } else {
                data[k++] = data[j++];
            }
        }
        if (i < firstPart.length) {
            System.arraycopy(firstPart, i, data, k, firstPart.length - i);
        }
    }

    public static void sort(int[] data, int numThreads) throws InterruptedException {
        if (data != null && data.length > 1) {
            if (numThreads > 1) {
                new MultithreadedMergeSort(numThreads, data).mergeSort();
            } else {
                recursiveMergeSort(data, 0, data.length);
            }
        }
    }

    private synchronized void mergeSort() throws InterruptedException {
        // A thread pool
        ExecutorService executors = Executors.newFixedThreadPool(m_num_threads);
        this.sortedChunks = new ArrayList<>(m_num_threads - 1);
        int lo = 0;
        int hi = 0;

        // Split the work
        for (int i = 1; i <= (m_num_threads - 1); i++) {
            lo = hi;
            hi = (m_data.length * i) / (m_num_threads - 1);
            // shiing the work to worker
            executors.execute(new MergeSortWorker(lo, hi));
        }
        // Waiting until work is done
        wait();

        // Shutdown the thread pool.
        executors.shutdown();
    }

    private synchronized int[] onChunkSorted(int lo, int hi) {
        if (lo > 0 || hi < m_data.length) {
            Iterator<int[]> it = sortedChunks.iterator();

            // searching a previous or next chunk
            while (it.hasNext()) {
                int[] f = it.next();
                if (f[1] == lo || f[0] == hi) {
                    // It found a previous/next chunk
                    it.remove();
                    return f;
                }
            }
            sortedChunks.add(new int[] { lo, hi });
        } else {
            // Data is sorted
            notify();
        }
        return null;
    }

    private class MergeSortWorker implements Runnable {

        int lo;
        int hi;

        public MergeSortWorker(int lo, int hi) {
            this.lo = lo;
            this.hi = hi;
        }

        @Override
        public void run() {
            // Sort a chunk
            recursiveMergeSort(m_data, lo, hi);
            // notify the sorted fragment
            int[] nearChunk = onChunkSorted(lo, hi);

            while (nearChunk != null) {
                // there's more work: merge two consecutives sorted fragments, (lo, hi) and
                // nearChunk
                int middle;
                if (nearChunk[0] < lo) {
                    middle = lo;
                    lo = nearChunk[0];
                } else {
                    middle = nearChunk[0];
                    hi = nearChunk[1];
                }
                merge(m_data, lo, middle, hi);
                nearChunk = onChunkSorted(lo, hi);
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int numThreads = Runtime.getRuntime().availableProcessors();
        System.out.println("NUM THREADS = " + numThreads);

        Random rand = new Random();
        int[] original = new int[90000000];
        for (int i = 0; i < original.length; i++) {
            original[i] = rand.nextInt(10000);
        }

        System.out.println("Number of elements = " + original.length);
        long startTime = System.currentTimeMillis();

        MultithreadedMergeSort.sort(original, numThreads);

        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;
        // warning: Take care with microbenchmarks
        System.out.println(numThreads + "-thread MergeSort takes: " + (float) elapsedTime / 1000 + " seconds");
    }
}