void Ctb() {

       for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        for (int i = 0; i < n; i++) {
            A[i] = i+1;
        }
        shuffle(A, A+n, random_device());

        int B[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        quickSort(B, 0, n-1);
        
        BstNode* root1 = sortedArraytoBST(B, 0, n-1);
        int B_c[n];
        itct = 0;
        LevelOrder(root1, B_c);

        clock_t tStart = clock();
        BstNode* root = arrayToBST(B_c, n);
        printf("%.3f",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

        cout << ", wysokość - " << FindHeight(root);

        tStart = clock();

        for (int i = 0; i < n; i++) {
            Search(root, A[i]);
        }

        printf(", czas wyszukiwania kolejnych elementow - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

    }
}