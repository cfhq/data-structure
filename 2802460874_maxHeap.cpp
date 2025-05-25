#include<stdio.h>

int maxHeap[100];
int dataCount = 0;

int getParentIndex(int index) {
	return index / 2;
}

int getLeftIndex(int index) {
	return index * 2;
}

int getRightIndex(int index) {
	return index * 2 + 1;
}

void viewHeap() {
	if(dataCount <= 0) {
		printf("Your Heap is Empty. Insert more data!\n\n");
	}
	else {
		for(int i = 1; i <= dataCount; i++)
		{
			printf("Heap[%02d] = %d\n", i, maxHeap[i]);
		}
		puts("");
	}
}

void swapValue(int parentIndex, int currIndex) {
	int temp = maxHeap[parentIndex];
	maxHeap[parentIndex] = maxHeap[currIndex];
	maxHeap[currIndex] = temp;
}

void HeapUp(int index) {
	if(index <= 1) return;
	
	int parentIndex = getParentIndex(index);
	if(maxHeap[parentIndex] >= maxHeap[index]) return;
	
	swapValue(parentIndex,index);
	HeapUp(parentIndex);
}

void HeapDown(int index) {
	if(index > dataCount) return;
	
	int largest = index;
	int leftValue = getLeftIndex(index);
	int rightValue = getRightIndex(index);
	
	if(maxHeap[leftValue] > maxHeap[largest] && leftValue < dataCount)
		largest = leftValue;
	
	if(maxHeap[rightValue] > maxHeap[largest] && rightValue < dataCount)
		largest = rightValue;
	
	if(largest == index) return;
	
	swapValue(index, largest);
	HeapDown(largest);
}

void push(int input) {
	dataCount++;
	maxHeap[dataCount] = input;
	HeapUp(dataCount);
}

int pop() {
	if(dataCount == 0) return -1;
	int removed = maxHeap[1];
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
