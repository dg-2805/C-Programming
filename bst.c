#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

struct Node* generateBSTFromFile(const char* filename) {
    struct Node* root = NULL;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        root = insert(root, num);
    }
    fclose(file);
    return root;
}

int search(struct Node* root, int key) {
    int count = 0;
    struct Node* current = root;
    while (current != NULL) {
        count++;
        if (key == current->data)
            return count;
        else if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return -1;
}

struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printInRange(struct Node* root, int low, int high) {
    if (root == NULL)
        return;
    if (root->data > low)
        printInRange(root->left, low, high);
    if (root->data >= low && root->data <= high)
        printf("%d ", root->data);
    if (root->data < high)
        printInRange(root->right, low, high);
}

int calculateHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void printSubtreeHeights(struct Node* root) {
    if (root == NULL)
        return;
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    printf("Node %d: Left Subtree Height = %d, Right Subtree Height = %d\n",
           root->data, leftHeight, rightHeight);
    printSubtreeHeights(root->left);
    printSubtreeHeights(root->right);
}

struct StackNode {
    struct Node* treeNode;
    bool visited;
};

void postOrderNonRecursive(struct Node* root) {
    if (root == NULL)
        return;
    struct StackNode stack[1000];
    int top = -1;
    struct Node* current = root;
    while (current != NULL || top != -1) {
        if (current != NULL) {
            stack[++top] = (struct StackNode){current, false};
            current = current->left;
        } else {
            struct StackNode temp = stack[top];
            if (!temp.visited) {
                stack[top].visited = true;
                current = temp.treeNode->right;
            } else {
                printf("%d ", temp.treeNode->data);
                top--;
            }
        }
    }
}

struct Node* deleteInRange(struct Node* root, int low, int high) {
    if (root == NULL)
        return NULL;
    root->left = deleteInRange(root->left, low, high);
    root->right = deleteInRange(root->right, low, high);
    if (root->data >= low && root->data <= high)
        return deleteNode(root, root->data);
    return root;
}

int calculateSum(struct Node* root) {
    if (root == NULL)
        return 0;
    return root->data + calculateSum(root->left) + calculateSum(root->right);
}

struct Node* buildNewBST(struct Node* root, struct Node* newRoot) {
    if (root == NULL)
        return newRoot;
    int sum = calculateSum(root);
    newRoot = insert(newRoot, sum);
    newRoot = buildNewBST(root->left, newRoot);
    newRoot = buildNewBST(root->right, newRoot);
    return newRoot;
}

void menu() {
    printf("\n1. Build BST from file\n");
    printf("2. Search a value in BST and count nodes traversed\n");
    printf("3. Delete a value from BST\n");
    printf("4. Print values within a range in BST\n");
    printf("5. Print subtree heights of each node\n");
    printf("6. Non-recursive post-order traversal\n");
    printf("7. Delete nodes in a range\n");
    printf("8. Create a new BST based on subtree sums\n");
    printf("9. Exit\n");
}

int main() {
    struct Node* root = NULL;
    struct Node* newBST = NULL;
    int choice, value, low, high;
    
    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = generateBSTFromFile("random_integers.txt");
                printf("BST built from file.\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                int nodesTraversed = search(root, value);
                if (nodesTraversed != -1)
                    printf("Nodes traversed: %d\n", nodesTraversed);
                else
                    printf("Value not found\n");
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Value deleted!\n");
                break;

            case 4:
                printf("Enter lower and upper bound: ");
                scanf("%d %d", &low, &high);
                printf("Values in range %d to %d: ", low, high);
                printInRange(root, low, high);
                printf("\n");
                break;

            case 5:
                printSubtreeHeights(root);
                break;

            case 6:
                printf("Post-order traversal (non-recursive): ");
                postOrderNonRecursive(root);
                printf("\n");
                break;

            case 7:
                printf("Enter range to delete nodes (low high): ");
                scanf("%d %d", &low, &high);
                root = deleteInRange(root, low, high);
                printf("Nodes within range deleted!\n");
                break;

            case 8:
                newBST = buildNewBST(root, newBST);
                printf("New BST built based on subtree sums!\n");
                break;

            case 9:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/*Sample Output
1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 1
BST built from file.

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 2
Enter value to search: 35
Nodes traversed: 9

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 4
Enter lower and upper bound: 300
800
Values in range 300 to 800: 301 302 303 305 306 307 308 312 314 317 318 319 320 321 322 323 324 325 326 327 329 330 331 332 333 334 335 336 338 339 340 341 342 343 344 345 347 348 350 351 352 353 354 355 356 357 358 360 361 363 364 365 367 368 371 372 373 374 375 377 379 380 382 385 388 389 390 391 393 394 396 399 400 403 405 407 408 409 410 411 412 413 414 415 417 418 419 420 421 422 423 424 425 426 427 429 430 431 434 435 436 437 438 439 440 442 446 449 450 452 453 454 455 456 457 458 459 460 463 466 467 470 471 474 475 476 477 478 480 481 482 483 485 491 492 494 495 497 498 499 501 502 504 506 507 508 510 511 513 514 516 517 519 520 521 523 524 529 530 531 532 533 534 537 538 539 540 541 543 544 547 548 549 551 552 556 558 559 560 561 563 567 568 571 572 573 574 575 576 577 578 579 580 581 583 584 585 586 587 588 589 590 591 592 593 596 598 599 600 601 603 605 606 607 608 609 610 613 614 615 616 617 618 619 620 622 623 625 627 628 629 630 631 634 636 637 639 641 642 643 644 645 647 649 651 652 653 656 658 659 661 662 663 664 665 667 669 672 673 676 678 679 680 681 683 684 685 686 687 689 690 691 692 694 696 697 698 699 701 702 703 705 708 709 710 712 713 714 715 718 722 723 724 726 727 728 729 730 731 732 734 737 738 739 740 742 744 746 747 748 749 750 751 752 753 754 756 757 758 759 760 761 762 763 764 765 767 768 769 771 775 776 778 781 782 784 786 787 788 789 791 792 793 794 797 798 800 

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 6
Post-order traversal (non-recursive): 6 1 12 11 15 14 13 18 17 20 21 19 10 25 26 28 27 23 31 30 22 33 38 44 40 45 47 35 50 53 56 57 55 52 48 60 59 58 68 63 71 70 74 73 77 76 75 61 32 80 79 78 83 82 87 85 89 84 93 94 97 101 100 99 105 108 107 104 103 115 112 111 120 122 121 117 131 130 134 135 133 140 143 142 136 129 146 144 110 98 90 81 150 152 149 155 159 158 157 153 162 160 164 163 166 165 179 177 176 187 183 190 189 182 195 194 198 196 199 204 201 192 180 207 209 210 208 214 212 215 217 218 216 206 222 221 220 224 228 226 225 230 229 237 236 241 239 235 242 234 245 249 256 252 251 246 258 257 263 264 272 270 273 274 275 269 266 261 243 231 219 169 278 283 281 288 285 290 289 284 279 292 295 294 293 297 291 298 299 303 305 302 307 306 301 312 314 317 308 319 320 322 323 321 324 326 325 318 329 332 333 335 334 339 338 342 341 340 336 347 348 345 344 343 331 330 352 351 355 356 354 353 358 361 364 365 367 371 372 368 363 373 360 357 379 377 375 385 382 380 389 393 394 396 391 390 403 400 408 407 405 399 388 411 410 412 409 413 415 419 418 417 414 423 422 421 425 424 426 420 374 350 327 429 435 436 434 437 440 439 438 442 446 431 430 450 453 452 455 456 454 457 459 460 466 463 467 458 471 474 475 477 478 476 470 481 485 491 494 497 498 495 492 483 501 504 506 502 508 507 511 516 514 513 510 499 482 519 520 523 524 529 531 532 530 533 534 538 539 540 537 521 543 548 547 549 544 552 556 551 541 559 560 567 563 561 568 574 573 576 575 572 577 571 558 517 480 449 581 580 583 579 586 589 588 590 592 596 593 591 587 599 598 601 603 609 608 613 610 607 606 605 616 617 615 618 620 623 627 629 628 634 631 636 637 630 625 622 642 641 643 644 639 619 652 651 649 647 645 614 600 585 584 578 658 656 659 662 663 661 665 664 669 678 676 673 672 667 679 680 683 681 685 686 689 691 690 692 687 697 698 699 696 694 702 705 709 708 703 713 712 714 718 715 710 701 684 724 726 723 729 728 731 732 737 738 739 734 742 740 746 748 747 744 730 750 751 749 727 722 653 427 277 147 753 756 754 757 761 760 762 767 765 764 763 759 758 771 776 775 782 786 784 781 778 769 787 789 793 792 797 794 800 801 798 791 788 768 805 808 807 810 806 803 814 813 815 816 818 817 821 824 827 826 825 823 829 820 811 832 834 833 838 836 831 802 846 844 841 848 851 849 855 847 860 859 863 865 864 875 871 869 867 886 882 887 899 900 901 902 890 880 861 907 913 910 914 916 918 917 922 927 921 919 928 915 932 930 906 937 941 944 942 947 946 945 940 953 955 954 948 933 960 959 958 957 964 963 962 968 969 967 961 972 971 977 980 979 978 975 982 981 984 988 986 985 983 970 991 996 995 994 1000 998 992 989 956 840 752 

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 7
Enter range to delete nodes (low high): 200
10000
Nodes within range deleted!

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 6
Post-order traversal (non-recursive): 6 1 12 11 15 14 13 18 17 20 21 19 10 25 26 28 27 23 31 30 22 33 38 44 40 45 47 35 50 53 56 57 55 52 48 60 59 58 68 63 71 70 74 73 77 76 75 61 32 80 79 78 83 82 87 85 89 84 93 94 97 101 100 99 105 108 107 104 103 115 112 111 120 122 121 117 131 130 134 135 133 140 143 142 136 129 146 144 110 98 90 81 150 152 149 155 159 158 157 153 162 160 164 163 166 165 179 177 176 187 183 190 189 182 195 194 198 196 199 192 180 169 147 

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 8
New BST built based on subtree sums!

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 6
Post-order traversal (non-recursive): 6 1 12 11 15 14 13 18 17 20 21 19 10 25 26 28 27 23 31 30 22 33 38 44 40 45 47 35 50 53 56 57 55 52 48 60 59 58 68 63 71 70 74 73 77 76 75 61 32 80 79 78 83 82 87 85 89 84 93 94 97 101 100 99 105 108 107 104 103 115 112 111 120 122 121 117 131 130 134 135 133 140 143 142 136 129 146 144 110 98 90 81 150 152 149 155 159 158 157 153 162 160 164 163 166 165 179 177 176 187 183 190 189 182 195 194 198 196 199 192 180 169 147 

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 5                                              
Node 147: Left Subtree Height = 11, Right Subtree Height = 8
Node 81: Left Subtree Height = 10, Right Subtree Height = 9
Node 78: Left Subtree Height = 9, Right Subtree Height = 2
Node 32: Left Subtree Height = 7, Right Subtree Height = 8
Node 22: Left Subtree Height = 6, Right Subtree Height = 5
Node 10: Left Subtree Height = 2, Right Subtree Height = 5
Node 1: Left Subtree Height = 0, Right Subtree Height = 1
Node 6: Left Subtree Height = 0, Right Subtree Height = 0
Node 19: Left Subtree Height = 4, Right Subtree Height = 2
Node 17: Left Subtree Height = 3, Right Subtree Height = 1
Node 13: Left Subtree Height = 2, Right Subtree Height = 2
Node 11: Left Subtree Height = 0, Right Subtree Height = 1
Node 12: Left Subtree Height = 0, Right Subtree Height = 0
Node 14: Left Subtree Height = 0, Right Subtree Height = 1
Node 15: Left Subtree Height = 0, Right Subtree Height = 0
Node 18: Left Subtree Height = 0, Right Subtree Height = 0
Node 21: Left Subtree Height = 1, Right Subtree Height = 0
Node 20: Left Subtree Height = 0, Right Subtree Height = 0
Node 30: Left Subtree Height = 4, Right Subtree Height = 1
Node 23: Left Subtree Height = 0, Right Subtree Height = 3
Node 27: Left Subtree Height = 2, Right Subtree Height = 1
Node 26: Left Subtree Height = 1, Right Subtree Height = 0
Node 25: Left Subtree Height = 0, Right Subtree Height = 0
Node 28: Left Subtree Height = 0, Right Subtree Height = 0
Node 31: Left Subtree Height = 0, Right Subtree Height = 0
Node 61: Left Subtree Height = 7, Right Subtree Height = 5
Node 58: Left Subtree Height = 6, Right Subtree Height = 2
Node 48: Left Subtree Height = 5, Right Subtree Height = 4
Node 35: Left Subtree Height = 1, Right Subtree Height = 4
Node 33: Left Subtree Height = 0, Right Subtree Height = 0
Node 47: Left Subtree Height = 3, Right Subtree Height = 0
Node 45: Left Subtree Height = 2, Right Subtree Height = 0
Node 40: Left Subtree Height = 1, Right Subtree Height = 1
Node 38: Left Subtree Height = 0, Right Subtree Height = 0
Node 44: Left Subtree Height = 0, Right Subtree Height = 0
Node 52: Left Subtree Height = 1, Right Subtree Height = 3
Node 50: Left Subtree Height = 0, Right Subtree Height = 0
Node 55: Left Subtree Height = 1, Right Subtree Height = 2
Node 53: Left Subtree Height = 0, Right Subtree Height = 0
Node 57: Left Subtree Height = 1, Right Subtree Height = 0
Node 56: Left Subtree Height = 0, Right Subtree Height = 0
Node 59: Left Subtree Height = 0, Right Subtree Height = 1
Node 60: Left Subtree Height = 0, Right Subtree Height = 0
Node 75: Left Subtree Height = 4, Right Subtree Height = 2
Node 73: Left Subtree Height = 3, Right Subtree Height = 1
Node 70: Left Subtree Height = 2, Right Subtree Height = 1
Node 63: Left Subtree Height = 0, Right Subtree Height = 1
Node 68: Left Subtree Height = 0, Right Subtree Height = 0
Node 71: Left Subtree Height = 0, Right Subtree Height = 0
Node 74: Left Subtree Height = 0, Right Subtree Height = 0
Node 76: Left Subtree Height = 0, Right Subtree Height = 1
Node 77: Left Subtree Height = 0, Right Subtree Height = 0
Node 79: Left Subtree Height = 0, Right Subtree Height = 1
Node 80: Left Subtree Height = 0, Right Subtree Height = 0
Node 90: Left Subtree Height = 4, Right Subtree Height = 8
Node 84: Left Subtree Height = 2, Right Subtree Height = 3
Node 82: Left Subtree Height = 0, Right Subtree Height = 1
Node 83: Left Subtree Height = 0, Right Subtree Height = 0
Node 89: Left Subtree Height = 2, Right Subtree Height = 0
Node 85: Left Subtree Height = 0, Right Subtree Height = 1
Node 87: Left Subtree Height = 0, Right Subtree Height = 0
Node 98: Left Subtree Height = 3, Right Subtree Height = 7
Node 97: Left Subtree Height = 2, Right Subtree Height = 0
Node 94: Left Subtree Height = 1, Right Subtree Height = 0
Node 93: Left Subtree Height = 0, Right Subtree Height = 0
Node 110: Left Subtree Height = 4, Right Subtree Height = 6
Node 103: Left Subtree Height = 3, Right Subtree Height = 3
Node 99: Left Subtree Height = 0, Right Subtree Height = 2
Node 100: Left Subtree Height = 0, Right Subtree Height = 1
Node 101: Left Subtree Height = 0, Right Subtree Height = 0
Node 104: Left Subtree Height = 0, Right Subtree Height = 2
Node 107: Left Subtree Height = 1, Right Subtree Height = 1
Node 105: Left Subtree Height = 0, Right Subtree Height = 0
Node 108: Left Subtree Height = 0, Right Subtree Height = 0
Node 144: Left Subtree Height = 5, Right Subtree Height = 1
Node 129: Left Subtree Height = 4, Right Subtree Height = 4
Node 117: Left Subtree Height = 3, Right Subtree Height = 2
Node 111: Left Subtree Height = 0, Right Subtree Height = 2
Node 112: Left Subtree Height = 0, Right Subtree Height = 1
Node 115: Left Subtree Height = 0, Right Subtree Height = 0
Node 121: Left Subtree Height = 1, Right Subtree Height = 1
Node 120: Left Subtree Height = 0, Right Subtree Height = 0
Node 122: Left Subtree Height = 0, Right Subtree Height = 0
Node 136: Left Subtree Height = 3, Right Subtree Height = 2
Node 133: Left Subtree Height = 2, Right Subtree Height = 2
Node 130: Left Subtree Height = 0, Right Subtree Height = 1
Node 131: Left Subtree Height = 0, Right Subtree Height = 0
Node 135: Left Subtree Height = 1, Right Subtree Height = 0
Node 134: Left Subtree Height = 0, Right Subtree Height = 0
Node 142: Left Subtree Height = 1, Right Subtree Height = 1
Node 140: Left Subtree Height = 0, Right Subtree Height = 0
Node 143: Left Subtree Height = 0, Right Subtree Height = 0
Node 146: Left Subtree Height = 0, Right Subtree Height = 0
Node 169: Left Subtree Height = 7, Right Subtree Height = 6
Node 165: Left Subtree Height = 6, Right Subtree Height = 1
Node 163: Left Subtree Height = 5, Right Subtree Height = 1
Node 160: Left Subtree Height = 4, Right Subtree Height = 1
Node 153: Left Subtree Height = 3, Right Subtree Height = 3
Node 149: Left Subtree Height = 0, Right Subtree Height = 2
Node 152: Left Subtree Height = 1, Right Subtree Height = 0
Node 150: Left Subtree Height = 0, Right Subtree Height = 0
Node 157: Left Subtree Height = 1, Right Subtree Height = 2
Node 155: Left Subtree Height = 0, Right Subtree Height = 0
Node 158: Left Subtree Height = 0, Right Subtree Height = 1
Node 159: Left Subtree Height = 0, Right Subtree Height = 0
Node 162: Left Subtree Height = 0, Right Subtree Height = 0
Node 164: Left Subtree Height = 0, Right Subtree Height = 0
Node 166: Left Subtree Height = 0, Right Subtree Height = 0
Node 180: Left Subtree Height = 3, Right Subtree Height = 5
Node 176: Left Subtree Height = 0, Right Subtree Height = 2
Node 177: Left Subtree Height = 0, Right Subtree Height = 1
Node 179: Left Subtree Height = 0, Right Subtree Height = 0
Node 192: Left Subtree Height = 4, Right Subtree Height = 4
Node 182: Left Subtree Height = 0, Right Subtree Height = 3
Node 189: Left Subtree Height = 2, Right Subtree Height = 1
Node 183: Left Subtree Height = 0, Right Subtree Height = 1
Node 187: Left Subtree Height = 0, Right Subtree Height = 0
Node 190: Left Subtree Height = 0, Right Subtree Height = 0
Node 199: Left Subtree Height = 3, Right Subtree Height = 0
Node 196: Left Subtree Height = 2, Right Subtree Height = 1
Node 194: Left Subtree Height = 0, Right Subtree Height = 1
Node 195: Left Subtree Height = 0, Right Subtree Height = 0
Node 198: Left Subtree Height = 0, Right Subtree Height = 0

1. Build BST from file
2. Search a value in BST and count nodes traversed
3. Delete a value from BST
4. Print values within a range in BST
5. Print subtree heights of each node
6. Non-recursive post-order traversal
7. Delete nodes in a range
8. Create a new BST based on subtree sums
9. Exit
Enter your choice: 9
*/
