#include<stdio.h>

int minHeap[100];
int dataCount = 0;

int getParentIndex(int index) {
	return index / 2;
}

int getLeftIndex(int index) {
	return index * 2;
}

int getRightIndex(int index) {
	return index * 2 +1;
}

void viewHeap() {
	if(dataCount <= 0) {
		printf("Your Heap is Empty. Insert more data!\n\n");
	}
	else {
		for(int i = 1; i <= dataCount; i++)
		{
			printf("Heap[%02d] = %d\n", i, minHeap[i]);
		}
		puts("");
	}
}

void swapValue(int parentIndex, int currIndex) {
	int temp = minHeap[parentIndex];
	minHeap[parentIndex] = minHeap[currIndex];
	minHeap[currIndex] = temp;
}

void HeapUp(int index) {
	if(index <= 1) return;
	
	int parentIndex = getParentIndex(index);
	
	if(minHeap[parentIndex] <= minHeap[index]) return;
	
	swapValue(parentIndex,index);
	HeapUp(parentIndex);
}

void HeapDown(int index) {
	if(index > dataCount) return;
	
	int smallest = index;
	int leftValue = getLeftIndex(index);
	int rightValue = getRightIndex(index);
	
	if(minHeap[leftValue] < minHeap[smallest] && leftValue <= dataCount)
		smallest = leftValue;
	
	if(minHeap[rightValue] < minHeap[smallest] && rightValue <= dataCount)
		smallest = rightValue;
	
	if(smallest == index) return;
	
	swapValue(index, smallest);
	HeapDown(smallest);
}

void push(int input) {
	dataCount++;
	minHeap[dataCount] = input;
	HeapUp(dataCount);
}

int pop() {
	if(dataCount == 0) return -1;
	int removed = minHeap[1];
	swapValue(1, dataCount);
	dataCount--;
	HeapDown(1);
	return removed;
}

void createMenu() {
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Exit\n");
}

int main() {
	int input = -1, num;
	do {
		printf("Data:\n",dataCount);
		viewHeap();
		createMenu();
		
		do {
			printf("input your choice: ");
			scanf("%d", &input); getchar();
		} while(input < 1 || input > 3);
	
		switch(input) {
			case 1:
				printf("What data should be inputted into the heap?");
				scanf("%d", &num);getchar();
				push(num);
				printf("%d has been inputted into the heap\n\n", num);
				getchar();
				break;
			case 2:
				if(dataCount <= 0) {
					printf("Your heap is empty. Insert more data!\n\n");
				}
				else {
					printf("%d has been deleted\n\n", pop());
				}
				getchar();
				break;
		}
	}while (input!=3);
	
	return 0;
}
